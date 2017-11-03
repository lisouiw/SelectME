/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:06:10 by ltran             #+#    #+#             */
/*   Updated: 2017/11/03 15:28:31 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

int			ft_put(int c)
{
	write(1, &c, 1);
	return(1);
}

t_get		give_g(void)
{
	t_get	get;

	get.cm = tgetstr("cm", NULL);
	get.us = tgetstr("us", NULL);
	get.ue = tgetstr("ue", NULL);
	get.so = tgetstr("so", NULL);
	get.se = tgetstr("se", NULL);
	tputs(tgetstr("cl", NULL), 1, ft_put);
	return (get);
}

int		check(int x, t_num **nb, t_lst **ls)
{
	int		i;

	if ((*ls)->next->info[1] == 1)
		*ls = (*ls)->next;
	while ((*ls)->info[1] != 1)
		*ls = (*ls)->next;

	while (x + (*nb)->max - 2 <= (*nb)->tb[0])
	{
		i = 0;
		while (i < (*nb)->tb[1])
		{
			*ls = (*ls)->next;
			if ((*ls)->info[1] == 1)
				return(1);
			++i;
		}
		x = x + (*nb)->max;
	}
	return(0);
}

void		my_list(t_lst **ls, t_num **nb)
{
	int		i;
	int		x;
	t_get	g;

	x = 0;
	g = give_g();
	if ((*ls)->next->info[1] == 1)
		*ls = (*ls)->next;
	while ((*ls)->info[1] != 1)
		*ls = (*ls)->next;
	while (x + (*nb)->max - 2 <= (*nb)->tb[0])
	{
		i = 0;
		while (i < (*nb)->tb[1])
		{
			tputs(tgoto(g.cm, x, i), 1, ft_put);
			(*ls)->info[4] = x;
			(*ls)->info[5] = i;
			if ((*ls)->info[0] == 1)
				tputs(g.so, 1, ft_put);
			if ((*ls)->info[3] == 1)
				tputs(g.us, 1, ft_put);
			tputs((*ls)->select, 1, ft_put);
			tputs(g.ue, 1, ft_put);
			tputs(g.se, 1, ft_put);
			*ls = (*ls)->next;
			if ((*ls)->info[1] == 1)
			{
				tputs(tgetstr("vi", NULL), 1, ft_put);
				return;
			}
			++i;
		}
		x = x + (*nb)->max;
	}
}
