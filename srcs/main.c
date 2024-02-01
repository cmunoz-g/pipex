#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_pipex *stc;

	if (!envp || !*envp)
		ft_error("No environment variables");
	if (argc != 5)
		ft_error("Wrong number of arguments");	
	stc = ft_calloc(1, sizeof(t_pipex));
	stc->fd_infile = open(argv[1], O_RDONLY);
	stc->fd_outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (stc->fd_infile < 0 || stc->fd_outfile < 0)
		ft_error("Could not open one of the files");
	ft_parse_envp(envp, stc);
	ft_parse_cmds(argv, stc);
	ft_path(stc);
	pipex(stc, envp);
	return (0);
}

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