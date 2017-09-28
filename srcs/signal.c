/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:11:21 by ltran             #+#    #+#             */
/*   Updated: 2017/09/28 17:23:47 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

void sighandler(int);

int main()
{
	signal(SIGINT, sighandler);
	signal(SIGTSTP, sighandler);
	signal(SIGQUIT, sighandler);
	while(1)
	{
		printf("Going to sleep for a second...\n");
		sleep(1);
	}
	return(0);
}

void sighandler(int signum)
{
	printf("Caught signal %d, coming out...\n", signum);
	exit(signum);
}
