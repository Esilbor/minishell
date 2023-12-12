
# Minishell Project Test Cases

## Overview
This document provides a series of test cases designed for the Minishell project of School 42. These tests focus on input/output redirection and multi-pipe commands, mimicking the behavior of `bash --posix`.

## Test Cases

### 1. Single Input Redirection
- **Command**: `cat < input.txt`
- **Expected Result**: Contents of `input.txt` are displayed.
- **Terminal Output**: 
  ```
  [contents of input.txt]
  ```

### 2. Single Output Redirection
- **Command**: `ls > output.txt`
- **Expected Result**: Output of `ls` is saved in `output.txt`.
- **Terminal Output**: No output on the terminal.

### 3. Appending Output Redirection
- **Command**: `echo "hello" >> output.txt`
- **Expected Result**: "hello" is appended to `output.txt`.
- **Terminal Output**: No output on the terminal.

### 4. Piping Between Commands
- **Command**: `ls | wc -l`
- **Expected Result**: Number of files/directories in the current directory.
- **Terminal Output**: 
  ```
  [number of files/directories]
  ```

### 5. Multiple Pipes
- **Command**: `cat input.txt | grep "pattern" | sort`
- **Expected Result**: Lines containing "pattern" from `input.txt`, sorted.
- **Terminal Output**: 
  ```
  [sorted lines with "pattern"]
  ```

### 6. Input and Output Redirection with Pipe
- **Command**: `grep "pattern" < input.txt | sort > output.txt`
- **Expected Result**: Lines with "pattern" from `input.txt` are sorted and saved to `output.txt`.
- **Terminal Output**: No output on the terminal.

### 7. Command Substitution
- **Command**: `echo "Today is $(date)"`
- **Expected Result**: Current date is displayed in the output.
- **Terminal Output**: 
  ```
  Today is [current date]
  ```

### 8. Redirection with Built-in Command
- **Command**: `echo "List:" > output.txt && ls >> output.txt`
- **Expected Result**: "List:" and the output of `ls` are saved in `output.txt`.
- **Terminal Output**: No output on the terminal.

### 9. Error Redirection
- **Command**: `ls non_existing_file 2> error.txt`
- **Expected Result**: Error message is saved in `error.txt`.
- **Terminal Output**: No output on the terminal.

### 10. Combining Input, Output, and Error Redirection
- **Command**: `grep "pattern" < input.txt > output.txt 2> error.txt`
- **Expected Result**: Lines with "pattern" are saved in `output.txt`; errors are saved in `error.txt`.
- **Terminal Output**: No output on the terminal.
