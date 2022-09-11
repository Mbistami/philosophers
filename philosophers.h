/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 03:59:32 by gruz              #+#    #+#             */
/*   Updated: 2022/09/11 04:01:17 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	unsigned long	eat_stamp;
	int				lfork;
	int				rfork;
	int				eat_counter;
	int				is_eating;
	pthread_mutex_t	eat;
	struct s_config	*config;
	int				died;
}	t_philo;

typedef struct s_config
{
	int				number_philos;
	int				ttd;
	int				tte;
	int				tts;
	int				max_meals;
	unsigned long	start_stamp;
	int				died;
	t_philo			*philosophers;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
}	t_config;

int			ft_atoi(const char *string);
int			ft_isdigit(int v);
void		*ft_init(t_config *config);
int			ft_parse(int ac, char **args, t_config *config);
void		ft_mutex_init(t_config *config);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_config *rules);
void		print(t_philo *philo, char *string);

#endif