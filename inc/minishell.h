/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:54 by dlu               #+#    #+#             */
/*   Updated: 2023/06/19 01:41:03 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "cmd_table.h"
# include "control_sequences.h"
# include "format_output.h"
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PROMPT				" $> "
# define RC_FILE			"/.minishellrc"
# define HIST_FILE			"/.minishell_hist"
# define MAX_HIST_SIZE		1000
# define MAX_PATH_SIZE		1024
# define MAX_CMD_SIZE		1024
# define MAX_ARGS			10

int			lexer(char *line);

t_cmd_table	*parser(char **tokens);

int			executor(t_cmd_table *cmd, char * const envp[]);
int			redir_in(t_cmd_table *cmd, char * const envp[]);
int			redir_out(t_cmd_table *cmd, char * const envp[]);
int			redir_append(t_cmd_table *cmd, char * const envp[]);
int			redir_here(t_cmd_table *cmd, char * const envp[]);
int			builtin(t_cmd_table *cmd, char * const envp[]);

int			ft_echo(t_cmd_table *cmd, char * const envp[]);
int			ft_cd(t_cmd_table *cmd, char * const envp[]);
int			ft_pwd(t_cmd_table *cmd, char * const envp[]);
int			ft_export(t_cmd_table *cmd, char * const envp[]);
int			ft_unset(t_cmd_table *cmd, char * const envp[]);
int			ft_env(t_cmd_table *cmd, char * const envp[]);
int			exit_shell(t_cmd_table *cmd, char * const envp[]);

int			director(int ac, char **av, char **envp);
int			init_shell(void);
int			setup_terminal(struct termios *term_backup);
void		reset_terminal(struct termios *term_backup);
char		*build_prompt(void);
int			do_stuff(struct termios *term_backup);
void		gtfo(struct termios *term_backup, char *prompt);
void		reset_cmd_line(char *prompt, char *buff, int *i);

#endif
