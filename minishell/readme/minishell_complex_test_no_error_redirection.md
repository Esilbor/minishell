
# Minishell Project Complex Test Case Without Error Redirection

## Overview
This test case is designed to challenge the robustness of the shell's parsing and execution capabilities, focusing on multiple redirections, heredocs, and multi-pipe commands without error redirection.

## Complex Test Case

### Command
```bash
cat < input.txt | grep "Pattern" | sort | uniq > sorted_output.txt << EOF
additional
input
EOF
```

### Expected Behavior
1. **Input Redirection (`<`)**: The shell reads from `input.txt` as the input for the `cat` command.
2. **Heredoc (`<< EOF`)**: The heredoc provides additional input after `input.txt`. Note that `cat` typically doesn't read from the standard input if a file is provided, so this part might not affect the output (depends on implementation).
3. **Pipe (`|`)**: The output of `cat` is piped to `grep`, which filters lines containing "Pattern". This output is then piped to `sort`, and subsequently to `uniq` to remove any duplicate lines.
4. **Output Redirection (`>`)**: The final output (unique sorted lines containing "Pattern") is redirected to `sorted_output.txt`.

### Testing Steps
1. Create an `input.txt` with several lines of text, ensuring some lines include the word "Pattern".
2. Execute the command in the Minishell.
3. Check `sorted_output.txt` to see if it contains the correct sorted and unique lines that include "Pattern".
