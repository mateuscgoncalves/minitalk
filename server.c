/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoncalv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:10:16 by mgoncalv          #+#    #+#             */
/*   Updated: 2022/01/21 12:19:12 by mgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static	void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static	void	ft_putnbr(int n)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		write(1, "-", 1);
		nb = -n;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	else
		ft_putchar(nb % 10 + '0');
}

static int	ft_makechar(char *s, int i, int j, int signal)
{
	s[j] = s[j] << 1;
	if (signal == SIGUSR2)
		s[j] = s[j] + 1;
	return (i + 1);
}

static void	ft_handler(int signal, siginfo_t *info, void *context)
{
	static int	i = 0;
	static int	j = 0;
	static char	s[2147483647];

	(void) context;
	if (i == 0)
		s[j] = '\0';
	if (i < 8)
		i = ft_makechar(s, i, j, signal);
	if (i == 8)
	{
		if (!s[j] || j == 2147483646)
		{
			write(1, s, j);
			if (!s[j])
				kill(info->si_pid, SIGUSR2);
			s[0] = '\0';
			j = 0;
			i = 0;
			return ;
		}
		i = 0;
		j++;
	}
}

int	main(void)
{
	struct sigaction	s1;

	s1.sa_flags = SA_RESTART;
	s1.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &s1, NULL);
	sigaction(SIGUSR2, &s1, NULL);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
}
