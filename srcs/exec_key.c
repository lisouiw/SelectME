/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:03:28 by ltran             #+#    #+#             */
/*   Updated: 2017/12/03 17:28:19 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

void	free_pls(void)
{
	t_lst	*tmp;

	free(g_nb);
	while (g_ls->info[1		] != 1)
		g_ls = g_ls->next;
	while (g_ls->info[1] != 1 && g_ls->info[2] != 1)
	{
		tmp = g_ls->next;
		g_ls->next->info[1] = 1;
		free(g_ls->select);
		free(g_ls);
	}
}

void	move_me(t_lst *ls, int i, int li)
{
	if (i == 68 && (ls = ls->prev))
	{
		while (ls->info[5] != li)
			ls = (*ls).prev;
	}
	else if (i == 67 && (ls = ls->next))
	{
		while (ls->info[5] != li)
			ls = (*ls).next;
	}
	(*ls).info[3] = 1;
}

void	del_ls(t_lst **ls)
{
	t_lst	**tmp;

	tmp = &(*ls);
	if ((*ls)->info[1] == 1 && (*ls)->info[2] == 1)
	{
		tputs(tgetstr("ve", NULL), 0, ft_put);
		tputs(tgetstr("te", NULL), 0, ft_put);
		init();
		free((*ls)->select);
		free(*ls);
		exit(EXIT_SUCCESS);
	}
	else if ((*ls)->info[1] == 1)
		(*ls)->next->info[1] = 1;
	else if ((*ls)->info[2] == 1)
		(*ls)->prev->info[2] = 1;
	(*ls)->prev->next = (*ls)->next;
	(*ls)->next->prev = (*ls)->prev;
	(*tmp)->next->info[3] = 1;
	free((*tmp)->select);
	free(*tmp);
}

void	enter_tch(t_lst *ls)
{
	int		i;

	i = 0;
	tputs(tgetstr("ve", NULL), 1, ft_put);
	tputs(tgetstr("te", NULL), 1, ft_put);
	while (ls->info[2] != 1)
	{
		if (ls->info[0] == 1)
		{
			++i;
			i > 1 ? ft_putchar_fd(' ', 1) : 0;
			ft_putstr_fd(ls->select, 1);
		}
		ls = ls->next;
	}
	if (ls->info[0] == 1)
	{
		++i;
		i > 1 ? ft_putchar_fd(' ', 1) : 0;
		ft_putstr_fd(ls->select, 1);
	}
	i > 0 ? ft_putchar_fd('\n', 1) : 0;
	init();
	free_pls();
	exit(0);
}

t_lst	*modif_ls(t_lst *ls, char *buf, t_lst *tmp)
{
	tmp = ls;
	while ((*tmp).info[3] != 1)
		tmp = tmp->next;
	tmp->info[3] = 0;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		tmp->next->info[3] = 1;
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		tmp->prev->info[3] = 1;
	else if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 67 || buf[2] == 68))
		move_me(tmp, buf[2], tmp->info[5]);
	else if (buf[0] == 127 && buf[1] == 0 & buf[2] == 0)
		del_ls(&tmp);
	else if (buf[0] == 10 && buf[1] == 0 & buf[2] == 0)
		enter_tch(ls);
	else if (buf[0] == 32 && buf[1] == 0 & buf[2] == 0)
	{
		tmp->info[0] = (tmp->info[0] == 0) ? 1 : 0;
		tmp->next->info[3] = 1;
	}
	else if (buf[0] == 27 && buf[1] == 0 & buf[2] == 0)
		s_ctrl_c(0);
	else
		tmp->info[3] = 1;
	return (ls);
}
