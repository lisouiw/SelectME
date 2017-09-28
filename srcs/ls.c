/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:49:29 by ltran             #+#    #+#             */
/*   Updated: 2017/09/28 18:14:16 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../select.h"

t_lst	*add_ls(char *str, t_lst *nw, t_lst *ls)
{
	t_lst		*tmp;

	tmp = ls;
	nw = (t_lst*)malloc(sizeof(t_lst));
	nw->select = ft_strdup(str);
	nw->next = NULL;
	if (ls == NULL)
		return (nw);
	while (tmp->next != NULL)
		tmp = tmp->next;
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
		ls = add_ls(ag[i], NULL, ls);
	return (ls);
}
