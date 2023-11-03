# Minishell Development Guide

## 1. Project Setup
- [ ] **Initialize a new project repository**.
- [ ] **Set up version control** (e.g., git).
- [X] **Create a basic directory structure** for your project (e.g., `src`, `include`, `bin`).
- [X] **Write a basic Makefile** to compile your program.

## 2. Command Line Input
- [X] **Integrate the `readline` library**.
- [X] **Display a simple prompt** to the user.
- [X] **Read the user input** and print it back for verification.

## 3. Basic Signal Handling
- [X] **Implement handlers** for `ctrl-C`, `ctrl-D`, and `ctrl-\` to handle them as described.

## 4. Lexer and Parser
- [X] **Write a lexer** to tokenize the user input.
  - Recognize spaces, quotes, special characters (`|`, `>`, `<`, `$`, etc.).
- [ ] **Write a parser** to transform the tokens into a command structure.
  - Handle commands, arguments, and built-in commands separately.
  - Recognize and separate pipes (`|`) and redirections (`>`, `<`, `>>`, `<<`).

## 5. Command Execution (Basic)
- [ ] **Check if the command is a built-in**.
   - If it is, execute the built-in function.
   - If not, try to execute it as an external command:
     - Search the command in the directories listed in PATH.
     - Use `fork()` and `execve()` to run the command.

## 6. Built-in Commands
- [ ] **Implement the `echo` built-in**.
- [ ] **Implement the `cd` built-in**.
- [ ] **Implement the `pwd` built-in**.
- [ ] **Implement the `export` built-in**.
- [ ] **Implement the `unset` built-in**.
- [ ] **Implement the `env` built-in**.
- [ ] **Implement the `exit` built-in**.

## 7. Advanced Command Execution
- [ ] **Implement pipes (`|`)**:
   - Use `pipe()`, adjust `stdin` and `stdout` accordingly for each command.
- [ ] **Implement input redirection (`<` and `<<`)**:
   - Adjust `stdin` for the affected command.
- [ ] **Implement output redirection (`>` and `>>`)**:
   - Adjust `stdout` for the affected command.
- [ ] **Handle errors** related to file opening, permissions, etc.

## 8. Environment Variables and Expansion
- [ ] **Implement a structure or method** to manage environment variables.
- [ ] **Allow for expansion** of environment variables (`$VARNAME`).
- [ ] **Implement the special case** for `$?`.

## 9. Quote Handling
- [] **Ensure single quotes (`'`)** prevent interpretation of all special characters within them.
- [ ] **Implement double quotes (`"`)** that allow for variable expansion but prevent interpretation of other special characters.

## 10. Command History
- [ ] **Integrate history functionality** with `readline`.
- [ ] **Ensure that history is saved** across sessions (if desired).

## 11. Testing and Debugging
- [ ] **Continuously test** each implemented feature with corner cases.
- [ ] **Use tools like `valgrind`** to check for memory leaks and other memory-related issues.
- [ ] **Debug issues** as they arise.

## 12. Cleanup and Optimization
- [ ] **Ensure all dynamically allocated memory is freed**.
- [ ] **Close any open files or pipes**.
- [ ] **Optimize for efficiency** where necessary.

## 13. Documentation
- [ ] **Write a comprehensive README**.
- [ ] **Document code** with meaningful comments.

## 14. Final Testing and Submission
- [ ] **Perform thorough testing** of the entire shell.
- [ ] **Ensure compliance** with all project requirements.
- [ ] **Prepare and submit** the project.



---
---

# Bonus Features

### 15. Logical Operators

- [ ] **Implement `&&` (AND) operator**:
  - Execute the command following this operator only if the preceding command succeeds (exits with status 0).

- [ ] **Implement `||` (OR) operator**:
  - Execute the command following this operator only if the preceding command fails (exits with non-zero status).

- [ ] **Support for Parenthesis**:
  - Implement support to group commands using parenthesis to influence the priority of logical operations.
  - Ensure proper nesting of parenthesis and handle potential errors (e.g., unmatched parenthesis).

### 16. Wildcard Expansion

- [ ] **Implement wildcard (`*`) support**:
  - Expand `*` in user input to match filenames in the current working directory.
  - Ensure correct handling when combined with other features like redirections, quotes, etc.

### 17. Bonus Testing

- [ ] **Implement thorough testing for the bonus features**:
  - Test the correct execution order with `&&` and `||` operators, especially when combined with parentheses.
  - Test the `*` wildcard functionality in different scenarios: with different file types, combined with quotes, etc.

- [ ] **Debug any issues** that arise during the testing of bonus features.

