/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:03:28 by ltran             #+#    #+#             */
/*   Updated: 2017/10/31 19:16:33 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

void	s_win(int sig)
{
	struct ttysize ts;
	extern t_lst *ls;
	extern t_num *nb;

	sig = 0;
	set_up_term();
	ioctl(1, TIOCGSIZE, &ts);
	nb->tb[0] = ts.ts_cols;
	nb->tb[1] = ts.ts_lines;
	my_list(&ls, &nb);
}

void	s_quit(int sig)
{
	sig = 0;
	tputs(tgetstr("ve", NULL),1,ft_put);
	exit(EXIT_SUCCESS);
}

void	ls_signal(void)
{
	signal(SIGWINCH, s_win);
	signal(SIGINT, s_quit);
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
		exit(0);
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

t_lst	*modif_ls(t_lst *ls, char *buf)
{
	t_lst	*tmp;

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
	else
		tmp->info[3] = 1;
	return (ls);
}