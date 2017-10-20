/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:05:38 by ltran             #+#    #+#             */
/*   Updated: 2017/10/20 15:12:58 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include "libft/libft.h"
# include <curses.h>
# include <errno.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <unistd.h>

typedef struct		s_lst
{
	char			*select;
	struct s_lst	*next;
	struct s_lst	*prev;
	int				info[5];
}					t_lst;

typedef struct		s_get
{
	char	*cm;
	char	*us;
	char	*ue;
}					t_get;

typedef struct		s_num
{
	int				max;
	int				tb[2];
}					t_num;

t_lst	*ls;
t_num	*nb;
int		set_up_term(void);
t_lst	*add_ls(char *str, t_lst *nw, t_lst *ls);
t_lst	*giv_ls(char **ag, t_lst *ls, t_num **nb);

#endif
