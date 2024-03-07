/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:56:54 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/02/21 12:10:57 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	char	**path;
	char	**parsed_cmd_one;
	char	**parsed_cmd_two;
	char	*path_cmd_one;
	char	*path_cmd_two;
	int		fd_infile;
	int		fd_outfile;
}				t_pipex;

int		main(int argc, char *argv[], char **envp);
void	pipex(t_pipex *stc, char **envp, char **argv);
void	status(int status_one, int status_two);
void	child_one(t_pipex *stc, int *fd, char **envp, char **argv);
void	child_two(t_pipex *stc, int *fd, char **envp, char **argv);
void	ft_parse_envp(char **envp, t_pipex *stc);
void	ft_parse_cmds(char **argv, t_pipex *stc);
void	ft_path(t_pipex *stc);
void	ft_error(char *str, char *message, int error_code);
char	**awk_aux_one(char *cmd, size_t len, char *cpy);
char	**awk_aux_two(void);
char	**awk_aux_three(char *cmd, size_t len);

#endif