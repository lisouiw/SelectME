/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:03:28 by ltran             #+#    #+#             */
/*   Updated: 2017/11/28 17:59:38 by ltran            ###   ########.fr       */
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
	g_nb->tb[0] = ts.ts_cols;
	g_nb->tb[1] = ts.ts_lines;
	my_list(&g_ls, &g_nb, 0, give_g());
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
	init();
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
	tputs(tgetstr("cl", NULL), 0, ft_put);
	tputs(tgetstr("ve", NULL), 0, ft_put);
	tputs(tgetstr("te", NULL), 0, ft_put);
}

void	s_ctrl_c(int sig)
{
	sig = 0;
	tputs(tgetstr("ve", NULL), 0, ft_put);
	tputs(tgetstr("te", NULL), 0, ft_put);
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
		tputs(tgetstr("ve", NULL), 0, ft_put);
		tputs(tgetstr("te", NULL), 0, ft_put);
		init();
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
	exit(0);
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
