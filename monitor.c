/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:00:37 by nando             #+#    #+#             */
/*   Updated: 2025/08/25 17:34:59 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_done(t_philo *p, int i, int *done)
{
	long	now;

	now = now_ms();
	if (now - p->last_meal_times[i] > p->time_to_die)
	{
		log_death(i, p, now);
		*(p->stop_flag) = 0;
		return (1);
	}
	if (p->eat_limit > 0 && p->eat_count[i] >= p->eat_limit)
		(*done)++;
	return (0);
}

void	monitoring(t_philo *p)
{
	int	i;
	int	done;

	while (*(p->stop_flag))
	{
		i = 0;
		done = 0;
		while (i < p->philo_count)
		{
			if (check_done(p, i, &done))
				return ;
			i++;
		}
		if (p->eat_limit > 0 && done == p->philo_count)
		{
			*(p->stop_flag) = 0;
			return ;
		}
		usleep(1000);
	}
}
