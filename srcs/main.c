/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostimacbook <gostimacbook@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/10/31 19:08:02 by ltran            ###   ########.fr       */
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

t_lst    *voir_touche(t_lst *ls, t_num *nb)
{
	char	buf[3];

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	ls_signal();
	if (read(0, buf, 3))
		ls = modif_ls(ls, buf, nb);
	return (ls);
}

int		main(int ac, char **ag)
{
	extern t_lst	*ls;
	extern t_num	*nb;

	ac = 0;
	ls = NULL;
	ls = giv_ls(ag, NULL, &nb);
	while (42)
	{
		my_list(&ls, &nb);
		ls = voir_touche(ls, nb);
	}
	return (0);
}
