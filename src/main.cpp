/**
 * @file main.cpp
 * @brief Entry point for the Log Analyzer CLI tool.
 *
 * Usage: loganalyzer <log_file>
 *
 * Exit codes:
 *   0 - Success
 *   1 - Error (file not found, invalid arguments, etc.)
 */

#include "LogAnalyzer.h"

#include <iostream>
#include <exception>

void printUsage(const char* programName)
{
    std::cerr << "Usage: " << programName << " <log_file>\n";
    std::cerr << "\n";
    std::cerr << "Analyzes a Docker-style log file and prints counts for INFO, WARN, ERROR entries.\n";
    std::cerr << "\n";
    std::cerr << "Arguments:\n";
    std::cerr << "  log_file    Path to the log file to analyze\n";
    std::cerr << "\n";
    std::cerr << "Example:\n";
    std::cerr << "  " << programName << " /var/log/docker.log\n";
}

int main(int argc, char* argv[])
{
    // Validate command line arguments
    if (argc != 2) {
        printUsage(argv[0]);
        return 1;
    }

    // Check for help flag
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
        printUsage(argv[0]);
        return 0;
    }

    try {
        // Create analyzer, process file, and print results
        LogAnalyzer analyzer(argv[1]);
        analyzer.analyze();
        analyzer.printSummary();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    catch (...) {
        std::cerr << "Error: Unknown exception occurred\n";
        return 1;
    }
}
