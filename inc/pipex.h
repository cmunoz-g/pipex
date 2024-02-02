#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct	s_pipex
{
	char **path;
	char **parsed_cmd_one;
	char **parsed_cmd_two;
	char *path_cmd_one;
	char *path_cmd_two;
	int fd_infile;
	int fd_outfile;
}				t_pipex;

int	main(int argc, char *argv[], char **envp);
void	pipex(t_pipex *stc, char **envp);
void	child_one(t_pipex *stc, int *fd, char **envp);
void	child_two(t_pipex *stc, int *fd, char **envp);
void	ft_parse_envp(char **envp, t_pipex *stc);
void	ft_parse_cmds(char **argv, t_pipex *stc);
void	ft_path(t_pipex *stc);
void	ft_error(char *str, int error_code);

#endif