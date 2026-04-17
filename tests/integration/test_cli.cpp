#include <filesystem>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <cstdio>
#define popen _popen
#define pclose _pclose
#else
#include <cstdio>
#include <sys/wait.h>
#endif

class CLIProcessTest : public ::testing::Test {
protected:
  // Helper to run CLI and capture output
  static int run_cli(const std::vector<std::string> &args, std::string &output,
                     std::string &error) {
    // Determine the CLI executable path
    // The test executable is in: build/release/tests/ or build/debug/tests/
    // The CLI executable is in: build/release/ or build/debug/
    // So we need to go up one directory: ../falcon-db-cli(.exe)

    std::string cli_path = "..";
    cli_path = (std::filesystem::path(cli_path) / "falcon-db-cli").string();

#ifdef _WIN32
    cli_path += ".exe";
#endif

    // Verify the path exists
    if (!std::filesystem::exists(cli_path)) {
      // Try alternative: maybe it's in the same directory
      std::string alt_path = "falcon-db-cli";
#ifdef _WIN32
      alt_path += ".exe";
#endif
      if (std::filesystem::exists(alt_path)) {
        cli_path = alt_path;
      } else {
        std::cerr << "falcon-db-cli not found at " << cli_path << " or "
                  << alt_path << '\n';
        error = "falcon-db-cli not found";
        return 127;
      }
    }

    std::ostringstream cmd;
#ifdef _WIN32
    // On Windows, to use output redirection, run via cmd /C
    cmd << "cmd /C \"" << cli_path;
    for (const auto &arg : args) {
      cmd << " " << arg;
    }
    cmd << " 2>&1\"";
#else
    cmd << cli_path;
    for (const auto &arg : args) {
      cmd << " " << arg;
    }
    cmd << " 2>&1";
#endif

    std::string command_str = cmd.str();

    FILE *pipe = popen(command_str.c_str(), "r");
    if (pipe == nullptr) {
      error = "Failed to open pipe for command: " + command_str;
      return 127;
    }

    char buffer[256];
    output.clear();
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
      output += buffer;
    }

    int status = pclose(pipe);
#ifdef _WIN32
    // On Windows, pclose returns the exit code directly.
    return status;
#else
    // On POSIX, check if process exited normally and return exit status.
    if (WIFEXITED(status)) {
      return WEXITSTATUS(status);
    } else {
      return 127; // Abnormal termination
    }
#endif
  }
};

TEST_F(CLIProcessTest, HelpCommandOutput) {
  std::string output, error;
  int exit_code = run_cli({"help"}, output, error);
  ASSERT_EQ(exit_code, 0) << "Output: " << output << "\nError: " << error;
  ASSERT_NE(output.find("falcon-db-cli: A command-line interface"),
            std::string::npos);
  ASSERT_NE(output.find("Usage:"), std::string::npos);
}

TEST_F(CLIProcessTest, SchemaCommandOutput) {
  std::string output, error;
  int exit_code = run_cli({"schema"}, output, error);
  ASSERT_EQ(exit_code, 0) << "Output: " << output << "\nError: " << error;
  ASSERT_NE(
      output.find("\"$schema\": \"http://json-schema.org/draft-07/schema#\""),
      std::string::npos);
  ASSERT_NE(
      output.find("\"title\": \"Falcon Device Characteristics Snapshot\""),
      std::string::npos);
}

TEST_F(CLIProcessTest, InvalidCommandError) {
  std::string output, error;
  int exit_code = run_cli({"unknown_command"}, output, error);
  ASSERT_NE(exit_code, 0);
  ASSERT_NE(output.find("Unknown command: unknown_command"), std::string::npos);
}

TEST_F(CLIProcessTest, DBArgMissingValue) {
  std::string output, error;
  int exit_code = run_cli({"--db"}, output, error);
  ASSERT_NE(exit_code, 0);
  ASSERT_NE(output.find("Error: --db requires an argument."),
            std::string::npos);
}

TEST_F(CLIProcessTest, ValidateNonExistentFile) {
  std::string output, error;
  int exit_code =
      run_cli({"snapshot", "validate", "does_not_exist.json"}, output, error);
  // It should fail validation because the file cannot be opened.
  ASSERT_NE(exit_code, 0);
  ASSERT_NE(output.find("Snapshot validation failed: does_not_exist.json"),
            std::string::npos);
}
