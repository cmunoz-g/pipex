#include "pipex.h"

void	ft_error(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_parse_envp(char **envp, t_pipex *stc)
{
	size_t	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		ft_error("No PATH found in envp");
	stc->path = ft_split(envp[i] + 5, ':');
	if (!stc->path)
		ft_error("Memory problems when splitting PATH");
}

void	ft_parse_cmds(char **argv, t_pipex *stc)
{
	stc->parsed_cmd_one = ft_split(argv[2], ' ');
	if (!stc->parsed_cmd_one)
		ft_error("Memory problems when parsing first cmd");
	stc->parsed_cmd_two = ft_split(argv[3], ' ');
	if (!stc->parsed_cmd_two)
		ft_error("Memory problems when parsing second cmd");
}

void	ft_path(t_pipex *stc)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (stc->path[i])
	{
		temp = ft_strjoin(stc->path[i], "/");
		temp = ft_strjoin(temp, stc->parsed_cmd_one[0]);
		if (access(temp, X_OK) == 0)
			stc->path_cmd_one = temp;
		else
			free(temp);
		i++;
	}
	if (!stc->path_cmd_one)
		ft_error("Could not find the first cmd");
	i = 0;
	while (stc->path[i])
	{
		temp = ft_strjoin(stc->path[i], "/");
		temp = ft_strjoin(temp, stc->parsed_cmd_two[0]);
		if (access(temp, X_OK) == 0)
			stc->path_cmd_two = temp;
		else
			free(temp);
		i++;
	}
	if (!stc->path_cmd_two)
		ft_error("Could not find the second cmd");
}
