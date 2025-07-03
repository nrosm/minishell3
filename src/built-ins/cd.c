/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:17 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 17:12:41 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"
#include <limits.h>	// Para PATH_MAX
#include <unistd.h>	// Para getcwd, chdir
#include <stdio.h>	// Para perror

// Renombrada para mayor claridad
void	update_env_path(const char *key, const char *path, t_shell *env)
{
	char	*string;
	
	string = ft_strjoin(key, path);
	if (!string)
		return ;
	new_env(&env->env, string, NULL);
	free(string);
}

int	ft_cd(t_shell *env, char *arg)
{
	char	cwd[PATH_MAX];
	char	*home;

	if (arg == NULL)
	{
		home = get_env(env->env, "HOME");
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
		arg = home;
	}
	// Guardar el directorio actual antes de cambiar
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd (getcwd before)");
		return (1);
	}
	if (chdir(arg) == -1)
	{
		perror("cd");
		return (1);
	}
	update_env_path("OLDPWD=", cwd, env);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd (getcwd after)");
		return (1);
	}
	update_env_path("PWD=", cwd, env);
	return (0);
}
