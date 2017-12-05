/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostimacbook <gostimacbook@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:08:49 by ltran             #+#    #+#             */
/*   Updated: 2017/12/03 17:42:02 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

int		init(void)
{
	char			*name_term;
	struct termios	term;

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
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

t_lst	*voir_touche(t_lst *ls, t_num *nb)
{
	char	buf[3];

	if (tcsetattr(0, TCSANOW, &term) == -1)
		exit(0);
	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	ls_signal();
	if (read(0, buf, 3) && check(0, &nb, &ls) == 1)
		ls = modif_ls(ls, buf, NULL);
	return (ls);
}

void	boucle(t_lst *ls, t_num *nb)
{
	while (42)
	{
		my_list(&ls, &nb, 0, give_g());
		wait(0);
		ls = voir_touche(ls, nb);
	}
}

int		main(int ac, char **ag)
{
	if (getenv("TERM") == NULL || ac == 1 || set_up_term())
	{
		ft_putendl_fd((ac == 1 ? "No arguments" : "Can't identify the terminal")
				, 1);
		exit(0);
	}
	tputs(tgetstr("vi", NULL), 0, ft_put);
	tputs(tgetstr("ti", NULL), 0, ft_put);
	g_ls = NULL;
	g_ls = giv_ls(ag, NULL, &g_nb);
	init_ls(&g_ls, &g_nb);
	boucle(g_ls, g_nb);
	return (0);
}
