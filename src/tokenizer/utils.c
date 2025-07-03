/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:27:23 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:27:25 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_in(char *input)
{
	if (ft_strncmp(">>", input, ft_strlen(input)) == 0)
		return (1);
	else if (ft_strncmp(">", input, ft_strlen(input)) == 0)
		return (1);
	return (0);
}

int	is_redirect_out(char *input)
{
	if (ft_strncmp("<<", input, ft_strlen(input)) == 0)
		return (1);
	else if (ft_strncmp("<", input, ft_strlen(input)) == 0)
		return (1);
	return (0);
}

int	is_command(char *token)
{
	if (ft_strncmp("echo", token, ft_strlen(token)) == 0)
		return (1);
	else if (ft_strncmp("cd", token, ft_strlen(token)) == 0)
		return (1);
	else if (ft_strncmp("pwd", token, ft_strlen(token)) == 0)
		return (1);
	else if (ft_strncmp("export", token, ft_strlen(token)) == 0)
		return (1);
	else if (ft_strncmp("unset", token, ft_strlen(token)) == 0)
		return (1);
	else if (ft_strncmp("env", token, ft_strlen(token)) == 0)
		return (1);
	else if (ft_strncmp("exit", token, ft_strlen(token)) == 0)
		return (1);
	return (0);
}

int	is_redirect(char *input)
{
	if (ft_strncmp(">>", input, ft_strlen(input)) == 0)
		return (1);
	else if (ft_strncmp(">", input, ft_strlen(input)) == 0)
		return (1);
	else if (ft_strncmp("<<", input, ft_strlen(input)) == 0)
		return (1);
	else if (ft_strncmp("<", input, ft_strlen(input)) == 0)
		return (1);
	else if (ft_strncmp("|", input, ft_strlen(input)) == 0)
		return (1);
	return (0);
}
