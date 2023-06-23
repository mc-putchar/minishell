/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:54 by dlu               #+#    #+#             */
/*   Updated: 2023/06/23 18:10:36 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "control_sequences.h"
# include "format_output.h"
# include "lexer.h"
# include <stdbool.h>
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
# define RC_FILE		"/.mshrc"
# define HIST_FILE		"/.msh_hist"
# define MAX_HIST_SIZE	1000
# define MAX_PATH_SIZE	1024
# define MAX_CMD_SIZE	1024
# define MAX_ARGS		10
# define TRUE			1
# define FALSE			0

/* Commands. */

typedef struct s_cmd		t_cmd;
typedef struct s_cmdline	t_cmdline;
typedef struct s_shell		t_shell;

typedef struct s_cmd
{
	char	*args[MAX_ARGS]; // statically defined for now, may change to dynamic resize later
	int		type;
	t_cmd	*pipe;	// PIPE node will point to a cmd, each command will point to the next pipe
					// if NULL, standalone
	char	*i_file;
	char	*o_file;
	t_type	o_type; // APPEND / REDIR_OUT
	t_type	i_type; // HERE_DOC / REDIR_IN; seems like they can work simultaneously
}	t_cmd;

typedef struct	s_cmdline
{
	char		buff[BUFSIZ];
	char		*prompt;
	int			i;
	int			size;
	char		*hist;
}	t_cmdline;

typedef struct	s_shell
{
	char		**envp;
	t_list		*hist;
	int			hist_i;
	int			status;
	bool		parse_error;
	t_token		*parse_tok;
}	t_shell;

/* Global variable */
extern t_shell	g_shell;

/* Functions. */

/* Lexer / Parser. */

t_node	*new_node(t_type type);
t_token	*new_token(t_type type, char *value, t_token *prev);
t_node	*accept(t_type type);
bool	expect(t_type type);
bool	ft_ismeta(char c);

int		input_validator(const char *str);
t_token	*input_lexer(char *line);

t_cmd	*parser(char **tokens);

int		executor(t_cmd *cmd, char * const envp[]);
int		redir_in(t_cmd *cmd, char * const envp[]);
int		redir_out(t_cmd *cmd, char * const envp[]);
int		redir_append(t_cmd *cmd, char * const envp[]);
int		redir_here(t_cmd *cmd, char * const envp[]);
int		builtin(t_cmd *cmd, char * const envp[]);
char	*cmd_validator(t_cmd *cmd);

int		ft_echo(t_cmd *cmd, char * const envp[]);
int		ft_cd(t_cmd *cmd, char * const envp[]);
int		ft_pwd(t_cmd *cmd, char * const envp[]);
int		ft_export(t_cmd *cmd, char * const envp[]);
int		ft_unset(t_cmd *cmd, char * const envp[]);
int		ft_env(t_cmd *cmd, char * const envp[]);
int		exit_shell(t_cmd *cmd, char * const envp[]);

int		director(int ac, char **av, char **envp);
int		init_shell(void);
int		init_history(void);
int		flush_history(t_cmdline *cmdl);
int		write_history(int fd);
void	ctrl_up_history(t_cmdline *cmdl);
void	ctrl_down_history(t_cmdline *cmdl);
int		setup_terminal(struct termios *term_backup);
void	reset_terminal(struct termios *term_backup);
char	*build_prompt(void);
int		do_stuff(void);
void	gtfo(t_cmdline *cmdl);
void	reset_cmd_line(t_cmdline *cmdl);

#endif
