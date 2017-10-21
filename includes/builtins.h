/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:35:36 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 14:55:52 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*
********************************************************************************
**                                   BUILTIN                                  **
********************************************************************************
*/

typedef struct		s_rdir
{
	int				t;
	int				(*f)(t_ast**, int);
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

/*
********************************* HASH TABLE ***********************************
*/
# define BUILTIN 64
# define PUT 65
# define FIND 66
# define CLEAN 67

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
	int				(*f)(t_ast**, t_job **, t_hash**);
}					t_mod;

int					hash(t_ast **ast, t_job **job, int mod);
int					put_cmd(t_ast **ast, t_job **job, t_hash **table);
int					find_table(t_job **job, t_hash **table);
int					search(t_ast **ast, t_hash **table, int i);
int					search_mod(t_ast **ast, t_hash **table);
int					clean_table(t_ast **ast, t_job **job, t_hash **table);
int					clear_table(t_hash **table);
int					reset_table(t_hash **table);
void				print_hash(t_hash **table);
int					builtin_hash(t_ast **ast, t_job **job, t_hash **table);
int					clean_hash(t_ast *ast, t_job **job, t_hash **table);
int					hash_cmd(char *cmd);
int					hashing(t_ast **ast, t_env **env);
int					find_search(t_ast **ast, t_job **job, t_hash **table);
int					count_opt(t_ast **ast);
int					check_opt(char *opt);
int					init_hash(t_hash **lst, char *cmd);
/*
******************** ENV SETENV UNSETENV UNSET EXPORT LOCAL ********************
*/
# define LOW_I_FLAG	1

int					builtin_env(t_ast **ast, t_env **env);
int					env_builtin(t_ast **ast, t_env **env, t_env **r_env);
int					env_builtin_pipe(t_ast **ast, t_env **env, t_env **r_env);
t_ast				*new_env(t_env **n_env, t_ast **ast, t_env **env, int flag);
t_ast				*complete_env(t_env **env, t_ast **ast);
int					exec_env(t_ast **ast, t_env **env, t_env **r_env);
void				recreat_ast(t_ast **n_ast, t_ast **ast);
void				change_env(t_env **env, char *var);
t_ast				*env_w(t_env **env, t_ast **ast);
t_ast				*env_without(t_env **env, t_ast **ast);
int					pipe_builtin(t_ast **ast, t_env **env, int foreground);
int					env_pipe(t_ast **ast, t_env **env);
int					exec_env_pipe(t_ast **ast, t_env **env, t_env **r_env);
int					exec_job_pipe(t_job **job, t_env **env, int foreground);
int					exec_pro_pipe(t_process **p, t_env **env, t_job **job);
void				complete_node(t_env **node, char *env);
void				init_env_ast(t_ast **ast, char *str, int type);
t_env				*next_node(t_env **env);
t_ast				*env_option(t_ast **ast, int *flags);
void				env_opt(char *str, int *flags);
int					print_error_env(int err, char *str);
int					init_env(t_env **lst, char **env);
void				ft_freetab(char **trash);
void				print_env(t_env *lst);
void				delete_lstenv(t_env **cmd);
int					ft_setenv(t_ast **ast, t_env **env);
void				add_env(t_env **env, char **arg);
void				replace_value(t_env **node, char *str);
void				add_var(t_env **env, char *var, char *value);
int					ft_unsetenv(t_ast **ast, t_env **env);
char				**creat_arg_env(t_ast **ast);
int					countab(char **tob);
void				deletevarenv(t_env **lst, char *var);
void				deletefirstnode(t_env **lst);
void				freenode(t_env *node);
int					ft_unset(t_ast **ast, t_env **env);
int					ft_export(t_ast **ast, t_env **env);
int					local(char *str);
int					put_into_lst(char *str, char *sub);

/*
*********************************** HISTORY ************************************
*/
typedef struct		s_hist
{
	int				op;
	void			(*f)(t_his **his, int offset, int len, char *arg);
}					t_hist;

# define C	1
# define D	2
# define A	4
# define N	8
# define R	16
# define W	32
# define P	64
# define S	128
# define HU1	"history: usage: history [-c] [-d offset] [n] or "
# define HU2	"history -awrn [filename] or history -ps arg [arg...]\n"
# define HO	"invalid option"

int					ft_history(t_ast **ast, t_env **env);
void				run_his(char *arg, int opt, int offset, int his_len);
void				hist_append(t_his **his, int offset, int his_len,
					char *arg);
void				hist_read(t_his **his, int offset, int his_len, char *arg);
void				hist_add(t_his **his);
void				hist_session(void);
void				hist_write(t_his **his, int offset, int his_len, char *arg);
void				hist_sarg(t_his **his, int offset, int his_len, char *arg);
int					get_history_arg(t_ast **tmp, char **arg);
void				hist_clear(t_his **his, int offset, int his_len, char *arg);
/*
************************************ READ **************************************
*/
# define AR	1
# define DR	2
# define NR	4
# define PR	8
# define RR	16
# define SR	32
# define TR	64
# define UR	128
# define RU1	"read: usage: read [-ers] [-u fd] [-t timeout] [-p prompt]"
# define RU2	"[-a array] [-n nchars] [-d delim] [name ...]"

typedef struct		s_read
{
	char			*delim;
	char			*local;
	char			*stack;
	int				opt;
	int				nchars;
	time_t			time;
	time_t			endwait;
	int				fd;
	int				eot;
}					t_read;

typedef struct		s_opt
{
	char			c[2];
	int				(*f)(t_read *var, char **arg, int *i, int j);
}					t_opt;

int					ft_read(t_ast **ast, t_env **env);
int					read_input(t_read *var, int i, int nchar, char buf[]);
void				handle_c(int sig);
void				save_input(t_read *var);
int					silent(t_read *var, char **arg, int *i, int j);
int					fd(t_read *var, char **arg, int *i, int j);
int					rtimeout(t_read *var, char **arg, int *i, int j);
int					error_msg(char c);
int					back_slash(t_read *var, char **arg, int *i, int j);
int					prompt(t_read *var, char **arg, int *i, int j);
int					nchars(t_read *var, char **arg, int *i, int j);
int					delim(t_read *var, char **arg, int *i, int j);
int					aname(t_read *var, char **arg, int *i, int j);
/*
********************************** CD ECHO EXIT ********************************
*/
int					ft_cd(t_ast **ast, t_env **env);
int					just_norme(struct stat *st, t_ast *tmp, char **path,
					int opt);
void				mod_env(t_env **env, char *path, char *save);
char				*construct_path(t_env **env, char *save, char *path);
int					ft_echo(t_ast **ast, t_env **env);
int					ft_exit(t_ast **ast, t_env **env);
int					set_exiting_value(t_cmdl **cmdl, int r_value);
/*
************************** FOREGROUND & BACKGROUNG *****************************
*/
int					ft_fg(t_ast **ast, t_env **env);
int					ft_bg(t_ast **ast, t_env **env);
int					foreground(t_job **job, t_ast **ast, t_job **table);
int					background(t_job **job, t_ast **ast, t_job **table);
t_job				*find_pgid(t_job **table, t_ast **ast);
void				mark_job_as_running(t_job **job);
void				wait_for_job(t_job **job);
#endif
