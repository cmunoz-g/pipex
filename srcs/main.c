#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_pipex *stc;

	if (!envp)
	{
		printf("esto sin asterisco!\n");
		ft_error("","No environment variables", EXIT_FAILURE);
	}
	if (!*envp)
	{
		printf("esto!\n");
		ft_error("","No environment variables", EXIT_FAILURE);
	}
	if (argc != 5)
		ft_error("","Wrong number of arguments", EXIT_FAILURE);	
	stc = ft_calloc(1, sizeof(t_pipex));
	stc->fd_infile = open(argv[1], O_RDONLY);
	stc->fd_outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_parse_envp(envp, stc);
	ft_parse_cmds(argv, stc);
	ft_path(stc);
	pipex(stc, envp, argv);
	return (0);
}

// gestionar awk diferente, si tiene '' quitarselas


// declare struct
	// init struct, open files
	// parse envp (locate PATH, generate a char** with all directories)
	// parse cmds (divide argv 1 and 4 with split to get a table)
	// check correct PATH, by adding / and joining path[i] with cmd[0]
	// ft_exec
		// declare pid, pid2, status, pipefd
		// pipe, fork
		// if child
			//dup2, execve (con path_cmd_one, parsed_cmd_one, envp)
		// if parent
			// fork
			// if child 2
				//dup2, execve (two)
			// if parent
				//waitpid(child one)
				//waitpid (child two)