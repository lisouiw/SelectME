/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:49:29 by ltran             #+#    #+#             */
/*   Updated: 2017/10/19 18:49:05 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

t_lst	*create_ls(void)
{
	t_lst	*nw;

	if (!(nw = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	nw->select = (char*)malloc(sizeof(char));
	nw->select = NULL;
	nw->start = 1;
	nw->end = 1;
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
		if(!(nw = (t_lst*)malloc(sizeof(t_lst))))
			return (NULL);
		nw->select = ft_strdup(str);
		nw->end = 1;
		nw->next = tmp;
		tmp->prev = nw;
		while (tmp->end != 1)
			tmp = tmp->next;
		tmp->end = 0;
		tmp->next = nw;
		nw->prev = tmp;
		return (ls);
	}
}

t_num	*alloue_num(t_num *nb, int max)
{
	nb = (t_num*)malloc(sizeof(t_num));
	nb->max = max + 1;
	return(nb);
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
	return (ls);
}
