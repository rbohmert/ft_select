/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 17:25:45 by rbohmert          #+#    #+#             */
/*   Updated: 2017/02/02 10:40:06 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

void	del_elem(t_select *slct, t_list **lst)
{
	t_list *list;
	t_list *tmp;

	if (!slct->list->next)
	{
		freeonelst(slct->list);
		restore_term(slct);
		exit(2);
	}
	if (L(slct->list)->cursor)
	{
		tmp = slct->list;
		slct->list = slct->list->next;
		freeonelst(tmp);
		return ;
	}
	tmp = slct->list;
	list = tmp->next;
	while (!L(list)->cursor)
	{
		list = list->next;
		tmp = tmp->next;
	}
	tmp->next = list->next;
	*lst = tmp;
	freeonelst(list);
}

t_list	*make_list(char **ag)
{
	t_list	*list;
	t_item	*itm;
	int		i;

	i = 1;
	list = NULL;
	itm = NULL;
	while (ag[i])
	{
		itm = (t_item *)malloc(sizeof(t_item));
		itm->cursor = (i == 1) ? 1 : 0;
		itm->select = 0;
		itm->name = ft_strdup(ag[i++]);
		ft_push_back(&list, itm, 0);
	}
	return (list);
}

void	put_item(t_list *list, int max, int flag)
{
	int len;

	if (list == NULL)
		return ;
	if (L(list)->cursor)
		tputs(tgetstr("us", NULL), 1, ptchr);
	if (L(list)->select)
		tputs(tgetstr("mr", NULL), 1, ptchr);
	ft_putstr(L(list)->name);
	if (L(list)->select)
		tputs(tgetstr("me", NULL), 1, ptchr);
	if (L(list)->cursor)
		tputs(tgetstr("ue", NULL), 1, ptchr);
	if (flag)
	{
		len = ft_strlen(L(list)->name);
		while (len < max)
		{
			ft_putchar(' ');
			len++;
		}
	}
}

void	print_list(t_select *slct)
{
	t_list	*list;
	int		i;
	int		j;
	int		col;

	i = 0;
	j = 0;
	list = slct->list;
	tputs(tgetstr("cl", NULL), 1, ptchr);
	col = nbr_column(slct);
	while (i < (slct->win.ws_row - 1) && list != NULL)
	{
		while (j < col)
		{
			put_item(get_lst_nb(slct->list, i + j * (slct->win.ws_row - 1)),\
			slct->maxwd, (col > 1) ? 1 : 0);
			(j++ == col - 1) ? 0 : ft_putstr("   ");
		}
		j = 0;
		ft_putchar('\n');
		i++;
		list = list->next;
	}
}
