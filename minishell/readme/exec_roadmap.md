# Roadmap for `EXEC` Part in Minishell

## **Introduction**
In this roadmap, we focus on the execution of commands that have been parsed and passed on by the Parsing component. Your job is to take the structured command data and execute it, ensuring that commands are carried out correctly with respect to the shell's specifications.

## **1. Receiving Parsed Command Data**
- **Goal**: Understand the structure and data received from the Parsing component.
- **Tasks**:
    1. Coordinate with the Parsing teammate to understand the format of parsed commands.
    2. Define a clear interface or data structure to receive this parsed information.

## **2. Command Path Resolution**
- **Goal**: Ensure that commands can be executed using both absolute and relative paths.
- **Tasks**:
    1. Check if the command contains a '/' (indicating it might be a relative or absolute path).
    2. If not, search directories listed in the `PATH` environment variable.
    3. Resolve the command to its absolute path.

## **3. Process Creation with fork**
- **Goal**: Execute commands in a child process to keep the main shell process intact.
- **Tasks**:
    1. Use `fork` to create a child process.
    2. In the child process (where `fork` returns 0), proceed to command execution.

## **4. Command Execution Using execve**
- **Goal**: Actual command execution using the `execve` function.
- **Tasks**:
    1. Use `execve` with the correct path and the provided arguments from the Parsing component.
    2. Construct the `envp` array from your shell's environment variables (if you have implemented them).

## **5. Handling Errors**
- **Goal**: Manage cases where the command can't be executed.
- **Tasks**:
    1. Check the return value of `execve`.
    2. If it's `-1`, handle the error gracefully, possibly using `perror` to display a relevant error message.
    3. Return to the shell's prompt.

## **6. Implementing Redirection and Piping**
- **Goal**: Use the redirection and piping information from the Parsing component to adjust file descriptors.
- **Tasks**:
    1. Set up any required pipes using the `pipe` function.
    2. Set up file descriptors for input/output redirection using `open`, `dup`, and `dup2`.
    3. Ensure proper closure of file descriptors and pipes to avoid resource leaks.

## **7. Clean-up and Testing**
- **Goal**: Ensure seamless integration with the Parsing component and overall functionality.
- **Tasks**:
    1. Collaborate with the Parsing teammate for integrated tests.
    2. Test various commands with different arguments and structures.
    3. Ensure the shell returns to its prompt after command execution.
    4. Check for resource leaks related to file descriptors.

---

This refactored roadmap emphasizes the collaborative nature of your project, ensuring that the execution part is well-integrated with parsed command structures. Regular communication with your Parsing teammate is key to ensuring that interfaces match and the overall shell functions smoothly.
