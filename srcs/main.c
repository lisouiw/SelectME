/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostimacbook <gostimacbook@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/10/20 15:54:27 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 fleche haut 27 91 65
 fleche bas 27 91 66
 fleche droite 27 91 67
 fleche gauche 27 91 68
 espace 32 91 67
 return (enter) 10 91 67
 echap 27 -85 -5
 delete 127 91 67
 ctrl+z 26 91 67
*/
#include "../select.h"

int		set_up_term(void)
{
	char           *name_term;
	struct termios term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_cc[VSUSP] = ISIG;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

int	ft_put(int c)
{
	write(1, &c, 1);
	return(1);
}

t_get	give_g(void)
{
	t_get	get;

	get.cm = tgetstr("cm", NULL);
	get.us = tgetstr("us", NULL);
	get.ue = tgetstr("ue", NULL);
	tputs(tgetstr("cl", NULL), 1, ft_put);
	return (get);
}

void	my_list(t_lst *ls)
{
	int		i;
	int		x;
	t_get	g;

	x = 0;
	g = give_g();
	while (2)
	{
		if (x + nb->max - 2 > nb->tb[0])
			return;
		i = 0;
		while (i < nb->tb[1])
		{
			tputs(tgoto(g.cm, x, i), 1, ft_put);
			if (ls->info[3] == 1)
				tputs(g.us, 1, ft_put);
			tputs(ls->select, 1, ft_put);
			tputs(g.ue, 1, ft_put);
			ls = ls->next;
			if (ls->info[1] == 1)
			{
				tputs(tgetstr("vi", NULL),1,ft_put);
				return;
			}
			++i;
		}
		x = x + nb->max;
	}
}

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
	my_list(ls);
}

void	s_quit(int sig)
{
	sig = 0;
	tputs(tgetstr("ve", NULL),1,ft_put);
	exit(0);
}

void	ls_signal(void)
{
	signal(SIGWINCH, s_win);
	signal(SIGINT, s_quit);
}

int     voir_touche(t_lst *ls)
{
	char     buffer[3];

	ls_signal();
	if (read(0, buffer, 3))
		;
	if (buffer[0] == 4)
	{
		exit(0);
	}
	ls = NULL;
	return (0);
}

int		main(int ac, char **ag)
{
	extern t_lst	*ls;
	extern t_num	*nb;

	ac = 0;
	ls = giv_ls(ag, NULL, &nb);
	my_list(ls);
/*	int i = 100;
	while (--i > -2)
	{
		printf("%s ->[%i][%i]\n", ls->select, ls->info[1], ls->info[2]);
		ls = ls->next;
	}
	exit(0);
*/	while (42)
		voir_touche(ls);
	return (0);
}

