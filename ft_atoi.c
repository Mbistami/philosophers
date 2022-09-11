/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 04:03:14 by gruz              #+#    #+#             */
/*   Updated: 2022/09/11 04:03:27 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_white_space(char c)
{
	char	*white_spaces;

	white_spaces = " \t\n\v\f\r";
	while (*white_spaces)
	{
		if (*white_spaces == c)
			return (1);
		white_spaces++;
	}
	return (0);
}

int	calculate_return(int ne)
{
	if (ne > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *string)
{
	size_t	i;
	int		ne;
	int		to_return;

	i = 0;
	ne = 1;
	to_return = 0;
	while (is_white_space(string[i]) == 1)
		i++;
	if (string[i] == '\0')
		return (0);
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			ne = -1;
		i++;
	}
	while (ft_isdigit(string[i]) != 0)
	{
		if (to_return > 999999998)
			return (calculate_return(ne));
		to_return = (string[i] - '0') + (10 * to_return);
		i++;
	}
	return (to_return * ne);
}

void	print(t_philo *philo, char *string)
{
	unsigned long	time_;

	time_ = (ft_get_time() - philo->config->start_stamp);
	pthread_mutex_lock(&(philo->config->write));
	printf("%ld\t%d\t%s\n", time_, philo->id, string);
	pthread_mutex_unlock(&(philo->config->write));
}
