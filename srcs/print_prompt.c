/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 14:57:54 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:46:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libftprintf.h"

void		print_prompt(void)
{
	char		prompt[1024];

	getcwd(prompt, 1024);
	ft_printf("%@42sh: %@%@\n$> ", H_YELLOW, prompt, I);
}
