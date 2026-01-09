cmake_minimum_required(VERSION 3.15)
project(loganalyzer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
add_executable(loganalyzer
    src/main.cpp
    src/LogAnalyzer.cpp
)

target_include_directories(loganalyzer PRIVATE include)

# Install rule - binary goes to <prefix>/bin
install(TARGETS loganalyzer
        RUNTIME DESTINATION bin)

# --- CPack configuration (NSIS + ZIP) ---
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "loganalyzer")
set(CPACK_PACKAGE_VENDOR "Your Name")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ CLI tool to analyze Docker-style logs")
set(CPACK_PACKAGE_CONTACT "your.email@example.com")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "LogAnalyzer")

# Generators: NSIS for Windows installer, ZIP for portable archive
set(CPACK_GENERATOR "NSIS;ZIP")

# NSIS customization
set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_NSIS_HELP_LINK "https://github.com/roy-herzlichkeit/Theory")
set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/roy-herzlichkeit/Theory")
set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)