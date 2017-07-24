/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:03:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/09 14:34:56 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

#include "lexer_parser.h"

/*
**	Key bidings
*/

#define UP		buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0
#define DWN		buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0

#define OPT_C	buf[0] != -61 && buf[1] != -89 && buf[2] != 0
#define OPT_V	buf[0] != -30 && buf[1] != -120 && buf[2] != -102

#define PRINT	(buf[0] > 31 && buf[0] < 127)

#define COMP	(buf[0] == 9 && buf[1] == 0)

#define CUT		(buf[0] == -30 && buf[1] == -119 && buf[2] == -120)
#define CPY		(buf[0] == -61 && buf[1] == -89 && buf[2] == 0)
#define	PST		(buf[0] == -30 && buf[1] == -120 && buf[2] == -102)

#define RETURN	(buf[0] == 10 && buf[1] == 0 && buf[2] == 0)

#define EOT		(buf[0] == 4 && buf[1] == 0)

#define ARR_L	(buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
#define ARR_R	(buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && buf[3] == 0)
#define HOME	buf[0] == 27 && buf[1] == 91 && buf[2] == 72 && buf[3] == 0
#define END		buf[0] == 27 && buf[1] == 91 && buf[2] == 70 && buf[3] == 0
#define OPT_L	(buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 68)
#define OPT_R	(buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 67)
#define OPT_U	(buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 65)
#define OPT_D	(buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 66)
#define MOVE	ARR_L || ARR_R || HOME || END || OPT_L || \
				OPT_R || OPT_U || OPT_D

#define DEL		buf[0] == 127 && buf[1] == 0 && buf[2] == 0

#define OPT_S	buf[0] == -62 && buf[1] == -82 && buf[2] == 0

#define CCP 	CUT || CPY || PST

#define UD		((UP) || (DWN))

#define SEP		(*cmd)[(*win)->cur - (*win)->pr] != ' ' && \
				(*cmd)[(*win)->cur - (*win)->pr] != '|' && \
				(*cmd)[(*win)->cur - (*win)->pr] != ';' && \
				(*cmd)[(*win)->cur - (*win)->pr] != '&' && \
				(*cmd)[(*win)->cur - (*win)->pr] != '<' && \
				(*cmd)[(*win)->cur - (*win)->pr] != '>'

#define OR_SEP	(*cmd)[(*win)->cur - (*win)->pr] == ' ' || \
				(*cmd)[(*win)->cur - (*win)->pr] == '|' || \
				(*cmd)[(*win)->cur - (*win)->pr] == ';' || \
				(*cmd)[(*win)->cur - (*win)->pr] == '&' || \
				(*cmd)[(*win)->cur - (*win)->pr] == '<' || \
				(*cmd)[(*win)->cur - (*win)->pr] == '>'



typedef struct			s_his
{
	size_t				len;
	int					add;
	char				*cmdl;
	struct s_his		*next;
	struct s_his		*prev;
}						t_his;

typedef struct			s_hdoc
{
	char				*hstring;
	char				*fd;
	struct s_hdoc		*next;
}						t_hdoc;

typedef struct			s_win
{
	int					co;
	int					li;
	int					pr;
	int					cur;
	int					cpy_b;
	int					cpy_e;
	int					ccp;
	int					quote;
	int					sh;
	int					ctrld;
	int					pao;
	int					tmp;
	char				*copy;
	t_hdoc				*hd;
	t_his				*his;
	t_env				*lstenv;
	struct termios		term;
}						t_win;

/*
**	cmdl handling functions.
*/

/*
**	arrow func
*/

typedef struct 			s_arrow
{
	int					a;
	int					b;
	int					c;
	int					d;
	void 				(*f)(t_win *win, char *cmd, char buf[]);
}						t_arrow;

void				arrows(t_win *win, char *cmd, char buf[]);
void				arrow_left(t_win *win, char *cmd, char buf[]);
void				arrow_rigth(t_win *win, char *cmd, char buf[]);
void 				up_dwn(t_win *win, char *cmd, char buf[]);
void 				home(t_win *win, char *cmd, char buf[]);
void 				end(t_win *win, char *cmd, char buf[]);
void 				opt_left(t_win *win, char *cmd, char buf[]);
void 				opt_right(t_win *win, char *cmd, char buf[]);


void    			catcmd(t_win *win, char **cmd);
void				call_chs(t_win **win, char **save);
void				ccp(char **cmd, char buf[], t_win *win);
int					check_cmdl(char **save, char **cmd, t_win **win, char buf[]);
int					check_line(char **save, char **cmd, t_win **win, char buf[]);
int					check_input(int i, char buf[], char **cmd);
int					check_quotes(char **cmd, t_win **win);
int					cmdl_signal(char **cmd, char *save, t_win **win);
void				cmp_herestring(char **cmd, t_hdoc *tmp, int fdt[]);
void				ctrl_l(t_win **win, char **cmd);
void				del(char **cmd, t_win *win, t_his **his);
void				del_all(char *cmd, t_win *win);
void				del_hd(t_hdoc **hd);
void 				del_his(char **cmd, t_win *win, t_his **his);
void				e(t_win **win, t_his **his, char **cmd, char **save);
void				exit_sh_mode(t_win *win, t_his **his, char **cmd, char buf[]);
void				findstr(t_his **his, char *cmd);
void 				get_be(t_win *win, char buf[]);
void				get_cmdl(char **cmd, t_win **win, char *save, char buf[]);
void				get_here_string(char **save, t_win **win, int i, int j);
int					get_win_data(t_win **win);
void				handle_pipe_and_or(char **save, t_win **win);
void				heredoc(char **cmd, t_win **win, char buf[]);
int					lst_len(t_his *his);
int					mode_off(t_win **win);
int					mode_on(t_win **win);
void				move_history(t_his **his, char **cmd, char buf, t_win *win);
void				get_history(t_his **his, char *tmp, char **cmd, char buf);
void				init_var(t_win **win);
void				print_prompt(t_win **win);
void				print_search(char **cmd, char buf[], t_his **his, t_win *win);
void				quote_removal(char **cmd);
void				save_history(t_win *win, char **cmd, t_his **his);
void				search_history(char **cmd, t_win **win);
int					set_shell(t_win **win);
void				tmp_pipe(int *p, int flag);
int					unset_shell(t_win **win);
t_win				*win_sgt(void);

/*
**	Completion
*/

typedef struct			s_ls
{
    char				padx[512];
    char				*name;
    struct s_ls			*next;
}						t_ls;

int					call_print_lst(t_win **win, char **cmd, t_ls *list, int i);
void				display_list(t_ls *list, char **cmd, char *path, t_win **win);
void	    		completion(t_win **win, char **cmd);
t_ls				*fill_lst(t_ls **head, struct dirent *rdd, int param);
void				ft_padd_x(t_ls **ls, int *maxlen);
void				ft_putpaddx(t_ls **ls, int maxlen);
int 				is_first_word(char *cmd, int i);
void				list_del(t_ls **list);
int 				list_exe(char *tmp, char **path, t_win **win, char **cmd);
void				list_files(char **tmp, t_win **win, char **cmd);
int					list_len(t_ls **list);
void				print_lst(t_ls **head, t_win **win, char *cmd, int len);


/*
**	Bang
*/

/*
**	bang options
*/

#define 	HB			1
#define 	TB 			2
#define 	RB 			4
#define 	EB 			8
#define 	PB 			16
#define 	QB 			32
#define 	XB 			64

typedef struct			s_bang
{
	int					n;
	char				*string;
	char				*s1;
	char				*s2;
	int					des;
	int					x;
	int					y;
	int					mod;
	int					s;
	int					b;
	int					e;
}						t_bang;

int     		    bang_bang(char **cmd, char *str, t_bang *bang, int len);
int 		        do_sub(t_his *his, t_bang *bang, char **cmd, char *array);
int 				fill_buf(char *tmp, char **cmd, int i, int j);
int					mod_cmd(char **cmd, char **array, t_bang *bang);
void   				process_mod(char **tmp, t_bang *bang, int i, char *ptr);

void				delete_lstenv(t_env **cmd);

#endif
