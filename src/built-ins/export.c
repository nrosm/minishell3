/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:01:12 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 16:22:04 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

bool is_valid_env_var_key(char *var)
{
	int i = 0;

	if (!var || (ft_isalpha(var[i]) == 0 && var[i] != '_'))
		return false;
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return false;
		i++;
	}
	return true;
}

t_env *get_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}


bool set_env_var(t_shell *data, char *key, char *value)
{
	t_env *existing = get_env_var(data->env, key);
	t_env *new_node;

	if (existing)
	{
		free_ptr(existing->value);
		existing->value = ft_strdup(value);
		return true;
	}

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return false;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;

	if (!data->env)
	{
		data->env = new_node;
	}
	else
	{
		t_env *temp = data->env;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return true;
}

void free_str_tab(char **tab)
{
	int i = 0;

	if (!tab)
		return;
	while (tab[i])
	{
		free_ptr(tab[i]);
		i++;
	}
	free(tab);
}

static char **get_key_value_pair(char *argv)
{
	char **tmp;
	char *equal_sign = ft_strchr(argv, '=');

	if (!equal_sign)
		return NULL;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return NULL;

	tmp[0] = ft_substr(argv, 0, equal_sign - argv);
	tmp[1] = ft_strdup(equal_sign + 1);
	tmp[2] = NULL;
	return tmp;
}

int ft_export(t_shell *data, char **args)
{
	int i = 1;
	int ret = EXIT_SUCCESS;
	char **tmp;

	if (!args[i])
		return ft_env(data, NULL);

	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '='))
		{
			tmp = get_key_value_pair(args[i]);
			if (tmp && tmp[0])
				set_env_var(data, tmp[0], tmp[1]);
			free_str_tab(tmp);
		}
		i++;
	}
	return ret;
}
