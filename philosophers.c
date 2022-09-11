/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 03:48:34 by gruz              #+#    #+#             */
/*   Updated: 2022/09/11 03:58:57 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->config->fork[philo->lfork]));
	print(philo, "taking left fork");
	pthread_mutex_lock(&(philo->config->fork[philo->rfork]));
	print(philo, "taking right fork");
	pthread_mutex_lock(&(philo->eat));
	print(philo, "eating");
	philo->eat_stamp = ft_get_time();
	smart_sleep(philo->config->tte, philo->config);
	philo->eat_counter++;
	pthread_mutex_unlock(&(philo->eat));
	pthread_mutex_unlock(&(philo->config->fork[philo->lfork]));
	pthread_mutex_unlock(&(philo->config->fork[philo->rfork]));
}

void	*ft_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2)
		usleep(15000);
	while (!philo->config->died)
	{
		ft_eat(philo);
		if (philo->config->max_meals == philo->eat_counter)
			break ;
		print(philo, "sleeping");
		smart_sleep(philo->config->tts, philo->config);
		print(philo, "thinking");
	}
}

void	handle_checker(t_philo *philos, t_config *config)
{
	int	i;

	while (!config->died)
	{
		i = 0;
		pthread_mutex_lock(&philos[i].eat);
		if (time_diff(philos[i].eat_stamp, ft_get_time()) > config->ttd)
		{
			print(&philos[i], "died");
			philos[i].died = 1;
			exit(0);
		}
		pthread_mutex_unlock(&philos[i].eat);
		usleep(100);
		i++;
	}
}

void	ft_launcher(t_config *config)
{
	int			i;
	pthread_t	tid;
	t_philo		*philos;

	i = 0;
	philos = config->philosophers;
	config->start_stamp = ft_get_time();
	while (i < config->number_philos)
	{
		if (pthread_create(&tid, NULL, &ft_routine,
				&config->philosophers[i]) != 0)
		{
			write(2, "Error: thread faild!", 20);
			return ;
		}
		philos[i].eat_stamp = ft_get_time();
		i++;
	}
	i = 0;
	handle_checker(philos, config);
}

int	main(int ac, char **av)
{
	t_config	config;

	if (ft_parse(ac, av, &config))
		return (0);
	ft_mutex_init(&config);
	ft_launcher(&config);
}
