/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:03:13 by khabbar           #+#    #+#             */
/*   Updated: 2017/04/24 13:09:55 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

#include "lexer_parser.h"

/*
**	define
*/

#define UP		buf[0] == 27 && buf[1] == 91 && buf[2] == 65
#define DWN		buf[0] == 27 && buf[1] == 91 && buf[2] == 66

#define OPT_C	buf[0] != -61 && buf[1] != -89 && buf[2] != 0
#define OPT_V	buf[0] != -30 && buf[1] != -120 && buf[2] != -102

#define PRINT	(buf[0] > 31 && buf[0] < 127)

#define COMP	(buf[0] == 9 && buf[1] == 0)

#define CUT		(buf[0] == -30 && buf[1] == -119 && buf[2] == -120)
#define CPY		(buf[0] == -61 && buf[1] == -89 && buf[2] == 0)
#define	PST		(buf[0] == -30 && buf[1] == -120 && buf[2] == -102)

#define RETURN	(buf[0] == 10 && buf[1] == 0 && buf[2] == 0)

#define EOT		(buf[0] == 4 && buf[1] == 0)

#define ARR_L	(buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
#define ARR_R	(buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
#define HOME	buf[0] == 27 && buf[1] == 91 && buf[2] == 72
#define END		buf[0] == 27 && buf[1] == 91 && buf[2] == 70
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

/*
**	key defines
*/


typedef struct		s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_ls
{
    char            padx[512];
    char            *name;
    struct s_ls		*next;
}					t_ls;

typedef struct		s_his
{
	size_t			len;
	char			*cmdl;
	struct s_his	*next;
	struct s_his	*prev;
}					t_his;

typedef struct		s_hdoc
{
	char			*hstring;
	char			*fd;
	struct s_hdoc	*next;
}					t_hdoc;

typedef struct		s_win
{
	int				co;
	int				li;
	int				pr;
	int				cur;
	int				cpy_b;
	int				cpy_e;
	int				ccp;
	int				quote;
	int				sh;
	int				ctrld;
	char			*copy;
	t_hdoc			*hd;
	t_his			*his;
	t_env			*lstenv;
	struct termios	term;
}					t_win;


/*
**	cmdl handling functions.
*/

void				arrows(t_win *win, char *cmd, char buf[]);
void				arrow_left(t_win *win);
void				arrow_rigth(t_win *win, char *cmd);
void    			catcmd(t_win *win, char **cmd);
void				ccp(char **cmd, char buf[], t_win *win);
void				check_line(char **save, char **cmd, t_win **win, char buf[]);
int					check_quotes(char **cmd, t_win **win);
void				cmdl_ctrc(int signal);
int					cmdl_signal(char **cmd, char *save, t_win **win);
void				del(char **cmd, t_win *win, t_his **his);
void				del_all(char *cmd, t_win *win);
void				del_hd(t_hdoc **hd);
void 				del_his(char **cmd, t_win *win, t_his **his);
void				e(t_win **win, t_his **his, char **cmd, char **save);
void				exit_sh_mode(t_win *win, t_his **his, char **cmd, char buf[]);
void				findstr(t_his **his, char *cmd);
void				get_cmdl(char **cmd, t_win **win, char *save);
void				get_here_string(char **save, t_win **win, int i, int j);
int					get_win_data(t_win **win);
void				handle_pipe_and_or(char **save, t_win **win);
void				heredoc(char **cmd, t_win **win);
int					lst_len(t_his *his);
int					mode_off(t_win **win);
int					mode_on(t_win **win);
void				init_var(t_win **win);
void				print_prompt(t_env *env);
void				print_search(char **cmd, char buf[], t_his **his, t_win *win);
void				quote_removal(char **cmd, t_win **win);
void				save_history(t_win *win, char **cmd, t_his **his);
void				search_history(char **cmd, t_win **win);
int					set_shell(t_win **win);
void				tmp_pipe(int *p, int flag);
int					unset_shell(t_win **win);
void				winsize(t_win **win, char **save, char **cmd);

/*
**	Completion
*/

int					call_print_lst(t_win **win, char **cmd, t_ls *list, int i);
void	    		completion(t_win **win, char **cmd);
t_ls				*fill_lst(t_ls **head, struct dirent *rdd, int param);
void				ft_padd_x(t_ls **ls, int *maxlen);
void				ft_putpaddx(t_ls **ls, int maxlen);
int 				is_first_word(char *cmd, int i);
void				list_del(t_ls **list);
int 				list_exe(char *tmp, char **path, t_win **win, char **cmd, int k);
void				list_files(char **tmp, t_win **win, char **cmd);
int					list_len(t_ls **list);
void				print_lst(t_ls **head, t_win **win, char *cmd, int len);


void				delete_lstenv(t_env **cmd);

#endif