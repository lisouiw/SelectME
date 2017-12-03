/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:06:10 by ltran             #+#    #+#             */
/*   Updated: 2017/12/03 14:38:20 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

void	my_list(t_lst **ls, t_num **nb, int x, t_get g)
{
	int		i;

	if ((*ls)->next->info[1] == 1)
		*ls = (*ls)->next;
	while ((*ls)->info[1] != 1)
		*ls = (*ls)->next;
	while (x + (*nb)->max - 2 <= (*nb)->tb[0])
	{
		i = -1;
		while (++i < (*nb)->tb[1])
		{
			tputs(tgoto(g.cm, x, i), 0, ft_put);
			(*ls)->info[4] = x;
			(*ls)->info[5] = i;
			my_tputs(ls, g);
			*ls = (*ls)->next;
			if ((*ls)->info[1] == 1)
				return ;
		}
		x = x + (*nb)->max;
	}
}

void	free_pls(void)
{
	t_lst	*tmp;

	free(g_nb);
	while (g_ls->info[1] != 1)
		g_ls = g_ls->next;
	while (g_ls->info[1] != 1 && g_ls->info[2] != 1)
	{
		tmp = g_ls->next;
		g_ls->next->info[1] = 1;
		free(g_ls->select);
		free(g_ls);
	}
}

void	init_ls(t_lst **ls, t_num **nb)
{
	int		i;
	int		x;

	x = 0;
	if ((*ls)->next->info[1] == 1)
		*ls = (*ls)->next;
	while ((*ls)->info[1] != 1)
		*ls = (*ls)->next;
	while (x + (*nb)->max - 2 <= (*nb)->tb[0])
	{
		i = 0;
		while (i < (*nb)->tb[1])
		{
			(*ls)->info[4] = x;
			(*ls)->info[5] = i;
			*ls = (*ls)->next;
			if ((*ls)->info[1] == 1)
				return ;
			++i;
		}
		x = x + (*nb)->max;
	}
}
