/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:58:25 by zaquedev          #+#    #+#             */
/*   Updated: 2023/11/29 16:59:17 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




/*
int	execution(t_data *data, t_cmd *cmd)
{

	int fork_nb = 0;
	int pid;

	while (cmd)
	{
		//fork_nb = ?

		
	}
	
}
*/



/*

enum PIPES 
{
    READ, 
    WRITE
};

void execute_pipeline(char*** pipeline)
{
    int fd[2];
    int fd_backup = 0;
    pid_t child_pid;

    while (*pipeline != '\0')
    {
        pipe(fd);
        child_pid = fork();

        if(child_pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if(child_pid == 0)
        {
            dup2(fd_backup, 0);// (old, new)
            close(fd[READ]);

            if(*(pipeline + 1) != '\0')
            {
                dup2(fd[WRITE], 1);
            }
            execvp((*pipeline)[0], *pipeline);
            exit(1);
        }
        else// Parent process
        {
            wait(NULL);
            close(fd[WRITE]);
            fd_backup = fd[READ];
            pipeline++;
        }
    }
}



*/




/*

  int i;
        pid_t children[numberOfCommands - 1];
        pid_t groupId = -1;
        for (i = 1; i < numberOfCommands - 1; i++)
        {
            int pd[2];
            if(pipe(pd) < 0){
                unix_error("Pipe failed");
            }
            pid = fork();
            children[i] = pid;
            if (!pid)
            {
                dup2(pd[1], 1);
                if (execve(argv[cmds[i]], argv, environ) < 0)
                {
                    unix_error("First Execve failed");
                }
            }
            else
            {
                if (i == 0)
                {
                    groupId = pid;
                }
                setpgid(pid, groupId);
            }
            dup2(pd[0], 0);
            close(pd[0]);
            close(pd[1]);
        }
        if (execve(argv[0], argv, environ) < 0) //  -->  EOF  ??
        {
            unix_error("Second Execve failed");
        }
        for (int j = 0; j < numberOfCommands; j++)
        {
            waitpid(children[j], NULL, 0);
        }





*/










