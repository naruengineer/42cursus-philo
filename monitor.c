/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:00:37 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 14:00:53 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_philo *p)
{
	int	i;
	int	eat_done_count;

	while (*(p->stop_flag))
	{
		i = 0;
		eat_done_count = 0;
		while (i < p->philo_count)
		{
			if (now_ms() - p->last_meal_times[i] > p->time_to_die)
			{
				log_death(i);
				*(p->stop_flag) = 0;
				return ;
			}
			if (p->eat_limit > 0 && p->eat_count[i] >= p->eat_limit)
				eat_done_count++;
			i++;
		}
		if (p->eat_limit > 0 && eat_done_count == p->philo_count)
		{
			*(p->stop_flag) = 0;
			return ;
		}
		usleep(1000);
	}
}
