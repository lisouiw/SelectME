/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostimacbook <gostimacbook@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/11/09 19:26:19 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

int		init(void)
{
	char           *name_term;
	struct	termios term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ICANON);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

int		set_up_term(void)
{
	char	 *name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
//	term.c_lflag |= (ECHONL);
	//IGNBRK
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
//	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

t_lst    *voir_touche(t_lst *ls, t_num *nb)
{
	char	buf[3];

	if (tcsetattr(0, TCSANOW, &term) == -1)
		exit(0);
	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	ls_signal();
	if (read(0, buf, 3) && check(0, &nb, &ls) == 1)
	{
		ls = modif_ls(ls, buf);
	}
	return (ls);
}

void	init_ls(t_lst **ls, t_num **nb)
{
	int		i;
	int		x;

	x = 0;
	if ((*ls)->next->info[1] == 1)
		*ls = (*ls)->next;
	while ((*ls)->info[1] != 1)
		*ls = (*ls)->next;
	while (x + (*nb)->max - 2 <= (*nb)->tb[0])
	{
		i = 0;
		while (i < (*nb)->tb[1])
		{
			(*ls)->info[4] = x;
			(*ls)->info[5] = i;
			*ls = (*ls)->next;
			if ((*ls)->info[1] == 1)
				return;
			++i;
		}
		x = x + (*nb)->max;
	}
}

void	boucle(t_lst *ls, t_num *nb)
{
	while (42)
	{
		my_list(&ls, &nb);
		ls = voir_touche(ls, nb);
	}
}

int		main(int ac, char **ag)
{
	set_up_term();
	if (getenv("TERM") == NULL || ac == 1)
	{
		ft_putendl_fd((ac == 1 ? "No arguments": "Can't identify the terminal"), 1);
		exit(0);
	}
	ls = NULL;
	ls = giv_ls(ag, NULL, &nb);
	init_ls(&ls, &nb);
	boucle(ls, nb);
	return (0);
}
