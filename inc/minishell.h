/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:54 by dlu               #+#    #+#             */
/*   Updated: 2023/06/20 16:18:18 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

# define PROMPT			" $> "
# define RC_FILE		"/.minishellrc"
# define HIST_FILE		"/.minishell_hist"
# define MAX_HIST_SIZE	1000
# define MAX_PATH_SIZE	1024
# define MAX_CMD_SIZE	1024
# define MAX_ARGS		10
# define TRUE			1
# define FALSE			0

/* Commands. */
# define EMPTY			0
# define PIPE			1
# define REDIR_IN		2
# define REDIR_OUT		3
# define REDIR_APPEND	4
# define REDIR_HERE		5
# define AND			6
# define OR				7
# define BUILTIN		8
# define CMD			9

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	**args;
	int		type;
	t_cmd	*root;
	t_cmd	*left;
	t_cmd	*right;
	char	*i_file;
	char	*o_file;
	int		o_type;
}	t_cmd;

/* Functions. */

int		input_validator(const char *str);
t_cmd	*input_lexer(char *line);

t_cmd	*parser(char **tokens);

int		executor(t_cmd *cmd, char * const envp[]);
int		redir_in(t_cmd *cmd, char * const envp[]);
int		redir_out(t_cmd *cmd, char * const envp[]);
int		redir_append(t_cmd *cmd, char * const envp[]);
int		redir_here(t_cmd *cmd, char * const envp[]);
int		builtin(t_cmd *cmd, char * const envp[]);

int		ft_echo(t_cmd *cmd, char * const envp[]);
int		ft_cd(t_cmd *cmd, char * const envp[]);
int		ft_pwd(t_cmd *cmd, char * const envp[]);
int		ft_export(t_cmd *cmd, char * const envp[]);
int		ft_unset(t_cmd *cmd, char * const envp[]);
int		ft_env(t_cmd *cmd, char * const envp[]);
int		exit_shell(t_cmd *cmd, char * const envp[]);

int		director(int ac, char **av, char **envp);
int		init_shell(void);
int		setup_terminal(struct termios *term_backup);
void	reset_terminal(struct termios *term_backup);
char	*build_prompt(void);
int		do_stuff(struct termios *term_backup);
void	gtfo(struct termios *term_backup, char *prompt);
void	reset_cmd_line(char *prompt, char *buff, int *i);

#endif
