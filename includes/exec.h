/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:35:36 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/23 19:40:36 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
/*
*******************************************************************************
**                                 EXECUTION                                **
*****************************************************************************
*/
void	exec_cmd_seq(t_ast **ast, t_env **env);
char	**creat_arg(t_ast **ast, char *cmd);
int		time_4_magic(char **arg, char **env);
int		exec_abs_cmd(t_ast **ast, t_env **env);
int		exec_rlt_cmd(t_ast **ast, t_env **env);
int		exec_binary(t_ast **ast, t_env **env);
// void	ft_freetab(char **trash);
char	*get_dir(char *cmd);
int		ft_checkbin(DIR *dir, char *cmd);
int		binary_finder(char *path, char *cmd);
int		find_bin(t_ast **ast);
char	*binary_find(char *cmd, char **path);
int		find_cmd_bin(t_ast **ast, char **path);
int		count_arg_node(t_ast **ast);
int		seak(char *s);
char	*var_value(int i, char *var, char *value);
void	reduc_shlvl(t_env **env, char *s);
void	increase_shlvl(t_env **env);
char	**get_env(t_env **lst, char *s);
int		isexec(char *path);
char	*create_path(char *env, char *cmd);
#endif
