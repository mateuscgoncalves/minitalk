/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoncalv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:58:38 by mgoncalv          #+#    #+#             */
/*   Updated: 2022/01/19 17:40:13 by mgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_atoi(char *str);

static void	ft_error(int ac, char **av)
{
	if (ac != 3)
	{
		write(1, "Usage : ./client <pid> <message>\n", 33);
		exit(1);
	}
	if (!ft_atoi(av[1]))
	{
		write(1, "PID is not a valid number\n", 26);
		exit(1);
	}
}

static void	ft_send_char(char av, int pid)
{
	int	i;
	int	ret;

	i = 7;
	while (i >= 0)
	{
		if ((av >> i) & 1)
			ret = kill(pid, SIGUSR2);
		else
			ret = kill(pid, SIGUSR1);
		if (ret)
		{
			exit(1);
			write(1, "Error sending signal to server\n", 31);
		}
		usleep(30);
		i--;
	}
	usleep(100);
}

static void	ft_handler_signal(int signal, siginfo_t *info, void *context)
{
	(void) signal;
	(void) info;
	(void) context;
	write(1, "Signal received from server, Au revoir!\n", 40);
	exit(0);
	return ;
}

static void	ft_set_signals(void)
{
	struct sigaction	s1;

	s1.sa_flags = SA_RESTART;
	s1.sa_sigaction = ft_handler_signal;
	sigaction(SIGUSR2, &s1, NULL);
}

int	main(int ac, char **av)
{
	long	i;

	ft_set_signals();
	i = 0;
	ft_error(ac, av);
	while (av[2][i] != '\0')
	{
		ft_send_char(av[2][i], ft_atoi(av[1]));
		i++;
	}
	ft_send_char(av[2][i], ft_atoi(av[1]));
	while (1)
	{
		pause();
	}
	return (0);
}
