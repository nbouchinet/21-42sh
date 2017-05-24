/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 10:40:43 by khabbar           #+#    #+#             */
/*   Updated: 2016/12/31 11:30:18 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sort_int_tab(int *nbr, int size)
{
	int		sorted;
	int		i;
	int		tmp;

	sorted = 0;
	i = 0;
	tmp = 0;
	while (sorted == 0)
	{
		i = 0;
		sorted = 1;
		while (i < size - 1)
		{
			if (nbr[i] > nbr[i + 1])
			{
				tmp = nbr[i];
				nbr[i] = nbr[i + 1];
				nbr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}
