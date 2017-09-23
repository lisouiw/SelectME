/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:49:24 by ltran             #+#    #+#             */
/*   Updated: 2017/09/23 16:32:25 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int main()
{
	char buf[1024];
	char buf2[30];
	char *ap = buf2;
	char *clearstr, *gotostr, *standstr, *stendstr;

	tgetent(buf, getenv("TERM"));

	clearstr = tgetstr("cl", &ap);
	gotostr = tgetstr("cm", &ap);
	standstr = tgetstr("so", &ap);
	stendstr = tgetstr("se", &ap);

	fputs(clearstr, stdout);
//	tputs(tgoto(gotostr, 20, 10), 1, ft_putchar);
//	printf("Hello, ");
	fputs(standstr, stdout);
	printf("world");
//	fputs(stendstr, stdout);
//	putchar('!');
	return (0);
}
