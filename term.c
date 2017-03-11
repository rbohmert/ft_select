/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 18:01:02 by rbohmert          #+#    #+#             */
/*   Updated: 2017/02/02 10:42:52 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		restore_term(t_select *slct)
{
	if (tcsetattr(0, 0, &slct->term2) == -1)
		return (0);
	tputs(tgetstr("te", NULL), 1, ptchr);
	tputs(tgetstr("ve", NULL), 1, ptchr);
	return (1);
}

int		init_term(char **env, t_select *slct)
{
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (0);
	if (tgetent(NULL, name_term) == -1)
		return (0);
	if (tcgetattr(0, &slct->term) == -1 || tcgetattr(0, &slct->term2) == -1)
		return (0);
	slct->term.c_lflag &= ~(ICANON);
	slct->term.c_lflag &= ~(ECHO);
	slct->term.c_cc[VMIN] = 1;
	slct->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &slct->term) == -1)
		return (0);
	tputs(tgetstr("ti", NULL), 1, ptchr);
	tputs(tgetstr("vi", NULL), 1, ptchr);
	ioctl(0, TIOCGWINSZ, &(slct->win));
	getslct(slct);
	return (1);
}

void	validate(t_select *slct)
{
	t_list *list;

	list = slct->list;
	restore_term(slct);
	while (list)
	{
		if (L(list)->select)
		{
			ft_putstr(L(list)->name);
			ft_putchar(' ');
		}
		list = list->next;
	}
	ft_putchar('\n');
	exit(2);
}
