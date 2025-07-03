/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:27:36 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:27:38 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *token, t_token_type token_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(token);
	new_token->token_type = token_type;
	new_token->next = NULL;
	return (new_token);
}

t_token_type	get_token_type(char *token)
{
	if (is_command(token))
		return (T_COMMAND);
	if (token[0] == '-' && token[1] != '\0' && token[1] != '-')
		return (T_FLAG);
	if (is_redirect_in(token))
		return (T_REDIRECT_IN);
	if (is_redirect_out(token))
		return (T_REDIRECT_OUT);
	if (ft_strncmp(token, "|", 1) == 0)
		return (T_PIPE);
	return (T_ARGV);
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_token	*tokenize_input(char *input)
{
	char			**split_args;
	char			**temporal_strings;
	t_token			*tokens;
	t_token			*input_tokenizer;
	t_token_type	type;

	tokens = NULL;
	input_tokenizer = NULL;
	quotes_manage(input);
	split_args = ft_split(input, ' ');
	temporal_strings = split_args;
	if (!split_args)
		return (NULL);
	while (*split_args)
	{
		restore_quotes(*split_args);
		type = get_token_type(*split_args);
		input_tokenizer = create_token(*split_args, type);
		token_lstadd_back(&tokens, input_tokenizer);
		free(*split_args);
		split_args++;
	}
	free(temporal_strings);
	return (tokens);
}
