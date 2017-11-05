/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 13:05:38 by ltran             #+#    #+#             */
/*   Updated: 2017/11/05 16:05:33 by ltran            ###   ########.fr       */
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
	int				info[7];
}					t_lst;

typedef struct		s_get
{
	char	*cm;
	char	*us;
	char	*ue;
	char	*so;
	char	*se;
}					t_get;

typedef struct		s_num
{
	int				max;
	int				tb[3];
}					t_num;

t_lst	*ls;
t_num	*nb;

//main
int		set_up_term(void);
int		init(void);
t_lst	*voir_touche(t_lst *ls, t_num *nb);

//ls
t_lst	*add_ls(char *str, t_lst *nw, t_lst *ls);
t_lst	*giv_ls(char **ag, t_lst *ls, t_num **nb);
t_num	*alloue_num(t_num *nb, int max);
t_lst	*create_ls(void);

//modif_ls
void	s_win(int sig);
void	s_quit(int sig);
void	ls_signal(void);
void	move_me(t_lst *lst, int i, int li);
void	del_ls(t_lst **ls);
t_lst	*modif_ls(t_lst *ls, char *buf);

//tools
int		ft_put(int c);
t_get	give_g(void);
void	my_list(t_lst **ls, t_num **nb);
int		check(int x, t_num **nb, t_lst **lst);

#endif
