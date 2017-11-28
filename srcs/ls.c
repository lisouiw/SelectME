/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:49:29 by ltran             #+#    #+#             */
/*   Updated: 2017/11/28 15:08:24 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

///0f03ad8568
/*
info[0] = video
info[1] = debut
info[2] = end
info[3] = cursor
info[4] = pos colonne;
info[5] = pos line;
*/

t_lst	*create_ls(void)
{
	t_lst	*nw;

	if (!(nw = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	nw->select = NULL;
	nw->info[0] = 0;
	nw->info[1] = 0;
	nw->info[2] = 0;
	nw->info[4] = 0;
	nw->info[5] = 0;
	nw->info[6] = 0;
	nw->prev = NULL;
	nw->next = NULL;
	return (nw);
}

t_lst	*add_ls(char *str, t_lst *nw, t_lst *ls)
{
	t_lst		*tmp;

	tmp = ls;
	if (tmp->select == NULL)
	{
		ls->select = ft_strdup(str);
		ls->next = ls;
		ls->prev = ls;
		return (ls);
	}
	else
	{
		if (!(nw = (t_lst*)malloc(sizeof(t_lst))))
			return (NULL);
		nw->select = ft_strdup(str);
		nw->next = tmp;
		nw->prev = tmp->prev;
		tmp->prev->next = nw;
		tmp->prev = nw;
		return (ls);
	}
}

t_num	*alloue_num(t_num *nb, int max)
{
	struct ttysize ts;

	nb = (t_num*)malloc(sizeof(t_num));
	nb->max = max + 2;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		exit(0);
	ioctl(1, TIOCGSIZE, &ts);
	nb->tb[0] = ts.ts_cols;
	nb->tb[1] = ts.ts_lines;
	nb->tb[2] = 0;
	return (nb);
}

t_lst	*giv_ls(char **ag, t_lst *ls, t_num **nb)
{
	int		i;
	int		max;
	int		tmp;

	i = 0;
	max = 0;
	while (ag[++i] && (tmp = ft_strlen(ag[i])))
		max = (max < tmp) ? tmp : max;
	*nb = alloue_num(NULL, max);
	i = 0;
	ls = create_ls();
	while (ag[++i])
		ls = add_ls(ag[i], NULL, ls);
	ls->info[1] = 1;
	ls->prev->info[2] = 1;
	ls->info[3] = 1;
	return (ls);
}
