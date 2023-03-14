/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:01:31 by aharrass          #+#    #+#             */
/*   Updated: 2023/03/13 16:38:09 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

typedef struct s_stack
{
	char			c;
	struct s_stack	*next;
}					t_stack;

typedef struct s_lex
{
	int				i;
	int				j;
	int				k;
	int				idx;
	int				space_exist;
	int				here;
	int				len;
	int				sq;
	int				dq;
	int				id;
	char			**splited1;
	char			**splited2;
	char			**sub_split;
	char			*line;
	char			*new_line_tmp;
	char			*new_line_join;
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
	int				cmd_count;
};

typedef struct s_cmd
{
	char			**heredoc;
	int				in;
	int				out;
	int				err;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

struct s_env		g_env;

//extern struct s_env	g_env;

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
int					ft_execute(t_cmd *cmd, char **envp);

//-----------------PARSING-----------------//

void				make_env(char **envp);
void				free_sub_split(char **splited);
char				*ft_get_value(char *var);
int					lex(t_lex *g);
char				*lst_to_str(t_stack *lst);
void				ft_transfert(t_lex *g);
int					quotes_check(t_lex *g);
char				*syntax_check(t_lex *g);
int					ft_lstsize(t_stack *lst);
t_stack				*ft_lstnew2(char c);
void				add_push(t_stack **lst, char c);
void				free_lst(t_stack *lst);
void				ft_lstadd_front(t_stack **lst, t_stack *new);
void				fill_the_list(t_lex *g, t_cmd **lst_final);
void				expand_me(t_lex *g, char **args);
#endif
