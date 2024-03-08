/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:08:03 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/03/07 11:40:07 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//PASAR LEAKS a mas casos (awk incluido, y cuando hay errores tmb)!
// revisar si meterle el ft_free en el ft_error
// apreder AWK

// void	leaks()
// {
// 	system("leaks pipex");
// }

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*stc;

	// atexit(leaks);
	if (!envp)
		ft_error("", "No environment variables", EXIT_FAILURE);
	if (argc != 5)
		ft_error("", "Wrong number of arguments", EXIT_FAILURE);
	stc = ft_calloc(1, sizeof(t_pipex));
	stc->fd_infile = open(argv[1], O_RDONLY);
	stc->fd_outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_parse_envp(envp, stc);
	ft_parse_cmds(argv, stc);
	ft_path(stc);
	pipex(stc, envp, argv);
	return (0);
}
