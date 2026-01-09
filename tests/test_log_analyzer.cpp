/**
 * @file test_log_analyzer.cpp
 * @brief Simple unit tests for LogAnalyzer.
 *
 * This is a minimal test file that can be run standalone or integrated
 * with a testing framework like GoogleTest or Catch2.
 *
 * Compile: g++ -std=c++17 -I../include test_log_analyzer.cpp ../src/LogAnalyzer.cpp -o test_runner
 * Run: ./test_runner
 */

#include "LogAnalyzer.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

// Test helper: create a temporary log file with given content
std::string createTempLogFile(const std::string& content)
{
    std::string tempPath = (fs::temp_directory_path() / "test_log.log").string();
    std::ofstream file(tempPath);
    file << content;
    file.close();
    return tempPath;
}

// Test helper: cleanup temp file
void cleanupTempFile(const std::string& path)
{
    fs::remove(path);
}

// Test 1: Basic counting
void testBasicCounting()
{
    std::string content = 
        "2026-01-05T10:23:11Z INFO Server started\n"
        "2026-01-05T10:24:02Z ERROR Database timeout\n"
        "2026-01-05T10:24:45Z WARN Disk usage high\n"
        "2026-01-05T10:25:00Z INFO Processing complete\n";
    
    std::string path = createTempLogFile(content);
    
    LogAnalyzer analyzer(path);
    analyzer.analyze();
    
    assert(analyzer.getInfoCount() == 2 && "Expected 2 INFO entries");
    assert(analyzer.getWarnCount() == 1 && "Expected 1 WARN entry");
    assert(analyzer.getErrorCount() == 1 && "Expected 1 ERROR entry");
    
    cleanupTempFile(path);
    std::cout << "[PASS] testBasicCounting\n";
}

// Test 2: Empty file
void testEmptyFile()
{
    std::string path = createTempLogFile("");
    
    LogAnalyzer analyzer(path);
    analyzer.analyze();
    
    assert(analyzer.getInfoCount() == 0 && "Expected 0 INFO entries");
    assert(analyzer.getWarnCount() == 0 && "Expected 0 WARN entries");
    assert(analyzer.getErrorCount() == 0 && "Expected 0 ERROR entries");
    
    cleanupTempFile(path);
    std::cout << "[PASS] testEmptyFile\n";
}

// Test 3: File not found
void testFileNotFound()
{
    LogAnalyzer analyzer("/nonexistent/path/to/file.log");
    
    bool exceptionThrown = false;
    try {
        analyzer.analyze();
    }
    catch (const std::runtime_error& e) {
        exceptionThrown = true;
    }
    
    assert(exceptionThrown && "Expected exception for missing file");
    std::cout << "[PASS] testFileNotFound\n";
}

// Test 4: Multiple ERROR entries
void testMultipleErrors()
{
    std::string content = 
        "2026-01-05T10:23:11Z ERROR First error\n"
        "2026-01-05T10:24:02Z ERROR Second error\n"
        "2026-01-05T10:24:45Z ERROR Third error\n";
    
    std::string path = createTempLogFile(content);
    
    LogAnalyzer analyzer(path);
    analyzer.analyze();
    
    assert(analyzer.getErrorCount() == 3 && "Expected 3 ERROR entries");
    assert(analyzer.getInfoCount() == 0 && "Expected 0 INFO entries");
    assert(analyzer.getWarnCount() == 0 && "Expected 0 WARN entries");
    
    cleanupTempFile(path);
    std::cout << "[PASS] testMultipleErrors\n";
}

// Test 5: Lines without recognized tokens
void testUnrecognizedLines()
{
    std::string content = 
        "2026-01-05T10:23:11Z DEBUG Some debug info\n"
        "2026-01-05T10:24:02Z TRACE Trace message\n"
        "Some random text\n"
        "2026-01-05T10:24:45Z INFO Valid info line\n";
    
    std::string path = createTempLogFile(content);
    
    LogAnalyzer analyzer(path);
    analyzer.analyze();
    
    assert(analyzer.getInfoCount() == 1 && "Expected 1 INFO entry");
    assert(analyzer.getWarnCount() == 0 && "Expected 0 WARN entries");
    assert(analyzer.getErrorCount() == 0 && "Expected 0 ERROR entries");
    
    cleanupTempFile(path);
    std::cout << "[PASS] testUnrecognizedLines\n";
}

// Test 6: Sample docker.log file (if exists)
void testSampleDockerLog()
{
    std::string samplePath = "../sample_logs/docker.log";
    
    if (!fs::exists(samplePath)) {
        std::cout << "[SKIP] testSampleDockerLog - sample file not found\n";
        return;
    }
    
    LogAnalyzer analyzer(samplePath);
    analyzer.analyze();
    
    // Based on our sample_logs/docker.log content:
    // INFO: 12, WARN: 2, ERROR: 1
    assert(analyzer.getInfoCount() == 12 && "Expected 12 INFO entries in sample");
    assert(analyzer.getWarnCount() == 2 && "Expected 2 WARN entries in sample");
    assert(analyzer.getErrorCount() == 1 && "Expected 1 ERROR entry in sample");
    
    std::cout << "[PASS] testSampleDockerLog\n";
}

int main()
{
    std::cout << "Running LogAnalyzer tests...\n\n";
    
    testBasicCounting();
    testEmptyFile();
    testFileNotFound();
    testMultipleErrors();
    testUnrecognizedLines();
    testSampleDockerLog();
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}
