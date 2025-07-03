/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:54 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 16:31:12 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static void	apply_redirs(t_command *command)
{
	if (command->infile)
		redirect_input(command->infile);
	if (command->outfile)
		redirect_output(command->outfile);
	if (command->append)
		redirect_output_append(command->append);
	if (command->heredoc)
		handle_heredoc(command->heredoc);
}

char	*filter_path(t_env *envp, char *key)
{
	size_t	length;

	if (!envp || !key)
		return (NULL);
	length = ft_strlen(key);
	while (envp)
	{
		if (envp->key && ft_strncmp(envp->key, key, length) == 0)
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (NULL);
}

static char	*find_executable(char *command, t_env *envp)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = filter_path(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, command, 1);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (ft_free_array(paths), NULL);
}

int	only_execute(t_shell *shell, t_command *command, t_env *envp)
{
	pid_t	pid;
	int		status;
	char	*full_path;
	char	**env_array;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		apply_redirs(command);
		if (is_command(command->argv[0]))
			exit(exec_builtin(shell, command));
		full_path = find_executable(command->argv[0], envp);
		if (!full_path)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			exit(127);
		}
		env_array = env_list_to_array(envp);
		execve(full_path, command->argv, env_array);
		perror("execve");
		ft_free_array(env_array);
		free(full_path);
		exit(126);
	}
	else
		return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}

int	executor(t_shell *shell)
{
	t_command	*command;
	int			save_stdin;
	int			save_stdout;

	command = shell->commands;
	while (command)
	{
		if (command->pipe == 1 && command->next)
			return (1);
		if (is_command(command->argv[0]))
		{
			save_stdin = dup(STDIN_FILENO);
			save_stdout = dup(STDOUT_FILENO);
			apply_redirs(command);
			exec_builtin(shell, command);
			dup2(save_stdin, STDIN_FILENO);
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdin);
			close(save_stdout);
		}
		else
			only_execute(shell, command, shell->env);
		command = command->next;
	}
	return (1);
}