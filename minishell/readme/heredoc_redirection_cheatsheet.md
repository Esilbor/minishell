# Unix Shell Redirection and Heredocs Cheat Sheet

## Redirection Basics

- <span style="font-size: 2em;">`>` (write to)</span> redirects standard output to a file, overwriting the file.
  - **Example**: `echo "Hello, World!" > hello.txt`
    - This command creates `hello.txt` with "Hello, World!" as its content.

- <span style="font-size: 2em;">`>>` (append to)</span> appends standard output to a file, without overwriting the file's existing contents.
  - **Example**: `echo "Add this line." >> hello.txt`
    - This command adds "Add this line." to the end of `hello.txt`.

- <span style="font-size: 2em;">`<` (read from)</span> redirects standard input to come from a file.
  - **Example**: `grep "search" < input.txt`
    - This command searches for "search" in `input.txt`.


- <span style="font-size: 2em;">`|`</span> pipes the standard output of one command to the standard input of another.
  - **Example**: `ls | sort`
    - This command lists files and sorts them alphabetically.

## Multiple Redirections

- If multiple redirections of the same type are specified, only the last one is used.
  - **Example for Output**: `echo "data" > file1 > file2`
    - This will write "data" to `file2`, and `file1` will be created but remain empty.

  - **Example for Input**: `cat < file1 < file2`
    - This will display the contents of `file2`, ignoring `file1`.

## Heredocs

- <span style="font-size: 2em;">`<<` </span> followed by a delimiter starts a heredoc for multi-line string input.
  - **Example**:
    ```bash
    cat << EOF
    This is line one.
    This is line two.
    EOF
    ```
    - This command inputs the two lines into `cat` until "EOF" is encountered.


## Heredoc and Redirection Interaction

- When using a heredoc with redirection, the heredoc content is subject to the last redirection specified.
  - **Example**:
    ```bash
    cat > message.txt << EOF
    Line one of the message.
    Line two of the message.
    EOF
    ```
    - This writes the heredoc content to `message.txt`.

## Multiple Heredocs and Redirections

- When multiple heredocs are used with redirections, each redirection must be resolved with its corresponding heredoc. The final output is subject to the last specified redirection.
  - **Example**:
    ```bash
    cat << EOF1 > file1 | cat << EOF2 > file2
    Content for file1
    EOF1
    Content for file2
    EOF2
    ```
    - This creates `file1` with "Content for file1" and `file2` with "Content for file2".
