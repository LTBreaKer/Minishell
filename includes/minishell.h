/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:01:31 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/22 20:29:45 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "get_next_line.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_stack
{
	char			c;
	struct s_stack	*next;
}					t_stack;

typedef struct s_lex
{
	char			*deleted;
	char			**splited2;
	char			**sub_split;
	char			*line;
	int				i;
	int				j;
	int				k;
	int				dol;
	int				idx;
	int				space_exist;
	int				here;
	int				len;
	int				sq;
	int				dq;
	int				id;
	int				ambg;
	char			*target;
	char			*value;
	char			*full_cmd;
	char			*full_heredoc;
	char			*new_line_tmp;
	char			*new_line_join;
	char			*tmp;
	int				idx_stx;
}					t_lex;
//----------------------------------//

typedef struct s_envp
{
	char			*var;
	char			*value;
	struct s_envp	*next;
}					t_env;

typedef struct s_export
{
	char			*var;
	struct s_export	*next;
}					t_export;

struct				s_env
{
	int				status;
	t_env			*env;
	t_export		*export;
	int				*pid;
	int				h_id;
	int				cmd_count;
	char			*line;	
};

typedef struct s_cmd
{
	char			**heredoc;
	int				*herepipe;
	int				in;
	int				out;
	int				wf;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

struct s_env		g_env;

//extern struct s_env	g_env;

void				rl_replace_line(const char *s, int clear_undo);
void				ft_print(void);
void				ft_pwd(void);
int					ft_cd(char *dir);
void				ft_env(void);
void				ft_echo(t_cmd *cmd);
void				ft_exit(char **args, int check);
int					ft_unset(char **args);
t_env				*ft_lstnew(char *var, int f);
t_env				*ft_lstadd_back(t_env **env, t_env *new);
void				ft_export(char **var);
t_export			*ft_lstnew_export(char *var);
void				ft_lstadd_back_export(t_export **export, t_export *new);
void				ft_lstadd_after_last(t_env **env, t_env *new);
void				ft_lstremove(t_export **export, char *var);
char				*ft_trim(char *str);
int					ft_change_elem(char *var, char *value);
void				ft_lstadd_after_last(t_env **env, t_env *new);
char				*ft_get_value(char *var);
void				ft_env_remove(t_env **env, char *var);
int					count_cmd(t_cmd *cmd);
void				ft_error(char *str);
char				**get_var(char *var);
int					heredoc(t_cmd *cmd);
int					ft_execute(t_cmd *cmd, char **envp);
void				sigint_handler(int sig);
void				sigquit_handler(int sig);
char				*here_expand(char *s);

//-----------------PARSING-----------------//

void				make_env(char **envp);
void				free_split(char **splited);
char				*ft_get_value(char *var);
int					lex(t_lex *g);
char				*lst_to_str(t_stack *lst);
int					quotes_check(t_lex *g);
char				*syntax_check(t_lex *g);
int					ft_lstsize(t_stack *lst);
t_stack				*ft_lstnew2(char c);
void				add_push(t_stack **lst, char c);
void				free_lst(t_stack *lst);
void				ft_lstadd_front(t_stack **lst, t_stack *new);
void				fill_the_list(t_lex *g, t_cmd **lst_final);
void				expand_me(t_lex *g);
void				clean_me(t_lex *g, char **args);
int					check_dash_n(char *str);
t_cmd				*ft_lstfinalnew(void);
void				ft_lstadd_backfinal(t_cmd **env, t_cmd *new);
void				fill_in(t_lex *g, t_cmd *new);
void				open_in(t_lex *g, t_cmd *new);
void				fill_out(t_lex *g, t_cmd *new);
void				open_out(t_lex *g, t_cmd *new, char **str);
void				fill_append(t_lex *g, t_cmd *new);
void				fill_heredoc(t_lex *g, t_cmd *new);
int					ambig_check(char c, char *s);
void				quotes_check_helper(t_lex *g);
char				*red_syntax_helper3(t_lex *g, int i);
char				*red_syntax_helper2(t_lex *g);
void				red_syntax_helper(t_lex *g);
char				*pipe_syntax_helper(t_lex *g);
char				*clean_quotes(t_lex *g, char *s);
char				*clean_quotes2(char *s);
void				trimer(t_lex *g);
void				f_mbig(t_lex *g, t_cmd *new, int i);
void				ftlist_helper(t_lex *g, t_cmd *new);
void				fill_args_helper(t_lex *g, t_cmd *new);
void				fill_args_helper2(t_lex *g);
char				*xpanterrogation(char *s, int dol);
char				*dol_dol(char *target, char *s, int dol);
char				*null_val(char *target, char *s, int dol, int len);
char				*normal_case(char *value, char *s, int dol, int len);
char				*dol_zero(char *target, t_lex *g, char *s);
int					qchecker(char *s, char c, int start, int end);
int					xpnd_help(char *s, int i, int *index, char c);
int					xpnd_in_loop(char *s, int i, int *index);
char				*get_target(char *s, int idx);
void				shifting(char **args, int j);
char				*put_stx_idx(t_lex *g, char *ret, int i);
void				clone_top(t_lex *g, t_cmd *new, t_cmd **lst);
#endif
