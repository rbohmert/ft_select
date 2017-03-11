/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 14:02:28 by rbohmert          #+#    #+#             */
/*   Updated: 2017/02/02 06:05:32 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/libft.h"
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <curses.h>
# include <term.h>
# include <stdio.h>
# define L(a) ((t_item *)(a->content))

typedef struct		s_select
{
	int		maxwd;
	struct	winsize	win;
	struct	termios	term;
	struct	termios	term2;
	t_list			*list;
}					t_select;

typedef struct		s_item
{
	int		cursor;
	int		select;
	char 	*name;
}					t_item;

void		ft_cpush_back(t_clist **clist, void *content);
t_list		*make_list(char **ag);
void		print_list(t_select *slct);
void		del_elem(t_select *slct, t_list **lst);

int			restore_term(t_select *slct);
int			init_term(char **env, t_select *slct);
void		validate(t_select *slct);

void		app_key(char buf[4], t_select *slct);
void		move_cursor_d(t_select *slct, int flag);
void		move_cursor_u(t_list *list);

t_select	*getslct(t_select *slct);
int			ptchr(int i);
void		freeonelst(t_list *list);
int			maxwd(t_list *lst);
int			nbr_column(t_select *slct);
t_list		*get_lst_nb(t_list *list, int no);
#endif
