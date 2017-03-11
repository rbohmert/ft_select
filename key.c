/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:59:58 by rbohmert          #+#    #+#             */
/*   Updated: 2017/02/02 10:44:38 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	move_cursor_u(t_list *list)
{
	t_list	*beg;
	t_list	*tmp;

	beg = list;
	tmp = list;
	if (L(list)->cursor)
	{
		L(list)->cursor = 0;
		while (list->next)
			list = list->next;
		L(list)->cursor = 1;
		return ;
	}
	list = list->next;
	while (list)
	{
		if (L(list)->cursor)
		{
			L(list)->cursor = 0;
			L(tmp)->cursor = 1;
			return ;
		}
		list = list->next;
		tmp = tmp->next;
	}
}

void	move_cursor_d(t_select *slct, int flag)
{
	t_list *list;

	list = slct->list;
	while (list)
	{
		if (L(list)->cursor)
		{
			if (flag == 1)
				L(list)->select = (L(list)->select) ? 0 : 1;
			else if (flag == 2)
				del_elem(slct, &list);
			L(list)->cursor = 0;
			if (list->next)
				L(list->next)->cursor = 1;
			else
				L(slct->list)->cursor = 1;
			break ;
		}
		list = list->next;
	}
}

void	app_key(char buf[4], t_select *slct)
{
	if (buf[0] == 32)
		move_cursor_d(slct, 1);
	else if (buf[0] == 27 && buf[1] == 91)
	{
		if (buf[2] == 66)
			move_cursor_d(slct, 0);
		else if (buf[2] == 65)
			move_cursor_u(slct->list);
		else if (buf[2] == 51 && buf[3] == 126)
			move_cursor_d(slct, 2);
	}
	else if (buf[0] == 27 && !buf[1] && !buf[2] && !buf[3])
	{
		restore_term(slct);
		exit(2);
	}
	else if (buf[0] == 127)
		move_cursor_d(slct, 2);
	else if (buf[0] == 10)
		validate(slct);
}
