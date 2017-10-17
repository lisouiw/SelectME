/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:49:29 by ltran             #+#    #+#             */
/*   Updated: 2017/10/17 19:08:40 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

t_lst	*add_ls(char *str, t_lst *nw, t_lst *ls)
{
	t_lst		*tmp;

	tmp = ls;
	nw = (t_lst*)malloc(sizeof(t_lst));
	nw->select = ft_strdup(str);
	nw->prev = NULL;
	nw->next = NULL;
	if (ls == NULL)
		return (nw);

	nw->prev = (t_lst*)malloc(sizeof(t_lst));
	while (tmp->next != NULL)
	{
		nw->prev = tmp;
		tmp = tmp->next;
	}
	printf("---++-->%s\n",);
	tmp->next = nw;
	return (ls);
}

t_lst	*giv_ls(char **ag, t_lst *ls)
{
	int		i;
	int		max;
	int		tmp;

	i = 0;
	max = 0;
	while (ag[++i] && (tmp = ft_strlen(ag[i])))
		max = (max < tmp) ? tmp : max;
	i = 0;
	while (ag[++i])
	{
		printf("ok %s\n", ag[i]);
		ls = add_ls(ag[i], NULL, ls);
	}

		printf("prv=%s && here=%s && next=%s\n",ls->next->prev->select, ls->next->select, ls->next->next->select);
	exit(0);
	while (ls != NULL)
	{
		printf("prv=%s && here=%s && next=%s\n",ls->prev->select, ls->select, ls->next->select);
		ls = ls->next;
	}
	return (ls);
}
