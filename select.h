/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:05:38 by ltran             #+#    #+#             */
/*   Updated: 2017/09/23 18:03:58 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include <termios.h>
# include <term.h>
#include <curses.h>
#include <termcap.h>
#include <termios.h>

typedef struct		s_lst
{
	char			*select;
	struct s_lst	*next;
}					t_lst;

#endif
