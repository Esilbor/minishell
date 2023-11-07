
# Parser To-Do List

Here is a step-by-step to-do list for the parser based on the provided details:

1. Define the `t_simple_cmds` structure in your program.
2. Initialize a list to hold `t_simple_cmds` nodes.
3. Begin looping through the t_lexer list to group tokens into commands:
   - Look for a pipe (`|`) token to determine the end of a command.
   - If a pipe is found, take all nodes before it as one command group.
   - If no pipe is found, take all remaining nodes as a command group.
4. For each command group identified:
   - Initialize a new `t_simple_cmds` node.
   - Loop through each token in the group and check for redirections:
     - If redirections are found (e.g., `>`, `<`, or a heredoc), store them in the `redirections` field of the `t_simple_cmds` node.
     - Remove the redirection tokens from the lexer list.
   - Check if the first word of the command is a builtin function:
     - If it is a builtin, store the pointer to the corresponding function in the `builtin` field of the `t_simple_cmds` node.
   - Combine all remaining non-redirection tokens into a 2D array (`str` field) that will be used for `execve`.
5. Special case handling:
   - Ensure that the 2D array is properly structured to represent commands that may have had their arguments separated by redirections, such as "cat > file -e".
6. Link the `t_simple_cmds` nodes together:
   - Set the `next` and `prev` pointers to maintain the order of commands.
7. Repeat the process for the entire lexer list until all tokens have been grouped into `t_simple_cmds` nodes.
8. After all commands have been parsed and the t_simple_cmds list is complete, make sure to check for any cleanup or post-processing that might be necessary, such as dealing with heredoc temporary files or finalizing any dynamic memory allocations.

Note: It's important that this list is adapted to the specifics of your implementation, particularly how memory is managed and how the lexer list is structured.
This to-do list assumes a linear flow where each lexer node is inspected sequentially, and it abstracts away some of the finer implementation details that would be required in an actual parser.
