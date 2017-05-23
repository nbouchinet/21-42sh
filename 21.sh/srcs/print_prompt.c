/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_promt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 14:57:54 by khabbar           #+#    #+#             */
/*   Updated: 2017/04/25 14:46:54 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libftprintf.h"

void		print_prompt(void)
{
	char		prompt[1024];

	getcwd(prompt, 1024);
	ft_printf("%@%@%@\n$> ", H_YELLOW, prompt, I);
}
