/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostimacbook <gostimacbook@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/10/15 18:29:41 by gostimacbook     ###   ########.fr       */
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
	return (0);
}
/*
int		term_mouv()
{
	char           *name_term;
	struct termios term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = (ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_cc[VSUSP] = ISIG;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (0);
}*/

int     voir_touche()
{
	char     buffer[3];

	read(0, buffer, 3);
	printf("C'est une touche %d %d %d !\n", buffer[0], buffer[1], buffer[2]);
	if (buffer[0] == 4)
	{
		printf("Ctlr+d, on quitte !\n");
		exit(0);
	}
	return (0);
}

void	test(t_lst *ls)
{
	ft_putstr_fd(tgetstr("cl", NULL), 1);
	ft_putstr_fd(tgetstr("us", NULL),1);
	ft_putendl_fd(ls->select,0);
	ft_putstr_fd(tgetstr("ue", NULL),1);
	ls = ls->next;
	ft_putendl_fd(ls->select,1);
//	ft_putstr_fd(tgoto(tgetstr("cm", NULL),0,0),1);
	return;
}

int	ft_put(int c)
{
	write(1, &c, 1);

	return(1);
}


void	my_list(t_lst *ls)
{
	int ver;
	int i;
	int x;
	char *got;

	x = 0;
	got = tgetstr("cm", NULL);
	tputs(tgetstr("cl", NULL), 1, ft_put);
	tputs(tgoto(got, x, 0),1,ft_put);
		
	ver = tgetnum("li");
	while (ls != NULL)
	{
		i = 0;
		tputs(tgoto(got, x, i),1,ft_put);
		while ( ls != NULL && i < ver -1 )
		{
			tputs(ls->select, 1, ft_put);
			ft_putstr_fd("\n",1);
			ls = ls->next;
			tputs(tgoto(got, x, i+1),1,ft_put);
			++i;
		}
		x = x + 10;
	}
}


int		main(int ac, char **ag)
{
	t_lst	*ls;

	ac = 0;
	ls = giv_ls(ag, NULL);
	set_up_term();
	my_list(ls);
	
	while (1)
		;
	return (0);
}

