/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:14:02 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/02/21 12:16:22 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**awk_aux_two(void)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * 2);
	if (!res)
		return (NULL);
	res[0] = ft_strdup("cat");
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	res[1] = NULL;
	return (res);
}

char	**awk_aux_one(char *cmd, size_t len, char *cpy)
{
	char	**res;

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
	{
		free(res);
		return (NULL);
	}
	res[1] = (char *)malloc(len + 1);
	if (!res[1])
	{
		(free(res[0]), free(res));
		return (NULL);
	}
	ft_strlcpy(res[1], cmd, len + 1);
	res[2] = NULL;
	return (res);
}

char	**awk_aux_three(char *cmd, size_t len)
{
	char	**res;

	res = (char **)malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = ft_strdup("awk");
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	cmd += 5;
	len = ft_strlen(cmd);
	res[1] = (char *)malloc(len + 1);
	if (!res[1])
	{
		(free(res[0]), free(res));
		return (NULL);
	}
	ft_strlcpy(res[1], cmd, len);
	res[2] = NULL;
	return (res);
}
