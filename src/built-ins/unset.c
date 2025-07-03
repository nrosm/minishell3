/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:01:35 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 17:27:50 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

// static size_t	env_size(char *env)
// {
// 	size_t		i;

// 	i = 0;
// 	while (env[i] && env[i] != '=')
// 		i++;
// 	return (i);
// }

static void	free_node(t_env *node)
{
	if (!node)
		return;
	free(node->key);
	free(node->value);
	free(node);
}

static int	unset_next_node(char *key, t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		printf("Revisando nodo: %s\n", env->next->key);
		if (ft_strcmp(key, env->next->key) == 0)
		{
			printf("Encontrado: eliminando \"%s\"\n", env->next->key);
			tmp = env->next;
			env->next = tmp->next;
			free_node(tmp);
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	ft_unset(char **a, t_shell *data)
{
	t_env	*env;

	if (!a[1])
	{
		printf("unset: ninguna variable proporcionada\n");
		return (0);
	}

	printf("unset: intentando eliminar \"%s\"\n", a[1]);

	env = data->env;
	if (!env)
	{
		printf("unset: entorno vacío\n");
		return (0);
	}

	// Ver si es la primera
	if (ft_strcmp(a[1], env->key) == 0)
	{
		printf("unset: eliminando primer nodo \"%s\"\n", env->key);
		t_env *tmp = env->next;
		free_node(env);
		data->env = tmp;
		return (0);
	}

	return (unset_next_node(a[1], env));
}


