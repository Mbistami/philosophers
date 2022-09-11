/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 03:56:53 by gruz              #+#    #+#             */
/*   Updated: 2022/09/11 03:58:37 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*ft_init(t_config *config)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * config->number_philos);
	while (i < config->number_philos)
	{
		philo[i].is_eating = 0;
		philo[i].id = i + 1;
		philo[i].eat_counter = 0;
		pthread_mutex_init(&philo[i].eat, NULL);
		philo[i].rfork = (i + 1) % config->number_philos;
		philo[i].lfork = i;
		philo[i].config = config;
		i++;
	}
	config->philosophers = philo;
}

int	ft_parse(int ac, char **args, t_config *config)
{
	if (ac < 5)
	{
		error_handler(0);
		return (1);
	}
	config->number_philos = ft_atoi(args[1]);
	config->ttd = ft_atoi(args[2]);
	config->tte = ft_atoi(args[3]);
	config->tts = ft_atoi(args[4]);
	config->died = 0;
	if (ac == 6)
		config->max_meals = ft_atoi(args[5]);
	ft_init(config);
	return (0);
}

void	ft_mutex_init(t_config *config)
{
	int	i;

	i = 0;
	config->fork = malloc(sizeof(pthread_mutex_t) * config->number_philos);
	pthread_mutex_init(&(config->write), NULL);
	while (i < config->number_philos)
		pthread_mutex_init(&config->fork[i++], NULL);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_config *rules)
{
	long long	i;

	i = ft_get_time();
	while (!(rules->died))
	{
		if (time_diff(i, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}
