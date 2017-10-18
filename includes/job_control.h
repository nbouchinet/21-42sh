/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:47:48 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/18 14:13:42 by zadrien          ###   ########.fr       */
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

int						job_ast(t_ast **ast, t_env **env, int foreground);
int						job_cmd_seq(t_ast **ast, t_env **env, int foreground);
int						exec_job(t_job **job, t_env **env, int foreground);
int						job_bg_seq(t_ast **ast, t_env **env, int foreground);
int						exec_bg_seq(t_ast **ast, t_env **env);
int						exec_job_bg(t_job **job, t_env **env);
void					job_cont_bg(t_process **lst, char **env,
						t_job **job, int *p);
int						job_qm_seq(t_ast **ast, t_env **env, int foreground);
int						job_oa_seq(t_ast **ast, t_env **env, int foreground);
int						job_andor(t_ast **ast, t_env **env, int foreground);
void					catch_error(t_job **job, int status);
char					*rdir_print(int type);
char					*init_rdir(char **cmd, t_ast **ast);
char					*init_job_name(t_ast **ast);
char					*init_pipe_job(t_ast **ast);
int						init_job(t_job **job);
int						init_proc(t_process **process);
int						check_builtin(t_ast **ast, t_process **p, t_env **env);
int						init_process(t_ast **ast, t_process **proc,
						t_env **env);
int						complete_process(t_ast **ast, t_process **p,
						t_env **env);
int						delete_job(t_job **job);
int						builtin_env(t_ast **ast, t_env **env);
int						env_builtin(t_ast **ast, t_env **env, t_env **r_env);
t_ast					*new_env(t_env **n_env, t_ast **ast, t_env **env,
						int flag);
t_ast					*complete_env(t_env **env, t_ast **ast);
t_env					*next_node(t_env **env);
int						find_rlt(t_ast **cmd, t_env **env);
char					*recreat_cmd(t_ast **ast);
t_ast					*env_option(t_ast **ast, int *flags);
void					env_opt(char *str, int *flags);
t_ast					*env_without(t_env **env, t_ast **ast);
t_ast					*env_w(t_env **env, t_ast **ast);
void					change_env(t_env **env, char *var);
int						exec_env(t_ast **ast, t_env **env, t_env **r_env);
void					wait_for_job(t_job **job);
void					mark_job_as_running(t_job **job);
t_job					*find_pgid(t_job **table, t_ast **ast);
int						background(t_job **job, t_ast **ast, t_job **table);
int						foreground(t_job **job, t_ast **ast, t_job **table);
int						new_abs_cmd(t_ast **ast);
int						new_rlt_cmd(t_ast **ast, t_env **env);
int						rlt_ou_abs(t_ast **ast, t_env **env);
char					**creat_arg_process(t_ast **ast, t_env **env);
void					set_pgid(pid_t pid, pid_t *pgid, int foreground);
void					set_pid(pid_t pid, pid_t *pgid, int foreground);
void					active_sig(pid_t pid, pid_t pgid, int foreground);
int						exec_pro(t_process **lst, t_env **env, t_job **j);
int						exec_pro_bg(t_process **pro, t_env **env, t_job **job);
void					creat_file(t_tok **lst);
int						heredoc(t_tok **lst);
int						next_hd(t_tok **tok);
int						hd_loop(t_tok **stop, t_cmdl *cmdl, int p[2], int i);
int						inter_job(t_ast **ast, t_env **env);
void					relink(t_process **tmp, t_process **del);
void					delete_tnode(t_job **node, t_job **prev, t_job **table);
int						job_control(t_job **job, t_ast **ast, int mod);
int						ft_joblstadd(t_job **new, t_ast **ast, t_job **table);
int						update_status(t_job **job, t_ast **ast, t_job **table);
int						check_job(t_job **job, t_ast **ast, t_job **table);
int						builtin_job(t_job **job, t_ast **ast, t_job **table);
int						job_is_stopped(t_job *j);
int						job_is_complete(t_job *j);
int						mark_job_status(t_job **job, int status, pid_t pid);
int						mark_job_as_stopped(t_job **job);
int						mark_process_status(t_job **job);
int						check_equal(char *s);
int						test(char *s);
int						job_pipe(t_ast **ast, t_env **env, int foreground);
int						pipe_job(t_job **lst, t_env **env, int foreground);
void					stock_restore(int mod);
int						ft_fg(t_ast **ast, t_env **env);
int						ft_bg(t_ast **ast, t_env **env);
int						return_exec(int status);
int						print_error(int err, char *str);
int						check_type_bin(t_ast **ast, t_env **env);
int						check_abs_bin(char *str);
int						check_file(DIR *dir, char *directory, char **str);
int						exist_bin(char **str, char *value);
int						check_rlt_bin(char **str, t_env **env);
int						nbr_arg(t_ast **ast);
char					**creat_argv(t_ast **ast);
int						pipe_builtin(t_ast **ast, t_env **env, int foreground);
int						check_abs_bin(char *str);
int						isnt_dot(char *file, char *str);
int						nbr_arg(t_ast **ast);
int						print_error(int err, char *str);
void					exec_fork(t_process **process, char **env, int r);
int						exec_env_pipe(t_ast **ast, t_env **env, t_env **r_env);
int						env_builtin_pipe(t_ast **ast, t_env **env,
						t_env **r_env);
int						check_kill(t_job **job);
int						delete_process(t_process **head, t_process **prev,
						t_process **process);
int						nbr_process(t_job **job);
int						check_j(t_job **table, t_job **job, t_job **prev);
int						bgre(t_ast **ast, int mod);
int						check_job(t_job **job, t_ast **ast, t_job **table);
void					job_len(t_job **j, t_job **table, int *len);
void					print_job_message(t_job **j, int *len, int *pos);
void					close_rdir(int fd, int mod);
void					init_fork(pid_t *pgid, int fg);
void					init_father(pid_t *pid, pid_t *pgid, int fg);
int						pipe_bg(t_process **process, pid_t *pgid, char **env, int r);
int						cont_pipe_bg(t_process **pro, pid_t *pgid, char **env, int *fd);
int						pipe_fg(t_process **process, pid_t *pgid, char **env,
						int r);
int						cont_pipe_fg(t_process **pro, pid_t *pgid, char **env,
						int *fd);
int						print_error_env(int err, char *str);
void					recreat_ast(t_ast **n_ast, t_ast **ast);
int						dup_fd(char *std, char *fd);
int						valid_fd(char *str);
int						check_io(char *tmp);
int		dup_fd(char *std, char *fd);
void	init_env_ast(t_ast **ast, char *str, int type);
#endif
