/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/09/23 18:32:48 by ltran            ###   ########.fr       */
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
		exit(0);
	}
	return (0);
}

/*
int              main(void)
{
	extern char PC;
	extern char * UP;
	extern char * BC;
//	int		nb_c;
//	int		nb_l;
	char    *res;

	set_up_term();
	while (42)
	{
		if ((res = tgetstr("mr", NULL)) == NULL)
			return (-1);
		tputs(tgoto(res, -1, -1), 1, putchar);
		ft_putendl("PUTE");
		if ((res = tgetstr("me", NULL)) == NULL)
			return (-1);

		voir_touche();
		tputs(tgoto(res, 0, 1), 1, putchar);
//		printf("co: %i && li: %i\n", nb_c, nb_l);
	}
	return (0);
}*/

t_lst	*add_ls(char *str, t_lst *new, t_lst *ls)
{
	t_lst		*tmp;

	tmp = ls;
	new = (t_lst*)malloc(sizeof(t_lst));
	new->select = ft_strdup(str);
	new->next = NULL;
	if (ls == NULL)
		return (new);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (ls);
}

t_lst	*giv_lst(char **ag, t_lst *ls)
{
	int		i;

	i = 0;
	while (ag[++i])
		ls = add_ls(ag[i], NULL, ls);
	return (ls);
}

int		main(int ac, char **ag)
{
	t_lst	*ls;

	ac = 0;
	ls = giv_lst(ag, NULL);
	return (0);
}

