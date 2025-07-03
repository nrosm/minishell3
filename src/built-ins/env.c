/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:46 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 17:06:04 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *data, char **args)
{
	t_env	*current;
	char	*line;
	char	*tmp;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	if (!data->env)
		return (EXIT_FAILURE);
	current = data->env;
	while (current)
	{
		if (current->value)
		{
			line = ft_strjoin(current->key, "=");
			if (!line)
				return (EXIT_FAILURE);
			tmp = ft_strjoin(line, current->value);
			free(line);
			if (!tmp)
				return (EXIT_FAILURE);
			ft_putendl_fd(tmp, STDOUT_FILENO);
			free(tmp);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

