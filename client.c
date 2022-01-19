/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoncalv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:58:38 by mgoncalv          #+#    #+#             */
/*   Updated: 2022/01/19 16:44:57 by mgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static int	ft_atoi(char *str)
{
	int	i;
	int	signe;
	int	nb;

	i = 0;
	signe = 1;
	nb = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	nb *= signe;
	return (nb);
}

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

int	main(int ac, char **av)
{
	long	i;

	i = 0;
	ft_error(ac, av);
	while (av[2][i] != '\0')
	{
		ft_send_char(av[2][i], ft_atoi(av[1]));
		i++;
	}
	ft_send_char(av[2][i], ft_atoi(av[1]));
	return (0);
}
