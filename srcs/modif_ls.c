/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:03:28 by ltran             #+#    #+#             */
/*   Updated: 2017/11/09 19:31:46 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

void	s_win(int sig)
{
	struct ttysize ts;

	sig = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		exit(0);
	ioctl(1, TIOCGSIZE, &ts);
	nb->tb[0] = ts.ts_cols;
	nb->tb[1] = ts.ts_lines;
	my_list(&ls, &nb);
	my_list(&ls, &nb);
}

void	s_continu(int sig)
{
	if (tcsetattr(0, TCSANOW, &term) == -1)
		exit(0);
	s_win(0);
	sig = 0;
}

void	s_ctrl_z(int sig)
{
	sig = 0;
	tputs(tgetstr("ve", NULL), 1, ft_put);
	init();
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

void	s_ctrl_c(int sig)
{
	sig = 0;
	tputs(tgetstr("ve", NULL), 1, ft_put);
	tputs(tgetstr("cl", NULL), 1, ft_put);
	init();
	exit(EXIT_SUCCESS);
}

void	ls_signal(void)
{
	signal(SIGTSTP, s_ctrl_z);
	signal(SIGCONT, s_continu);
	signal(SIGQUIT, s_ctrl_c);
	signal(SIGWINCH, s_win);
	signal(SIGINT, s_ctrl_c);
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
		tputs(tgetstr("cl", NULL), 1, ft_put);
		tputs(tgetstr("ve", NULL), 1, ft_put);
		exit(0);
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
//	else if (buf[0] == 10 && buf[1] == 0 & buf[2] == 0)
	else if (buf[0] == 32 && buf[1] == 0 & buf[2] == 0)
	{
		tmp->info[0] = (tmp->info[0] == 0) ? 1 : 0;
		tmp->next->info[3] = 1;
	}
	else
	{
		tmp->info[3] = 1;
		exit(0);
		}
	return (ls);
}
