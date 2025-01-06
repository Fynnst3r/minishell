/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:47:39 by fforster          #+#    #+#             */
/*   Updated: 2025/01/04 21:31:41 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler3(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
	}
	if (signum == SIGQUIT)
	{
	}
}

void	signal_handler2(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	if (signum == SIGQUIT)
	{
	}
}

void	signal_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGINT)
	{
		write(2, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
	}
}

void	prepare_signal(t_data *data, void (sig_handler)(int))
{
	g_signal = 0;
	data->sa.sa_handler = sig_handler;
	sigemptyset(&data->sa.sa_mask);
	data->sa.sa_flags = 0;
	rl_catch_signals = 0;
	if (sigaction(SIGINT, &data->sa, NULL) == -1)
		ft_error("Error: Could not recieve SIGQUIT!", 1, NULL);
	if (sigaction(SIGQUIT, &data->sa, NULL) == -1)
		ft_error("Error: Could not recieve SIGQUIT!", 1, NULL);
}
