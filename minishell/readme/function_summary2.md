# Authorized Functions in Minishell Project

# Functions and Their Uses

## **1. Readline Functions**
-  **readline**: Reads a line from the terminal. `char *readline(const char *prompt);`
- **rl_clear_history**: Clears the readline history. `void rl_clear_history(void);`
- **rl_on_new_line**: Prepares readline for a new line. `void rl_on_new_line(void);`
- **rl_replace_line**: Replaces the current line in the history. `int rl_replace_line(const char *text, int clear_undo);`
- **rl_redisplay**: Redraws the current line. `void rl_redisplay(void);`
- **add_history**: Adds a line to the readline history. `void add_history(const char *string);`

## **2. Input/Output Functions**
- **printf**: Formats and prints data. `int printf(const char *format, ...);`
- **write**: Writes to a file descriptor. `ssize_t write(int fd, const void *buf, size_t count);`
- **access**: Checks user's permissions for a file. `int access(const char *pathname, int mode);`
- **open**: Opens a file. `int open(const char *pathname, int flags);`
- **read**: Reads from a file descriptor. `ssize_t read(int fd, void *buf, size_t count);`
- **close**: Closes a file descriptor. `int close(int fd);`

## **3. Memory Management**
- **malloc**: Allocates dynamic memory. `void *malloc(size_t size);`
- **free**: Deallocates dynamic memory. `void free(void *ptr);`

## **4. Process Management**
- **fork**: Creates a new process. `pid_t fork(void);`
- **execve**: Executes a program. `int execve(const char *filename, char *const argv[], char *const envp[]);`
- **wait**: Waits for a child process. `pid_t wait(int *wstatus);`
- **waitpid**: Waits for a specific process. `pid_t waitpid(pid_t pid, int *wstatus, int options);`

## **5. Signal Handling**
- **signal**: Sets a function to handle a signal. `void (*signal(int signum, void (*handler)(int)))(int);`
- **sigaction**: Specifies signal handling with more detail. `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`
- **kill**: Sends a signal. `int kill(pid_t pid, int sig);`
- **exit**: Exits the process. `void exit(int status);`

## **6. Directory and File Management**
- **getcwd**: Gets the current working directory. `char *getcwd(char *buf, size_t size);`
- **chdir**: Changes the current directory. `int chdir(const char *path);`
- **stat/lstat/fstat**: Get file status. `int stat(const char *pathname, struct stat *statbuf);`
- **unlink**: Deletes a file. `int unlink(const char *pathname);`
- **opendir**: Opens a directory. `DIR *opendir(const char *name);`
- **readdir**: Reads a directory entry. `struct dirent *readdir(DIR *dirp);`
- **closedir**: Closes a directory. `int closedir(DIR *dirp);`

## **7. Terminal and Error Functions**
- **isatty**: Checks if a descriptor is a terminal. `int isatty(int fd);`
- **ttyname**: Returns terminal name. `char *ttyname(int fd);`
- **perror**: Prints an error message. `void perror(const char *s);`
- **strerror**: Returns error string. `char *strerror(int errnum);`

[Note: This is a concise summary of the functions. For detailed use and prototypes, refer to man pages or the previous detailed descriptions.]


## **1. Readline Functions**

- **readline**: Reads a line from the terminal.
    ```c
    char *readline(const char *prompt);
    char *line = readline("Prompt> ");
    ```
- **rl_clear_history**: Clears the entire history list.
    ```c
    void rl_clear_history(void);
    rl_clear_history();
    ```
- **rl_on_new_line**: Informs the library that the cursor is on a new line.
    ```c
    void rl_on_new_line(void);
    rl_on_new_line();
    ```
- **rl_replace_line**: Replaces the contents of the command line.
    ```c
    int rl_replace_line(const char *text, int clear_undo);
    rl_replace_line("New Command", 0);
    ```
- **rl_redisplay**: Redraws the current line.
    ```c
    void rl_redisplay(void);
    rl_redisplay();
    ```
- **add_history**: Adds the line to history.
    ```c
    void add_history(const char *string);
    add_history("echo Hello");
    ```

## **2. Basic Input/Output & Memory Management**

- **printf**: Formats and prints data.
    ```c
    int printf(const char *format, ...);
    printf("Hello %s!\n", "World");
    ```
- **malloc**: Allocates dynamic memory.
    ```c
    void *malloc(size_t size);
    int *arr = malloc(10 * sizeof(int));
    ```
- **free**: Frees allocated memory.
    ```c
    void free(void *ptr);
    free(arr);
    ```
- **write**: Writes to a file or output stream.
    ```c
    ssize_t write(int fd, const void *buf, size_t count);
    write(STDOUT_FILENO, "Hello\n", 6);
    ```
- **read**: Reads from a file or input stream.
    ```c
    ssize_t read(int fd, void *buf, size_t count);
    char buffer[256];
    read(STDIN_FILENO, buffer, sizeof(buffer));
    ```

## **3. File & Process Management**

- **open**: Opens a file descriptor.
    ```c
    int open(const char *pathname, int flags);
    int fd = open("file.txt", O_RDONLY);
    ```
- **close**: Closes a file descriptor.
    ```c
    int close(int fd);
    close(fd);
    ```
- **access**: Checks user's permissions for a file.
    ```c
    int access(const char *pathname, int mode);
    if (access("file.txt", F_OK) != -1) {
        printf("File exists.\n");
    }
    ```
- **fork**: Creates a new process.
    ```c
    pid_t fork(void);
    pid_t child_pid = fork();
    ```
- **execve**: Executes a program.
    ```c
    int execve(const char *filename, char *const argv[], char *const envp[]);
    char *argv[] = {"ls", "-l", NULL};
    execve("/bin/ls", argv, NULL);
    ```
- **wait**: Waits for process to change its state.
    ```c
    pid_t wait(int *wstatus);
    int status;
    wait(&status);
    ```

## **4. Signal Handling**

- **signal**: Sets a function to handle a signal.
    ```c
    void (*signal(int signum, void (*handler)(int)))(int);
    signal(SIGINT, signal_handler_function);
    ```
- **sigaction**: Examines and changes a signal action.
    ```c
    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    struct sigaction sa;
    sa.sa_handler = signal_handler_function;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    ```

## **5. File & Directory Info**

- **getcwd**: Gets the current working directory.
    ```c
    char *getcwd(char *buf, size_t size);
    char path[1024];
    getcwd(path, sizeof(path));
    ```
- **chdir**: Changes the current working directory.
    ```c
    int chdir(const char *path);
    chdir("/home/user");
    ```
- **stat**: Retrieves file status.
    ```c
    int stat(const char *pathname, struct stat *statbuf);
    struct stat fileStat;
    stat("file.txt", &fileStat);
    ```

## **6. Terminal & Environment**

- **isatty**: Determines if a file descriptor refers to a terminal.
    ```c
    int isatty(int fd);
    if (isatty(STDIN_FILENO)) {
        printf("stdin is a terminal\n");
    }
    ```
- **ttyname**: Gets the name of the terminal.
    ```c
    char *ttyname(int fd);
    printf("Terminal name: %s\n", ttyname(STDIN_FILENO));
    ```

## **7. Advanced Process Management**

- **waitpid**: Waits for a specific process or any child process.
    ```c
    pid_t waitpid(pid_t pid, int *wstatus, int options);
    int status;
    waitpid(child_pid, &status, 0);
    ```
- **wait3**: Waits for a child process, and returns resource usage.
    ```c
    pid_t wait3(int *wstatus, int options, struct rusage *rusage);
    struct rusage usage;
    wait3(&status, 0, &usage);
    ```
- **wait4**: Waits for a specific process, returning resource usage.
    ```c
    pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
    wait4(child_pid, &status, 0, &usage);
    ```

## **8. Signal Sets and Actions**

- **sigemptyset**: Initializes a signal set to empty.
    ```c
    int sigemptyset(sigset_t *set);
    sigset_t newset;
    sigemptyset(&newset);
    ```
- **sigaddset**: Adds a specific signal to a signal set.
    ```c
    int sigaddset(sigset_t *set, int signum);
    sigaddset(&newset, SIGINT);
    ```

## **9. Process Termination and Error Handling**

- **kill**: Sends a signal to a process.
    ```c
    int kill(pid_t pid, int sig);
    kill(child_pid, SIGTERM);
    ```
- **exit**: Exits from a program.
    ```c
    void exit(int status);
    exit(0);
    ```
- **strerror**: Returns a string describing an error number.
    ```c
    char *strerror(int errnum);
    printf("Error: %s\n", strerror(errno));
    ```
- **perror**: Prints a description of the last error.
    ```c
    void perror(const char *s);
    perror("Failed to open file");
    ```

## **10. File Handling and Duplication**

- **unlink**: Deletes a name from the file system.
    ```c
    int unlink(const char *pathname);
    unlink("tempfile.txt");
    ```
- **dup**: Duplicates a file descriptor.
    ```c
    int dup(int oldfd);
    int newfd = dup(oldfd);
    ```
- **dup2**: Duplicates a file descriptor to a specified descriptor.
    ```c
    int dup2(int oldfd, int newfd);
    dup2(oldfd, newfd);
    ```
- **pipe**: Creates a pipe between two file descriptors.
    ```c
    int pipe(int pipefd[2]);
    int fds[2];
    pipe(fds);
    ```

## **11. Directory Operations**

- **opendir**: Opens a directory stream.
    ```c
    DIR *opendir(const char *name);
    DIR *dir = opendir(".");
    ```
- **readdir**: Reads a directory entry.
    ```c
    struct dirent *readdir(DIR *dirp);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    ```
- **closedir**: Closes a directory stream.
    ```c
    int closedir(DIR *dirp);
    closedir(dir);
    ```

## **12. Terminal Control**

- **tcsetattr**: Sets terminal attributes.
    ```c
    int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    ```
- **tcgetattr**: Gets terminal attributes.
    ```c
    int tcgetattr(int fd, struct termios *termios_p);
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    ```

[... more terminal control functions as needed.]

## **13. Terminal Database Functions**

- **tgetent**: Loads a terminal description into buffer.
    ```c
    int tgetent(char *bp, const char *name);
    char buffer[1024];
    tgetent(buffer, "xterm-256color");
    ```

- **tgetflag**: Returns the value of a capability flag from the terminal database.
    ```c
    int tgetflag(const char *id);
    int amflag = tgetflag("am");
    ```

- **tgetnum**: Returns the numeric value of a capability from the terminal database.
    ```c
    int tgetnum(const char *id);
    int cols = tgetnum("cols");
    ```

- **tgetstr**: Returns the string value of a capability from the terminal database.
    ```c
    char *tgetstr(const char *id, char **area);
    char *clstr = tgetstr("cl", NULL);
    ```

- **tgoto**: Returns a cursor addressing string.
    ```c
    char *tgoto(const char *cap, int col, int row);
    char *cursor_move = tgoto("cm", 5, 10);
    ```

- **tputs**: Outputs a string to the terminal.
    ```c
    int tputs(const char *str, int affcnt, int (*putc)(int));
    tputs(cursor_move, 1, putchar);
    ```

## **14. Miscellaneous Functions**

- **isatty**: Determines if a file descriptor refers to a terminal.
    ```c
    int isatty(int fd);
    if (isatty(STDIN_FILENO)) {
        printf("stdin is a terminal.\n");
    }
    ```

- **ttyname**: Returns the terminal name.
    ```c
    char *ttyname(int fd);
    printf("Terminal name: %s\n", ttyname(STDIN_FILENO));
    ```

- **ttyslot**: Returns the terminal slot number.
    ```c
    int ttyslot(void);
    int slot = ttyslot();
    ```

- **ioctl**: Control device.
    ```c
    int ioctl(int fd, unsigned long request, ...);
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
    ```

[Note: This concludes the summary of the given functions. You can utilize them as per your requirements.]
