/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 15:23:29 by rbohmert          #+#    #+#             */
/*   Updated: 2017/02/02 10:49:05 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	change_size(void)
{
	t_select *slct;

	slct = getslct(NULL);
	ioctl(0, TIOCGWINSZ, &(slct->win));
	print_list(slct);
}

void	stop(int sig)
{
	char		charstop[2];
	t_select	*slct;

	(void)sig;
	slct = getslct(NULL);
	charstop[0] = slct->term2.c_cc[VSUSP];
	charstop[1] = 0;
	tcsetattr(0, TCSADRAIN, &slct->term2);
	tputs(tgetstr("te", NULL), 1, ptchr);
	tputs(tgetstr("ve", NULL), 1, ptchr);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, charstop);
	ft_putstr(" ");
}

void	continu(int sig)
{
	t_select	*slct;

	(void)sig;
	signal(SIGTSTP, stop);
	slct = getslct(NULL);
	tcsetattr(0, TCSADRAIN, &slct->term);
	tputs(tgetstr("ti", NULL), 1, ptchr);
	tputs(tgetstr("vi", NULL), 1, ptchr);
	print_list(slct);
}

void	sighandler(int sig)
{
	if (sig == SIGWINCH)
		change_size();
	else if (sig == SIGINT || sig == SIGQUIT || sig == SIGTERM)
	{
		restore_term(getslct(NULL));
		exit(2);
	}
	else if (sig == SIGTSTP)
		stop(SIGTSTP);
	else if (sig == SIGCONT)
		continu(SIGCONT);
	else
	{
		ft_putnbr(sig);
		ft_putnbr(SIGWINCH);
		ft_putstr("signal non gere magueul\n");
	}
}

void	block_sig(void)
{
	int i;

	i = 0;
	while (i < 33)
		signal(i++, sighandler);
}

int		main(int ac, char **ag, char **env)
{
	t_select	slct;
	char		buf[4];

	if (ac == 1)
		return (0);
	slct.list = make_list(ag);
	init_term(env, &slct);
	block_sig();
	bzero(buf, 4);
	while (1)
	{
		app_key(buf, &slct);
		print_list(&slct);
		bzero(buf, 4);
		read(0, buf, 4);
	}
	restore_term(&slct);
	return (0);
}
