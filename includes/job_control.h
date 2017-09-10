/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:23:56 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/10 17:57:45 by zadrien          ###   ########.fr       */
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

pid_t 			g_shell_pgid;
struct termios 	g_shell_tmodes;
int 			g_shell_terminal;
int 			g_shell_is_interactive;


typedef void			sigfunc(int);
void					signal_handler(void);

typedef struct			s_process
{
	char				**argv;  /* for execve */
	pid_t				pid; /* Process ID */
	char				completed; /* True if process has completed */
	char				stopped; /* True if process has stopped */
	int					status; /* Report status value*/
	t_ast				*rdir;
	struct s_process	*next; /* Next process in pipe */
}						t_process;

typedef struct			s_job
{
	char				*command; /* Command line */
	struct s_process	*first_process; /* List of process in this job */
	pid_t				pgid; /* Process Group ID */
	char				notified; /* True if user told about stopped job */
	struct termios		tmodes; /* terminal save mode */
	struct s_job		*next; /* Next job */
}						t_job;

typedef struct			s_jseq
{
	int					type;
	int					(*f)(t_ast**, t_env**, int);
}						t_jseq;

typedef struct 			s_tab
{
	int					mod;
	int					(*f)(t_job**, t_ast**, t_job**);
}						t_tab;


void					init_shell();
void					delete_tnode(t_job **node, t_job **prev, t_job **table);
int						ft_joblstadd(t_job **new, t_ast **ast, t_job **table);
int						end_pid(t_job **job, t_ast **ast, t_job **table);
int						add_pid(t_job **job, t_ast **ast, t_job **table);
int						sus_pid(t_job **job, t_ast **ast, t_job **table);
int						chk_pid(t_job **job, t_ast **ast, t_job **table);
int						foreground(t_job **job, t_ast **ast, t_job **table);
int						job_control(t_job **job, t_ast **ast, int mod);
void					new_exec_ast(t_ast **ast, t_env **env);
int						cmd_seq_ast(t_ast **ast, t_env **env);
int						new_cmd_seq(t_ast **ast, t_env **env);
int						new_pipe(t_ast **ast, t_env **env);
void					new_cont_pipe(t_ast **ast, t_env **env, int p[2]);
void					fin_cmd_seq(t_ast **ast, t_env **env);
int						exec_binary(t_ast **ast, t_env **env);
int						exec_ast_oa(t_ast **ast, t_env **env);
int						new_exec_oa(t_ast **ast, t_env **env);
int						new_qm_seq(t_ast **ast, t_env **env);
int						new_ex_pipe(t_ast **ast, t_env **env, int r);
int						init_process(t_ast **ast, t_process **proc, t_env **env);
void					print_process(t_process **pro);
char					**creat_arg_process(t_ast **ast, t_env **env);
int						complete_process(t_ast **ast, t_process **p, t_env **env);
void					print_job(t_job **job);
void					job_ast(t_ast **ast, t_env **env, int foreground);
int						job_pipe(t_ast **ast, t_env **env, int foreground);
int						job_andor(t_ast **ast, t_env **env, int foreground);
int						job_oa_seq(t_ast **ast, t_env **env, int foreground);
int						job_qm_seq(t_ast **ast, t_env **env, int foreground);
int						job_cmd_seq(t_ast **ast, t_env **env, int foreground);
int						exec_pipe_job(t_process **lst, char **env, int r, t_job **job);
char					*init_job_name(t_ast **ast);
int						init_pgid(t_job **job, pid_t pid, t_ast **ast);
void					destroy_ast(t_ast **head);
void					destroy_tok(t_tok **head);
int						exec_job(t_job **job, t_env **env, int foreground);
int						exec_pro(t_process **lst, t_env **env, t_job **j);
char					*init_pipe_job(t_ast **ast);
int						init_job(t_job **job);
int						pipe_job(t_job **lst, t_env **env, int foreground);
int						mark_process_status(t_job **job);
int						inter_job(t_ast **ast, t_env **env);
int						mark_job_status(t_job **job, int status, pid_t pid);
int						job_is_complete(t_job *j);
int						job_is_stopped(t_job *j);
int						ft_fg(t_ast **ast, t_env **env);
int						ft_bg(t_ast **ast, t_env **env);
int						ft_enve(t_ast **ast, t_env **env);
int						mark_job_as_stopped(t_job **job);
int						job_bg_seq(t_ast **ast, t_env **env, int foreground);
void					wait_for_job(t_job **job);
int						exec_pro_bg(t_process **pro, t_env **env, t_job **job);
int						exec_pipe_bg(t_process **pro, char **env, int r, t_job **job);
void					job_cont_pipe(t_process **lst, char **env, t_job **job, int *p);
// =============================================================================
void					cmdl_ctrc(int signal);
void					cmdl_wins(int signal);
void					canon_mode(int signal);
void					ctrl_z(int signal);
int						background(t_job **job, t_ast **ast, t_job **table);
#endif
