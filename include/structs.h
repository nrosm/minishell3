/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:39:10 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/02 13:11:05 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	T_COMMAND,
	T_FLAG,
	T_ARGV,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
}						t_token_type;

typedef struct s_token
{
	t_token_type		token_type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	char				*heredoc;
	char				*append;
	int					pipe;
	struct s_command	*next;
}						t_command;

typedef struct s_job
{
	struct s_job		*previous;
	char				**cmd;
	char				**file;
	int					fd[2];
	pid_t				pid;
	struct s_job		*next;
}						t_job;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	int					history;
	int					exit;
	char				*input;
	t_env				*env;
	t_token				*tokens;
	t_command			*commands;
}						t_shell;

#endif
