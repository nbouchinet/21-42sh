/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:47:48 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 14:54:35 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H
# define ADD 65
# define SUS 66
# define CHK 67
# define FG  68
# define UPT 69
# define KILL 70
# define BG 71

pid_t					g_shell_pgid;
struct termios			g_shell_tmodes;
int						g_shell_terminal;
int						g_shell_is_interactive;
void					signal_handler(void);

typedef struct			s_process
{
	char				**argv;
	t_ast				*builtin;
	t_env				*env;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
	t_ast				*rdir;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	int					status;
	int					num;
	char				*command;
	struct s_process	*first_process;
	pid_t				pgid;
	char				notified;
	struct s_job		*next;
}						t_job;

typedef struct			s_jseq
{
	int					type;
	int					(*f)(t_ast**, t_env**, int);
}						t_jseq;

typedef struct			s_tab
{
	int					mod;
	int					(*f)(t_job**, t_ast**, t_job**);
}						t_tab;

typedef struct			s_bi
{
	char				*builtin;
}						t_bi;

typedef struct			s_fd
{
	int					fd;
	struct s_fd			*next;
}						t_fd;

/*
********************************************************************************
**                                   EXECUTION                                **
********************************************************************************
*/

int						job_ast(t_ast **ast, t_env **env, int foreground);
int						job_cmd_seq(t_ast **ast, t_env **env, int foreground);
int						job_qm_seq(t_ast **ast, t_env **env, int foreground);
int						job_oa_seq(t_ast **ast, t_env **env, int foreground);
int						job_andor(t_ast **ast, t_env **env, int foreground);
int						job_bg_seq(t_ast **ast, t_env **env, int foreground);
int						return_exec(int status);
int						exec_job(t_job **job, t_env **env, int fg);
int						job_pipe(t_ast **ast, t_env **env, int fg);
int						pipe_job(t_job **lst, t_env **env, int fg);
int						exec_pro(t_process **lst, t_env **env, t_job **j);
int						pipe_fg(t_process **process, pid_t *pgid, char **env,
						int r);
int						cont_pipe_fg(t_process **pro, pid_t *pgid, char **env,
						int *fd);
int						exec_pro_bg(t_process **pro, t_env **env, t_job **job);
int						pipe_bg(t_process **process, pid_t *pgid, char **env,
						int r);
int						cont_pipe_bg(t_process **pro, pid_t *pgid, char **env,
						int *fd);
void					init_fork(pid_t *pgid, int fg);
void					init_father(pid_t *pid, pid_t *pgid, int fg);
void					exec_fork(t_process **process, char **env, int r);
int						io_seq(t_ast **ast, int mod);
int						bgre(t_ast **ast, int mod);
int						wtf_rdir(t_ast **ast, int mod);
int						bdir(t_ast **ast, int mod);
int						agre(t_ast **ast, int mod);
int						bbdir(t_ast **ast, int mod);
void					stock_restore(int mod);
void					close_rdir(int fd, int mod);
void					close_fd(t_fd **lst);
int						find_fd(int fd, t_fd **lst);
int						test(char *s);
int						check_equal(char *s);
int						check_io(char *tmp);
int						valid_fd(char *str);
int						dup_fd(char *std, char *fd, int type);
/*
******************************** CREATE JOB ************************************
*/
int						init_job(t_job **job);
int						init_proc(t_process **process);
int						init_process(t_ast **ast, t_process **p, t_env **env);
int						complete_process(t_ast **ast, t_process **p,
						t_env **env);
int						check_builtin(t_ast **ast, t_process **p, t_env **env);
char					*init_job_name(t_ast **ast);
char					*init_pipe_job(t_ast **ast);
char					*init_rdir(char **cmd, t_ast **ast);
char					*rdir_print(int type);
char					**creat_argv(t_ast **ast);
int						check_type_bin(t_ast **ast, t_env **env);
int						check_abs_bin(char *str);
int						check_rlt_bin(char **str, t_env **env);
int						exist_bin(char **str, char *value);
int						check_file(DIR *dir, char *directory, char **str);
int						isnt_dot(char *file, char *str);
int						nbr_arg(t_ast **ast);
int						print_error(int err, char *str);
int						delete_job(t_job **job);
t_env					*find_node(t_env **env, char *var, char *value);
char					**get_env(t_env **lst, char *s);
void					increase_shlvl(t_env **env);
void					reduc_shlvl(t_env **env, char *s);
char					*var_value(int i, char *var, char *value);
void					addvalue(t_env **env, char *str);
int						seak(char *s);
int						countnode(t_env *env);
/*
********************************* JOB CONTROL **********************************
*/
int						job_control(t_job **job, t_ast **ast, int mod);
int						ft_joblstadd(t_job **new, t_ast **ast, t_job **table);
int						check_job(t_job **job, t_ast **ast, t_job **table);
int						update_status(t_job **job, t_ast **ast, t_job **table);
int						builtin_job(t_job **job, t_ast **ast, t_job **table);
int						job_is_stopped(t_job *j);
int						job_is_complete(t_job *j);
int						mark_job_status(t_job **job, int status, pid_t pid);
int						mark_job_as_stopped(t_job **job);
int						mark_process_status(t_job **job);
void					job_len(t_job **j, t_job **table, int *len);
void					print_job_message(t_job **j, int *len, int *pos);
int						inter_job(t_ast **ast, t_env **env);
void					relink(t_process **tmp, t_process **del);
void					delete_tnode(t_job **node, t_job **prev, t_job **table);
int						delete_process(t_process **head, t_process **prev,
						t_process **process);
int						check_kill(t_job **job);
void					catch_error(t_job **job, int status);
#endif
