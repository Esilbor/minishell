# Minishell Project

## Initialization
- Load the PATH variable.
- Set up any required signal handlers (for ctrl-C, ctrl-D, and ctrl-\).
- Initialize an environment variables list.

## Main Loop
While the user hasn't entered the 'exit' command:
1. Display a prompt.
2. Get the user input using `readline()`.
3. Add command to history.

   - If the input is ctrl-D:
     - Exit the shell.
   - If the input is empty:
     - Continue to the next iteration.
   - If the input is a built-in command:
     - Execute the built-in command.
   - Else:
     - Parse the command:
       - Handle single and double quotes.
       - Detect and expand environment variables ($VAR or $?).
       - Detect redirections (`<`, `>`, `<<`, `>>`) and set them up.
       - Split the commands by pipes (`|`).

   For each command separated by a pipe:
   1. Set up the pipe.
   2. Fork a child process.
      - If child:
        - If there's a redirection, set it up.
        - Execute the command using execve.
      - Else (parent):
        - Wait for the child to finish.
        - Handle the pipe for the next command.

   Display the return status (success or error).

## Built-in Commands Implementation
- **echo**:
  - If `-n` option is present: Print without a newline at the end.
  - Else: Print with a newline.
- **cd**: Change the directory to the given path.
- **pwd**: Print the current working directory.
- **export**: Add a new environment variable or update an existing one.
- **unset**: Remove an environment variable.
- **env**: Print all environment variables.
- **exit**: Exit the shell.

## Signal Handling
- **ctrl-C**: Display a new prompt on a new line.
- **ctrl-D**: Exit the shell.
- **ctrl-\**: Do nothing.

## Cleanup
- Free any allocated memory.
- Close any open files or pipes.
- Exit the shell.
