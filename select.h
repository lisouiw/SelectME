/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:05:38 by ltran             #+#    #+#             */
/*   Updated: 2017/10/16 18:10:56 by ltran            ###   ########.fr       */
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
	int				max;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_l
{
	int		co;
	int		li;
}					t_l;

t_lst	*add_ls(char *str, t_lst *nw, t_lst *ls);
t_lst	*giv_ls(char **ag, t_lst *ls);

#endif
