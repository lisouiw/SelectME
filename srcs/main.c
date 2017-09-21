/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/09/21 18:28:26 by ltran            ###   ########.fr       */
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
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

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
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

int     voir_touche()
{
	char     buffer[3];

	read(0, buffer, 3);
	printf("C'est une touche %d %d %d !\n", buffer[0], buffer[1], buffer[2]);
	if (buffer[0] == 27 && buffer[1] == 91)
		return (27);
	if (buffer[0] == 4)
	{
		printf("Ctlr+d, on quitte !\n");
		return (-1);
	}
	return (0);
}

int              main(void)
{
	int		nb_c;
	int		nb_l;

	set_up_term();
	while (42)
	{
		term_mouv();
		if (voir_touche() == -1)
			return (0);
		set_up_term();
		nb_l = tgetnum ("li");
		nb_c = tgetnum ("co");
		printf("co: %i && li: %i\n", nb_c, nb_l);
	}
	return (0);
}


