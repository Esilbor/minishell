
# Minishell Project Mandatory Test Cases

## Overview
This document provides a series of test cases designed for the mandatory features of the Minishell project at School 42. These tests cover basic command executions, input/output redirection, and pipes.

## Test Cases

### 1. Basic Command Execution
- **Command**: `echo Hello`
- **Expected Output**: `Hello`

### 2. Single Input Redirection
- **Command**: `cat < input.txt`
- **Expected Output**: Contents of `input.txt`

### 3. Single Output Redirection
- **Command**: `ls > output.txt`
- **Expected Behavior**: Output of `ls` is saved in `output.txt`

### 4. Appending to File
- **Command**: `echo "New line" >> output.txt`
- **Expected Behavior**: "New line" is appended to `output.txt`

### 5. Pipe Between Commands
- **Command**: `ls | wc -l`
- **Expected Output**: Number of files/directories listed by `ls`

### 6. Multiple Pipes
- **Command**: `cat input.txt | grep "pattern" | wc -l`
- **Expected Output**: Number of lines in `input.txt` containing "pattern"

### 7. Using 'cd' Command
- **Command**: `cd /tmp`
- **Expected Behavior**: Changes the current directory to `/tmp`

### 8. Using 'pwd' Command
- **Command**: `pwd`
- **Expected Output**: Current working directory

### 9. Using 'env' Command
- **Command**: `env`
- **Expected Output**: List of environment variables

### 10. Using 'export' Command
- **Command**: `export NEW_VAR=42`
- **Expected Behavior**: `NEW_VAR` set to `42` in environment

### 11. Using 'unset' Command
- **Command**: `unset NEW_VAR`
- **Expected Behavior**: `NEW_VAR` removed from environment

### 12. Using 'echo' Command Without Quotes
- **Command**: `echo Testing echo command`
- **Expected Output**: `Testing echo command`

### 13. Redirecting Standard Error
- **Command**: `ls non_existing_file 2> error.txt`
- **Expected Behavior**: Error message redirected to `error.txt`

### 14. Redirecting Standard Output and Error
- **Command**: `ls 1>out.txt 2>err.txt`
- **Expected Behavior**: Output to `out.txt`, errors to `err.txt`

### 15. Command with Environment Variable
- **Command**: `echo $HOME`
- **Expected Output**: Value of `HOME` variable

### 16. Complex Command with Pipe
- **Command**: `grep "pattern" < input.txt | sort`
- **Expected Output**: Filtered and sorted lines from `input.txt`

### 17. Check Exit Status
- **Command**: `ls; echo $?`
- **Expected Output**: Exit status of `ls`

### 18. Redirection with 'echo'
- **Command**: `echo This is a test > test.txt`
- **Expected Behavior**: Text written to `test.txt`

### 19. Combining Redirection and Pipe
- **Command**: `cat input.txt | head -n 5 > output.txt`
- **Expected Behavior**: First 5 lines of `input.txt` in `output.txt`

### 20. Using Wildcards in Commands
- **Command**: `ls *.txt`
- **Expected Output**: Lists `.txt` files in current directory
