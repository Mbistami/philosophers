/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gruz <gruz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 03:50:05 by gruz              #+#    #+#             */
/*   Updated: 2022/09/11 04:02:19 by gruz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int v)
{
	if (v >= 48 && v <= 57)
		return (1);
	else
		return (0);
}

void	error_handler(int id)
{
	if (id == 0)
	{
		write(2, "Error: an error has occured.", 28);
		exit(0);
	}
}

unsigned long long	ft_get_time(void)
{
	struct timeval		current_time;
	unsigned long long	i;

	gettimeofday(&current_time, NULL);
	i = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (i);
}
