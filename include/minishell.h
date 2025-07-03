/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:39:21 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:34 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>

// Init program
t_command	*init_commands(void);
t_token		*init_tokens(void);
t_env		*init_env(void);
t_shell		*init_minishell(void);

// enviroment
char		*get_key(char *env);
char		*get_value(char *env);
char		*get_env(t_env *env, const char *key);
void		new_env(t_env **env, char *key, char *value);
void		get_variables(t_env **env, char **envp);

// built-ins
int			ft_echo(char **args);
int			ft_unset(char **a, t_shell *data);
int	        ft_env(t_shell *data, char **args);
int			ft_pwd(void);
int			ft_cd(t_shell *env, char *arg);
int			ft_export(t_shell *data, char **args);
void	    ft_exit(char **arg, t_command *cmd, t_shell *shell);

// clean args
char		*remove_spaces(char *input);
void		normalize_spaces(char *input);
void		quotes_manage(char *input);
void		restore_quotes(char *input);
void		pre_process(t_shell *shell);

// tokenizer
int			is_command(char *token);
int			is_redirect(char *input);
int			is_redirect_in(char *input);
int			is_redirect_out(char *input);
t_token		*create_token(char *token, t_token_type token_type);
t_token		*tokenize_input(char *input);

// Parser
t_command	*create_command(void);
void		update_command(t_command *command, t_token *token);
void		add_args_command(t_command *command, char *token);
int			command_empty(t_command *command);
void		add_command_list(t_command **commands, t_command *new);
int			can_execute(t_token *tokens);
void		parser(t_command **commands, t_token *tokens);
char	*remove_quotes(const char *arg);
void clean_arguments(t_command *cmd);

// redirect
int			redirect_input(const char *filename);
int			redirect_output(const char *filename);
int			redirect_output_append(const char *filename);
int			handle_heredoc(const char *delimiter);
int			handle_redirection(const char *operator, const char *target);

// Free memory
void		free_env_list(t_env *env);
void		free_tokens(t_token *tokens);
void		free_command(t_command *commands);
void		free_command_list(t_command *commands);
void		free_minishell(t_shell *minishell);

// Executer
void		init_signals(void);
int			exec_builtin(t_shell *shell, t_command *command);
char		*filter_path(t_env *envp, char *key);
int			executor(t_shell *shell);
int			is_shell_builtin(char *cmd);
int			exec_builtin_parent(t_shell *shell, t_command *command);


// Utils
char		*ft_strjoin_free(char *s1, char *s2, int mode);
char		**env_list_to_array(t_env *envp);
void		ft_free_array(char **array);
int			only_execute(t_shell *shell, t_command *command, t_env *envp);

// error
char	*join_strs(char *str, char *add);
void	free_ptr(void *ptr);
int	errmsg_cmd(char *command, char *detail, char *error_message, int error_nb);
void	errmsg(char *errmsg, char *detail, int quotes);
bool	usage_message(bool return_val);

#endif
