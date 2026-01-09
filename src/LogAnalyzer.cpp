#include "LogAnalyzer.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

LogAnalyzer::LogAnalyzer(const std::string& path)
    : filePath_(path)
    , infoCount_(0)
    , warnCount_(0)
    , errorCount_(0)
{
}

bool LogAnalyzer::containsToken(const std::string& line, const std::string& token) const
{
    // Check if line starts with the token followed by space
    // e.g., "INFO Server started"
    if (line.rfind(token + " ", 0) == 0) {
        return true;
    }

    // Check if token appears with space before it
    // e.g., "2026-01-05T10:23:11Z INFO Server started"
    std::string spacedToken = " " + token + " ";
    if (line.find(spacedToken) != std::string::npos) {
        return true;
    }

    // Check if token appears at end of line with space before
    // e.g., "2026-01-05T10:23:11Z INFO"
    std::string endToken = " " + token;
    if (line.length() >= endToken.length()) {
        if (line.compare(line.length() - endToken.length(), endToken.length(), endToken) == 0) {
            return true;
        }
    }

    return false;
}

void LogAnalyzer::analyze()
{
    std::ifstream file(filePath_);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filePath_);
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Check for log level tokens
        // Order matters: check most specific first, but each line should only match one level
        if (containsToken(line, "ERROR")) {
            ++errorCount_;
        } else if (containsToken(line, "WARN")) {
            ++warnCount_;
        } else if (containsToken(line, "WARNING")) {
            ++warnCount_;
        } else if (containsToken(line, "INFO")) {
            ++infoCount_;
        }
        // Lines without recognized tokens are silently ignored
    }

    file.close();
}

void LogAnalyzer::printSummary() const
{
    std::cout << "Log Summary\n";
    std::cout << "-----------\n";
    std::cout << "INFO: " << infoCount_ << "\n";
    std::cout << "WARN: " << warnCount_ << "\n";
    std::cout << "ERROR: " << errorCount_ << "\n";
}
