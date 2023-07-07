/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:12:54 by dlu               #+#    #+#             */
/*   Updated: 2023/07/07 12:39:31 by mcutura          ###   ########.fr       */
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
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PROMPT			" $> "
# define RC_FILE		"/.mishrc"
# define HIST_FILE		"/.mish_hist"
# define HERE_DOC_FILE	"/tmp/.mish_here_doc"
# define MISH			"🐭"
# define MAX_HIST_SIZE	1000
# define MAX_PATH_SIZE	1024
# define MAX_CMD_SIZE	1024
# define MAX_ENV		4096
# define MAX_ARG_E		8192
# define WC_CHAR		128

/* Commands. */

typedef struct s_cmd		t_cmd;
typedef struct s_cmdline	t_cmdline;
typedef struct s_shell		t_shell;
typedef struct termios		t_termios;
extern t_shell				g_shell;

typedef struct s_cmdline
{
	char		buff[BUFSIZ];
	int			i;
	int			size;
	char		*hist;
}	t_cmdline;

typedef struct s_shell
{
	char		**envp;
	t_list		*hist;
	int			hist_i;
	int			status;
	bool		parse_error;
	t_token		*tok;
	t_token		*tok_head;
	t_cmd		*ast;
	t_cmdline	*cmdl;
	t_termios	*term_backup;
}	t_shell;

/* Lexer & Parser. */
bool	ft_ismeta(char c);
bool	ft_isop(char *s);
bool	accept(t_type type);
bool	expect(t_type type);
bool	expect_redir(void);
bool	load_redir(t_cmd *node);
bool	input_validator(const char *str);
void	free_token(t_token *token);
void	free_cmd_ast(t_cmd *root);
t_token	*input_lexer(char *line);
t_token	*new_token(t_type type, char *value, t_token *prev);
t_cmd	*new_cmd(t_type type);
t_cmd	*build_conditional(void);
t_cmd	*build_pipeline(void);
t_cmd	*build_command(void);

/* Execution. */
int		parse_execute(char *line);
int		executor(t_cmd *cmd);
int		pipex(t_cmd *cmd);
int		invalid_command(t_cmd *cmd);
int		wildcard_expansion(char **args, char *format, int i);
char	*cmd_path(char *cmd);
char	**cmd_expansion(char **args);
char	*arg_expansion(char *arg);
bool	redir_setup(t_cmd *cmd);
int		here_doc(t_cmd *cmd);

/* Builtins. */
void	backup_stdfds(int fd[2]);
void	restore_stdfds(int fd[2]);
int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_cmd *cmd);
int		builtin_pwd(t_cmd *cmd);
int		builtin_export(t_cmd *cmd);
int		builtin_unset(t_cmd *cmd);
int		builtin_env(t_cmd *cmd);
int		builtin_exit(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd);
bool	is_builtin(t_cmd *cmd);
void	replace_env(char *key, char *replace);
char	*ft_getenv(char *name);
int		ft_setenv(char *name, char *value, int overwrite);

/* Director. */
int		director(void);
int		init_history(void);
int		flush_history(t_cmdline *cmdl);
int		write_history(int fd);
void	ctrl_up_history(t_cmdline *cmdl, char *prompt);
void	ctrl_down_history(t_cmdline *cmdl, char *prompt);
int		setup_terminal(t_termios *term_backup);
void	reset_terminal(t_termios *term_backup);
int		print_prompt(char *prompt);
char	*read_line(char *prompt);
int		do_stuff(void);
void	gtfo(t_cmdline *cmdl, int status);
void	reset_cmd_line(t_cmdline *cmdl, char *prompt);

/* Debugging tools. */
void	ast_display(t_cmd *node, int level);
void	tokens_print(t_token *start);

#endif
