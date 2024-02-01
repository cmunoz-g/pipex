#include "pipex.h"

// con este comando no funciona, revisar ft_awk para que se comporte correctamente en todas circunstancias y que sea 
// eficiente y con pocas lineas
//  ./pipex infile.txt "grep hello" "awk '\"{count++} END {print count}\"'" outfile.txt
// {count++} END {print count}"
// 34, 39, 92

char	**ft_awk(char *cmd)
{
	char	**res;
	char	*cpy;
	size_t	len;

	len = 0;
	cmd += 4;
	while (*cmd == 34 || *cmd == 39 || *cmd == 92)
		cmd++;
	cpy = cmd;
	while (*cpy != 34 && *cpy != 39 && *cpy != 92)
	{
		cpy++;
		len++;
	}
	res = (char **)malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = ft_strdup("awk");
	if (!res[0])
		return (NULL);
	res[1] = (char *)malloc(len + 1);
	if (!res[1])
		return (NULL); 
	ft_strlcpy(res[1], cmd, len + 1);
	res[2] = NULL;
	printf("%s\n",res[1]);
	exit(0);
	return (res);
}

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
	if (ft_strncmp(argv[2], "awk ", 4) == 0)
		stc->parsed_cmd_one = ft_awk(argv[2]);
	else
		stc->parsed_cmd_one = ft_split(argv[2], ' ');
	if (!stc->parsed_cmd_one)
		ft_error("Memory problems when parsing first cmd");
	if (ft_strncmp(argv[3], "awk ", 4) == 0)
		stc->parsed_cmd_two = ft_awk(argv[3]);
	else
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
}
