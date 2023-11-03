# Minishell Project

## Initialization
- **Load the PATH variable**

      Retrieve the system's PATH variable, which determines where the system looks for its executables.
- **Set up signal handlers**

      Initialize handlers to capture and respond to signals like ctrl-C, ctrl-D, and ctrl-\ without terminating the shell in an unexpected manner.
- **Initialize environment variables list**

      Create or load a list or structure to manage and manipulate environment variables within the shell.

## Main Loop
While the user hasn't entered the `exit` command:
1. **Display a prompt**

        Show a user prompt, indicating that the shell is ready to accept a command.
2. **Get user input using `readline()`**

        Read the user's command line input until they press Enter.
3. **Add command to history**:

        Store the entered command so that it can be recalled later, similar to how pressing the up arrow in a terminal recalls previous commands.

   - **If input is ctrl-D**

        Recognize this as an EOF (End of File) signal, and exit the shell gracefully.
   - **If input is empty**

        If the user presses Enter without typing a command, just show the prompt again.
   - **If input is a built-in command**

        Identify if the command is one of the shell's internal commands (like `cd`, `echo`, etc.) and execute it without spawning a new process.
   - **Else**

        If the command isn't built-in:
     - **Handle quotes**

          Process single (`'`) and double (`"`) quotes which affect how strings and variables inside them are interpreted.
     - **Expand environment variables**

          Replace variables like `$HOME` or `$?` with their actual values.
     - **Handle redirections**

          Set up input and output redirection based on symbols like `<`, `>`, `<<`, and `>>`.
     - **Split commands by pipes**

          If there are pipes (`|`), split the command to execute them sequentially, passing the output of one as input to the next.

## Built-in Commands Implementation
- **echo**: Print given arguments.
  - If `-n` option is present: Outputs the given text without appending a newline at the end.
  - Else: Print the provided text followed by a newline.
- **cd**: Change the shell's current directory to the given path.
- **pwd**: Display the shell's current working directory.
- **export**: Add a new environment variable or modify the value of an existing one.
- **unset**: Remove a specified environment variable.
- **env**: List all environment variables and their values.
- **exit**: Terminate the shell session and return to the parent process.

## Signal Handling
- **ctrl-C**: Interrupt the currently running command and display a new prompt on a new line.
- **ctrl-D**: Recognize it as an EOF signal and close the shell.
- **ctrl-\**: Ignore this input and continue running.

## Cleanup
- **Free allocated memory**: Ensure that any dynamically allocated memory during the shell's execution is properly released to prevent memory leaks.
- **Close open files or pipes**: Ensure that any opened files or inter-process communication pipes are closed.
- **Exit the shell**: Terminate the shell process gracefully.
