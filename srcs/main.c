/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/09/24 18:04:42 by ltran            ###   ########.fr       */
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
int		term_init()
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
	if (tcsetattr(0, TCSANOW, &term) == -1)
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

int     my_puts(const char *s)
{
	while (*s != '\0')
		write(1, s++, 1);
	write(1, "\n", 1);
	return (1);
}

void	test(t_lst *ls)
{
	char buf[1024];
	char buf2[30];
	char *ap = buf2;
	char *clear, *cm_p, *vd, *vid, *un, *und;

	tgetent(buf, getenv("TERM"));

	clear = tgetstr("cl", &ap);
	cm_p = tgetstr("cm", &ap);
	vd = tgetstr("so", &ap);
	vid = tgetstr("se", &ap);
	un = tgetstr("us", &ap);
	und = tgetstr("ue", &ap);

	while (ls != NULL)
	{
		un = tgetstr("us", &ap);
		und = tgetstr("ue", &ap);
		tputs(vd, 1, putchar);
			printf("%s\n", ls->select);
		tputs(vid, 1, putchar);
	tputs(un, 1, putchar);
		tputs(und, 1, putchar);

		ls = ls->next;
	}
	putchar('!');
}

int		main(int ac, char **ag)
{
	t_lst	*ls;
	char  *clstr;
//	char  *cmstr;

	set_up_term();
	clstr = tgetstr("cl", NULL);
//	tputs(clstr, 1, putchar);
	ac = 0;
	ls = giv_lst(ag, NULL);

	test(ls);
	term_init();
//	term_mouv();
	while (42)
		;
	while (voir_touche())
		;
	return (0);
}
