/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:05:38 by ltran             #+#    #+#             */
/*   Updated: 2017/10/19 19:02:03 by ltran            ###   ########.fr       */
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
	struct s_lst	*prev;
	int				start;
	int				end;
	int				info[3];
}					t_lst;

typedef struct		s_num
{
	int				max;
	int				co;
	int				li;
}					t_num;

t_lst	*ls;
t_num	*nb;
t_lst	*add_ls(char *str, t_lst *nw, t_lst *ls);
t_lst	*giv_ls(char **ag, t_lst *ls, t_num **nb);

#endif
