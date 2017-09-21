/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:49:24 by ltran             #+#    #+#             */
/*   Updated: 2017/09/21 17:02:56 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"
#include <curses.h>
#include <term.h>

int		main(void)
{
	int		nb_c;
	int		nb_l;

	while (42)
	{
		nb_c = tgetnum ("li");
		nb_l = tgetnum ("co");
		printf("co: %i && li: %i\n", nb_c, nb_l);
	}
	return (0);
}
