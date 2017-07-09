/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:35:36 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/09 15:31:06 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#define C	1
#define D	2
#define A	4
#define N	8
#define R	16
#define W	32
#define P	64
#define S	128
#define HIS_USAGE 	"history: usage: history [-c] [-d offset] [n] or "\
					"history -awrn [filename] or history -ps arg [arg...]\n"
#define HIS_MSG		"history position out of range"

/*
********************************************************************************
**                                   EXECUTION                                **
********************************************************************************
*/
typedef struct		s_rdir
{
	int				t;
	int				(*f)(t_ast**);
}					t_rdir;

typedef struct		s_cmd
{
	char			*cmd;
	int				(*f)(t_ast**, t_env**);
}					t_cmd;

typedef struct		s_seq
{
	int				type;
	int				(*f)(t_ast**, t_env**, int);
}					t_seq;

void				exec_ast(t_ast **ast, t_env **env);
int					exec_cmd_seq(t_ast **ast, t_env **env, int type);
int					exec_bina(t_ast **ast, t_env **env, int r, int type);
int					qm_seq(t_ast **ast, t_env **env, int type);
int					exec_oa(t_ast **ast, t_env **env, int type);
void				cmd_seq(t_ast **ast, t_env **env);
void				pipe_seq(t_ast **ast, t_env **env, int i);
void				rlt_cmd(t_ast **ast, t_env **env);
void				abs_cmd(t_ast **ast, t_env **env);
void				execution(char **arg, char **env, t_ast **rdir);
int					io_seq(t_ast **ast);
int					wtf_rdir(t_ast **ast);
int					bdir(t_ast **ast);
int					agre(t_ast **ast);
char				**creat_arg(t_ast **ast, char *cmd);
int					find_cmd_bin(t_ast **ast, char **path);
char				*binary_find(char *cmd, char **path);
int					find_bin(t_ast **ast);
int					count_arg_node(t_ast **ast);
char				*create_path(char *env, char *cmd);
int					binary_finder(char *path, char *cmd);
int					ft_checkbin(DIR *dir, char *cmd);
char				*get_dir(char *cmd);
int					isexec(char *path);
char				**get_env(t_env **lst, char *s);
void				increase_shlvl(t_env **env);
void				reduc_shlvl(t_env **env, char *s);
char				*var_value(int i, char *var, char *value);
int					seak(char *s);
void				addvalue(t_env **env, char *str);
int					countnode(t_env *env);
void				cont_pipe(t_ast **ast, t_env **env, int *p);
void				ft_putast(t_ast *root);
t_env				*find_node(t_env **env, char *var, char *value);
/*
*************************************BUILT-IN***********************************
*/
int					ft_setenv(t_ast **ast, t_env **env);
void				add_env(t_env **env, char **arg);
void				add_var(t_env **env, char *var, char *value);
int					ft_unsetenv(t_ast **ast, t_env **env);
int					ft_env(t_ast **ast, t_env **env);
char				**creat_arg_env(t_ast **ast);
void				deletevarenv(t_env **lst, char *var);
int					countab(char **tob);
void				deletefirstnode(t_env **lst);
void				deletevar(t_env **tmp, t_env *prev);
void				freenode(t_env *node);
t_env 				*lst_at(t_env **env, char *cmp);
int     			ft_cd(t_ast **ast, t_env **env);
int					ft_echo(t_ast **ast, t_env **env);
int					ft_exit(t_ast **ast, t_env **env);
int					ft_history(t_ast **ast, t_env **env);

/*
*************************************HASHING***********************************
*/
# define BUILTIN 64
# define PUT 65
# define FIND 66

typedef struct		s_hash
{
	int				abs_key;
	int				rlt_key;
	int				hits;
	char			*path;
	struct s_hash	*next;
}					t_hash;

typedef struct		s_mod
{
	int				mod;
	int				(*f)(t_ast**, t_hash**);
}					t_mod;

int		init_hash(t_hash **lst, char *cmd);
int		hashing(t_ast **ast, t_env **env);
int		builtin_hash(t_ast **ast, t_hash **table);
int		hash(t_ast **ast, int mod);
int		search_mod(t_ast **ast, t_hash **table);
int		put_cmd(t_ast **ast, t_hash **table);
int		search(t_ast **ast, t_hash **table, int i);
int		find_search(t_ast **ast, t_hash **table);
int		hash_cmd(char *cmd);
void	remove_cmd(t_ast **ast, t_hash **table);
void	clean_cmd(t_hash **table, t_hash **prev, t_hash **curr);
int		count_opt(t_ast **ast);
int		check_opt(char *opt);

/*
********************************************************************************
**                                  INIT_ENV                                  **
********************************************************************************
*/
int					init_env(t_env **lst, char **env);
void				ft_freetab(char **trash);
void				print_env(t_env *lst);
void				delete_lstenv(t_env **cmd);
char				**check_env(char **env);
#endif
