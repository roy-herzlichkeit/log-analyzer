#ifndef LOG_ANALYZER_H
#define LOG_ANALYZER_H

#include <string>

/**
 * @class LogAnalyzer
 * @brief Parses Docker-style log files and counts INFO/WARN/ERROR entries.
 *
 * Usage:
 *   LogAnalyzer analyzer("path/to/logfile.log");
 *   analyzer.analyze();
 *   analyzer.printSummary();
 */
class LogAnalyzer {
public:
    /**
     * @brief Constructs a LogAnalyzer for the given file path.
     * @param path Path to the log file to analyze.
     */
    explicit LogAnalyzer(const std::string& path);

    /**
     * @brief Analyzes the log file, counting INFO/WARN/ERROR entries.
     * @throws std::runtime_error if file cannot be opened.
     */
    void analyze();

    /**
     * @brief Prints a summary of log entry counts to stdout.
     */
    void printSummary() const;

    // Accessors for counts (useful for testing)
    int getInfoCount() const { return infoCount_; }
    int getWarnCount() const { return warnCount_; }
    int getErrorCount() const { return errorCount_; }

private:
    std::string filePath_;
    int infoCount_  = 0;
    int warnCount_  = 0;
    int errorCount_ = 0;

    /**
     * @brief Checks if a line contains a specific log level token.
     * @param line The log line to check.
     * @param token The token to search for (e.g., "INFO", "WARN", "ERROR").
     * @return true if token is found as a word boundary, false otherwise.
     */
    bool containsToken(const std::string& line, const std::string& token) const;
};

#endif // LOG_ANALYZER_H
