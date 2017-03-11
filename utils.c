/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 00:44:54 by rbohmert          #+#    #+#             */
/*   Updated: 2017/02/02 10:46:10 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*getslct(t_select *slct)
{
	static t_select *select;

	if (slct)
		select = slct;
	else
		return (select);
	return (NULL);
}

int			ptchr(int i)
{
	write(STDIN_FILENO, &i, 1);
	return (0);
}

void		freeonelst(t_list *lst)
{
	free(L(lst));
	free(lst);
}

int			maxwd(t_list *lst)
{
	int i;
	int len;

	i = 0;
	while (lst)
	{
		if (i < (len = ft_strlen(L(lst)->name)))
			i = len;
		lst = lst->next;
	}
	return (i);
}

int			nbr_column(t_select *slct)
{
	int len;
	int col;

	len = ft_lstlen(slct->list);
	slct->maxwd = maxwd(slct->list);
	col = (len / (slct->win.ws_row - 1)) + 1;
	while ((slct->maxwd * col) > slct->win.ws_col)
		col--;
	return (col);
}

t_list		*get_lst_nb(t_list *list, int no)
{
	int		i;
	t_list	*tmp;

	tmp = list;
	i = -1;
	while (++i < no)
	{
		tmp = tmp->next;
		if (!tmp)
			break ;
	}
	return (tmp);
}
