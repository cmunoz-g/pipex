#include "pipex.h"

void	child_one(t_pipex *stc, int *fd, char **envp)
{
	dup2(stc->fd_infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(stc->fd_outfile);
	if (!stc->path_cmd_one)
		ft_error("Could not find the first cmd");
	if (execve(stc->path_cmd_one, stc->parsed_cmd_one, envp) == -1)
		ft_error("Could not execute the first cmd");
}

void	child_two(t_pipex *stc, int *fd, char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(stc->fd_outfile, STDOUT_FILENO);
	close(fd[1]);
	close(stc->fd_infile);
	if (!stc->path_cmd_two)
		ft_error("Could not find the second cmd");
	if (execve(stc->path_cmd_two, stc->parsed_cmd_two, envp) == -1)
		ft_error("Could not execute the second cmd");
}

void	pipex(t_pipex *stc, char **envp)
{
	pid_t	pid_one;
	pid_t	pid_two;
	int		status;
	int		fd[2];

	if (pipe(fd) < 0)
		ft_error("Could not create the pipe");
	pid_one = fork();
	if (pid_one < 0)
		ft_error("Could not fork the first process");
	if (pid_one == 0)
		child_one(stc, fd, envp);
	else
		close(fd[1]);
	pid_two = fork();
	if (pid_two < 0)
		ft_error("Could not fork the second process");
	if (pid_two == 0)
		child_two(stc, fd, envp);
	else
		close(fd[0]);
	waitpid(pid_one, &status, 0);
	waitpid(pid_two, &status, 0);
}