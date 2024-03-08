/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:13:58 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/03/07 11:27:46 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str, char *message, int error_code)
{
	size_t	len_str;
	size_t	len_message;

	len_str = ft_strlen(str);
	len_message = ft_strlen(message);
	write(2, "pipex: ", 7);
	if (len_str > 0)
	{
		write(2, str, len_str);
		write(2, ": ", 2);
	}
	write(2, message, len_message);
	write(2, "\n", 1);
	// incluir aqui ft_free?
	exit(error_code);
}