/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:13:53 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/03/07 11:30:28 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_awk(char *cmd)
{
	char	**res;
	char	*cpy;
	size_t	len;

	len = 0;
	if (ft_strnstr(cmd, " '{", 15) || ft_strnstr(cmd, " \"{", 15))
	{
		cmd += 4;
		while (*cmd == 34 || *cmd == 39 || *cmd == 92)
			cmd++;
		cpy = cmd;
		res = awk_aux_one(cmd, len, cpy);
	}
	else if (ft_strnstr(cmd, " '\"{", 15))
		res = awk_aux_two();
	else
		res = awk_aux_three(cmd, len);
	if (!res)
		return (NULL);
	return (res);
}

void	ft_parse_envp(char **envp, t_pipex *stc)
{
	size_t	i;
	char	*unset_path;

	unset_path = ft_strjoin("/bin:/sbin:/usr/bin:/usr/sbin:/usr/",
			"sbin:/usr/local/bin:/opt/bin:/usr/local/sbin");
	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		stc->path = ft_split(unset_path, ':');
	else
		stc->path = ft_split(envp[i] + 5, ':');
	if (!stc->path)
		ft_error("", "Memory problems when splitting PATH", EXIT_FAILURE);
	free(unset_path);
}

void	ft_parse_cmds(char **argv, t_pipex *stc)
{
	if (ft_strncmp(argv[2], "awk ", 4) == 0)
		stc->parsed_cmd_one = ft_awk(argv[2]);
	else
		stc->parsed_cmd_one = ft_split(argv[2], ' ');
	if (!stc->parsed_cmd_one)
		ft_error("", "Memory problems when parsing first cmd", EXIT_FAILURE);
	if (ft_strncmp(argv[3], "awk ", 4) == 0)
		stc->parsed_cmd_two = ft_awk(argv[3]);
	else
		stc->parsed_cmd_two = ft_split(argv[3], ' ');
	if (!stc->parsed_cmd_two)
		ft_error("", "Memory problems when parsing second cmd", EXIT_FAILURE);
}

void	ft_path(t_pipex *stc)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (stc->path[i])
	{
		temp = ft_strjoin(stc->path[i], "/"); // cambiar el join para que libere la primera str
		temp = ft_strjoin_free(temp, stc->parsed_cmd_one[0]);
		if (access(temp, X_OK) == 0)
			stc->path_cmd_one = ft_strdup(temp);
		free(temp);
		i++;
	}
	i = 0;
	while (stc->path[i])
	{
		temp = ft_strjoin(stc->path[i], "/");
		temp = ft_strjoin_free(temp, stc->parsed_cmd_two[0]);
		if (access(temp, X_OK) == 0)
			stc->path_cmd_two = ft_strdup(temp);
		free(temp);
		i++;
	}
}
char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s3size;

	s3size = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)malloc(s3size);
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, s1, (ft_strlen(s1) + 1));
	ft_strlcat(s3, s2, s3size);
	free((void *)s1);
	return (s3);
}