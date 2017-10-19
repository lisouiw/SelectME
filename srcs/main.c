/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostimacbook <gostimacbook@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/10/19 19:07:44 by ltran            ###   ########.fr       */
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
#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>


int		set_up_term()
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

void	my_list(t_lst *ls, t_num *nb)
{
	int ver;
	int i;
	int x;
	char *got;
	char *su;
	char *ue;

	x = 0;
	tputs(tgetstr("cl", NULL), 1, ft_put);
	got = tgetstr("cm", NULL);
	su = tgetstr("us", NULL);
	ue = tgetstr("ue", NULL);
	tputs(tgoto(got, x, 0),1,ft_put);
	ver = tgetnum("li");
	while (ls->end != 1)
	{
		i = 0;
		tputs(tgoto(got, x, i),1,ft_put);
		ver = tgetnum("li");
		while ( ls->end != 1 && i < ver -1 )
		{
			if (ls->info[0] == 1)
				tputs(su, 1, ft_put);
			tputs(ls->select, 1, ft_put);
			tputs(ue, 1, ft_put);
			ft_putstr_fd("\n",1);
			ls = ls->next;
			tputs(tgoto(got, x, i+1),1,ft_put);
			++i;
		}
		x = x + nb->max;
	}
	tputs(ls->select, 1, ft_put);
	ft_putstr_fd("\n",1);
	ls = ls->next;
	tputs(tgoto(got, x, i+1),1,ft_put);
}

void	s_win(int sig)
{
	struct ttysize ts;
	extern t_lst *ls;

	set_up_term();
	ioctl(1, TIOCGSIZE, &ts);
	printf ("%i && lines %d\n", sig, ts.ts_lines);
	printf ("columns %d\n", ts.ts_cols);
}

void	ls_signal(void)
{
	signal(SIGWINCH, s_win);
}

int     voir_touche(void)
{
	char     buffer[3];

	ls_signal();
	if (read(0, buffer, 3))
		;
	//	printf("%i\n", 4);
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
	ls->info[0] = 1;
	ls->info[1] = 0;
	ls->info[2] = 0;
	set_up_term();
	my_list(ls, nb);
	while (42)
	{
		voir_touche();
	}
	return (0);
}

