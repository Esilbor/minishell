# Minishell Built-ins Roadmap

## 1. **Understanding Built-ins**

### 1.1. Reasons for Built-ins
- Understand the necessity of built-in commands.
- Learn how changing directories affects the current shell process and why `cd` must be a built-in.

### 1.2. Common Built-ins
- Familiarize with commonly used built-ins in shells like `bash`.
- Decide on the built-ins to implement in Minishell based on common usage and importance.

## 2. **Implementation Roadmap**

### 2.1. `echo`
- Display a line of text.
- Implement and test options like `-n`.

### 2.2. `cd`
- Change the current directory of the shell process.
- Handle and test special arguments like `..` and `-`.
- Ensure the `PWD` environment variable is updated accordingly.

### 2.3. `pwd`
- Implement the command to print the current working directory.
- Test it to ensure it reflects the latest directory change made by `cd`.

### 2.4. `exit`
- Implement a command to exit the shell.
- Test with various exit statuses.
- Ensure any child processes or jobs are handled properly before exiting.

### 2.5. `env`
- Display the environment variables.
- Consider allowing options for modifying or adding new environment variables.

### 2.6. `setenv` and `unsetenv` (if considered for your Minishell)
- Add or modify environment variables (`setenv`).
- Remove environment variables (`unsetenv`).

### 2.7. `jobs`, `fg`, and `bg` (if advanced job control is considered)
- `jobs`: List background jobs.
- `fg`: Bring a background job to the foreground.
- `bg`: Push a foreground job to the background.

## 3. **Testing**
- Ensure that each built-in is tested in isolation.
- Test built-ins in combination to check for potential conflicts or issues.
- Compare behavior with other established shells like `bash` for consistency.
