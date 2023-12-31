#!/bin/sh
while IFS= read -r line
do
  eval "$line"
done < "/home/esilbor/CANDYSHELL/minishell/test_list.txt"