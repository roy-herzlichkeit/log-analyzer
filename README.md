# Log Analyzer CLI

A small, robust C++ CLI tool that parses Docker-style log files, counts INFO/WARN/ERROR entries, and prints a concise summary.

## Features

- Parses standard Docker-style log format
- Counts INFO, WARN, and ERROR log entries
- Clean exit codes for scripting integration
- Distributed via NSIS installer or portable ZIP

## Build

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

## Run

```bash
./loganalyzer ../sample_logs/docker.log
```

Expected output:
```
Log Summary
-----------
INFO: 12
WARN: 2
ERROR: 1
```

## Package (Windows)

### NSIS Installer
First, install NSIS: https://nsis.sourceforge.io/Download

```bash
cd build
cpack -G NSIS
```

This creates `loganalyzer-1.0.0-win64.exe` installer.

### Portable ZIP

```bash
cd build
cpack -G ZIP
```

This creates `loganalyzer-1.0.0.zip` portable archive.

### Both at once

```bash
cd build
cpack
```

## Log File Format

The analyzer expects log files with lines in the following format:
```
<timestamp> <LEVEL> <message>
```

Where `<LEVEL>` is one of:
- `INFO` - Informational messages
- `WARN` or `WARNING` - Warning messages
- `ERROR` - Error messages

Example:
```
2026-01-05T10:23:11Z INFO Server started
2026-01-05T10:24:02Z ERROR Database timeout
2026-01-05T10:24:45Z WARN Disk usage high
```

## Exit Codes

| Code | Description |
|------|-------------|
| 0    | Success     |
| 1    | Error (file not found, parse error, invalid arguments) |

## License

MIT License
