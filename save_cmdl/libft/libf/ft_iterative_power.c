/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 16:14:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/02/20 13:58:54 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_power(int nb, int power)
{
	int		i;
	int		result;

	i = 0;
	result = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (++i != power)
		result = result * nb;
	return (result);
}
