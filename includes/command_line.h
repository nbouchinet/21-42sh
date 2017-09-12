/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:03:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 09:34:48 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H
#include <term.h>
#include <dirent.h>

/*
**	Deplacement sur la cmdl
*/

# define LEFT(buf)	buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && !buf[3]
# define RIGHT(buf)	buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && !buf[3]
# define HOME(buf)	buf[0] == 27 && buf[1] == 91 && buf[2] == 72 && !buf[3]
# define END(buf)	buf[0] == 27 && buf[1] == 91 && buf[2] == 70 && !buf[3]
# define OPT_L(buf)	buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 68
# define OPT_R(buf)	buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 67
# define OPT_U(buf)	buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 65
# define OPT_D(buf)	buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 66
# define ARROW(buf)	(LEFT(buf)) || (RIGHT(buf)) || (UP(buf)) || (DOWN(buf))
# define OPT(buf)	(OPT_L(buf)) || (OPT_R(buf)) || (OPT_U(buf)) || (OPT_D(buf))

/*
**	Caractere imprimable et recherche dans l historique
*/

# define SH(buf)	buf[0] == 18 && !buf[1] && !buf[2] && !buf[3]
# define NEXT(buf)	buf[0] == 14 && !buf[1] && !buf[2] && !buf[3]
# define OPT_N(buf)	buf[0] == -62 && buf[1] == -82 && !buf[2] && !buf[3]
# define UP(buf)	buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && !buf[3]
# define DOWN(buf)	buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && !buf[3]
# define PRINT(buf)	buf[0] > 31 && buf[0] < 127

/*
**	Couper/Coller
*/

# define CUT(buf)	buf[0] == -30 && buf[1] == -119 && buf[2] == -120 && !buf[3]
# define CPY(buf)	buf[0] == -61 && buf[1] == -89 && !buf[2] && !buf[3]
# define PST(buf)	buf[0] == -30 && buf[1] == -120 && buf[2] == -102 && !buf[3]

/*
**	Return, CTRL-D, CTRL-L, CTRL-U, CTRL-T
*/

# define RETURN(buf) buf[0] == 10 && !buf[1] && !buf[2] && !buf[3]
# define CTRL_D(buf) buf[0] == 4 && !buf[1] && !buf[2] && !buf[3]
# define CTRL_L(buf) buf[0] == 12 && !buf[1] && !buf[2] && !buf[3]
# define CTRL_U(buf) buf[0] == 21 && !buf[1] && !buf[2] && !buf[3]
# define CTRL_T(buf) buf[0] == 20 && !buf[1] && !buf[2] && !buf[3]
# define CTRL_L(buf) buf[0] == 12 && !buf[1] && !buf[2] && !buf[3]

/*
**	Structure de gestion de la cmdl (deplacement, historique, couper/coller ...)
*/

typedef struct		s_comp
{
	char			*str;
	char			pad[512];
	struct s_comp	*n;
}					t_comp;

typedef struct		s_his
{
	char			*cmdl;
	struct s_his	*n;
	struct s_his	*p;
}					t_his;

typedef struct		s_line
{
	char			*str;
	char			*save;
	char			buf[6];
	int				co;
	int				li;
	int				cur;
	int				pr;
	int				len;
}					t_line;

typedef	struct		s_ccp
{
	char			*cpy;
	int				start;
	int				end;
	int				ccp;

}					t_ccp;

/*
**	Mode
*/

# define CCTRLD		1
# define CHIS_S		2
# define CSQ			4
# define CDQ			8
# define CRESET		16
# define CPIPE		32
# define CAND		64
# define COR			128

typedef struct		s_cmdl
{
	int				exit;
	int				opt;
	char			*prompt;
	t_line			line;
	t_ccp			ccp;
	t_env			*lstenv;
	struct termios	term;
}					t_cmdl;

/*
**	A supprimer
*/

t_env 		*lst_at(t_env **env, char *cmp);

/*
**	Structure des commandes ds la cmdl
*/

typedef struct 		s_op
{
	int				key[5];
	int				(*f)(t_cmdl *cmdl);
}					t_op;

/*
**	Affichage du promt
*/

void 				print_prompt(void);


/*
**	Renvoi les tete de listes
*/

t_cmdl				**cmdl_slg(void);
t_his				**his_slg(void);

/*
**	Suppression des listes
*/

void 				del_all(t_cmdl **cmdl, t_his **his);

/*
**	Check l env
*/

char				**check_env(char **env);

/*
**	Active/desactive le mode canonique et l echo du term
**	Recup de la taille du term
*/

int					mode_off(t_cmdl *cmdl);
int					unset_shell(t_cmdl *cmdl);
int					mode_on(t_cmdl *cmdl);
int					set_shell(t_cmdl *cmdl);
int					get_win_data(t_cmdl *cmdl);

/*
**	========	Fonctions de la ligne de commande	========
*/

void				get_cmdl(t_cmdl *cmdl);
void 				init_cmdl(void);
void 				remalloc_cmdl(t_line * line, int len);

/*
**	Affichage
*/

int	 				print(t_cmdl *cmdl, char buf[]);
int					search_history_print(t_cmdl *cmdl, char buf[]);

/*
**	Gestion des signaux
*/

void 				cmdl_signals(t_cmdl *cmdl);

/*
**	Suppression
*/


int					del(t_cmdl *cmdl);

/*
**	Clear
*/

int					ctrl_l(t_cmdl *cmdl);

/*
**	Deplacement
*/

int	 				arrow_left(t_cmdl *cmdl);
int					arrow_rigth(t_cmdl *cmdl);
int	 				home(t_cmdl *cmdl);
int	 				end(t_cmdl *cmdl);
int					up_dwn(t_cmdl *cmdl);
int	 				opt_right(t_cmdl *cmdl);
int	 				opt_left(t_cmdl *cmdl);

/*
**	Functions du Copier/Couper/Coller
*/

int	 				ccp(t_cmdl *cmd);
int					paste(t_cmdl *cmdl, int len_cpy, int len_str);

/*
**	Fonctions de gestion de l historique et recherche dans l historique
*/

void 				cmd_save_history(char *str);
int 				cmd_history(t_cmdl *cmdl);
int					cmd_search_history(t_cmdl *cmdl);
t_his				*findcmdl(char *str, char buf[], int reset);

/*
**	Fonction de verification de la cmdl (quick-in suite a un return ou un ctrld)
*/

int 				return_cmdl(t_cmdl *cmdl);
int 				exit_search_mode(t_cmdl *cmdl);
int					check_quote(t_cmdl *cmdl);
int					handle_pipe_and_or(t_cmdl *cmdl, int k);
int					inhibiteur(t_cmdl *cmdl, int len);
int					ctrl_d(t_cmdl *cmdl);

/*
**	Completion
*/

t_comp 				*fill_comp(t_comp **comp, struct dirent *rdd, int param);
int 				display_comp(t_cmdl *cmdl, t_comp **comp, int offset);
char				*get_path(char **tmp);
int					completion(t_cmdl *cmdl);
int					sep(t_cmdl *cmdl, int w);
int					is_exec(t_cmdl *cmdl);
int					check_comp(t_comp **head, char *name);
void 				completion_edit(t_line *line, t_comp **comp,
	 char *tmp, int offset);

#endif
