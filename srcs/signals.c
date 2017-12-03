/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:03:28 by ltran             #+#    #+#             */
/*   Updated: 2017/12/03 14:22:05 by ltran            ###   ########.fr       */
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
		exit(EXIT_SUCCESS);
	tputs(tgetstr("vi", NULL), 0, ft_put);
	tputs(tgetstr("ti", NULL), 0, ft_put);
	s_win(0);
	sig = 0;
}

void	s_ctrl_z(int sig)
{
	sig = 0;
	init();
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
	tputs(tgetstr("ve", NULL), 0, ft_put);
	tputs(tgetstr("te", NULL), 0, ft_put);
}

void	s_ctrl_c(int sig)
{
	sig = 0;
	tputs(tgetstr("ve", NULL), 0, ft_put);
	tputs(tgetstr("te", NULL), 0, ft_put);
	free_pls();
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
