/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:32:13 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:32:16 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->argv = NULL;
	new_command->infile = NULL;
	new_command->outfile = NULL;
	new_command->heredoc = NULL;
	new_command->append = NULL;
	new_command->pipe = 0;
	new_command->next = NULL;
	return (new_command);
}

void	update_command(t_command *cmd, t_token *token)
{
	char	*value;
	char	**target;

	target = NULL;
	if (!token->next)
		return ;
	value = ft_strdup(token->next->value);
	if (!value)
		return ;
	if (token->token_type == T_REDIRECT_IN)
		target = &cmd->infile;
	else if (token->token_type == T_REDIRECT_OUT)
		target = &cmd->outfile;
	else if (token->token_type == T_APPEND)
		target = &cmd->append;
	else if (token->token_type == T_HEREDOC)
		target = &cmd->heredoc;
	if (target)
	{
		free(*target);
		*target = value;
	}
	else if (token->token_type == T_PIPE)
	{
		cmd->pipe = 1;
		free(value);
	}
}

void	add_args_command(t_command *command, char *token)
{
	int		i;
	int		j;
	int		count;
	char	**new_argv;

	i = 0;
	j = 0;
	count = 0;
	while (command->argv && command->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	while (i < count)
	{
		new_argv[i] = ft_strdup(command->argv[i]);
		i++;
	}
	new_argv[i++] = ft_strdup(token);
	new_argv[i] = NULL;
	while (j < count)
		free(command->argv[j++]);
	free(command->argv);
	command->argv = new_argv;
}

int	command_empty(t_command *command)
{
	return (!command->argv && !command->infile && !command->heredoc
		&& !command->outfile);
}

void	add_command_list(t_command **commands, t_command *new)
{
	t_command	*temporal;

	if (!new || command_empty(new))
	{
		free_command(new);
		return ;
	}
	if (!*commands)
	{
		*commands = new;
		return ;
	}
	temporal = *commands;
	while (temporal->next)
		temporal = temporal->next;
	temporal->next = new;
}
