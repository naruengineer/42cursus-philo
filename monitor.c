/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:00:37 by nando             #+#    #+#             */
/*   Updated: 2025/07/30 19:20:29 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_philo *p)
{
	int		i;
	int		done;
	long	detect_ts;

	while (*(p->stop_flag))
	{
		i = 0;
		done = 0;
		while (i < p->philo_count)
		{
			detect_ts = now_ms();
			// 飢死判定
			if (detect_ts - p->last_meal_times[i] > p->time_to_die)
			{
				log_death(i, p, detect_ts);
				*(p->stop_flag) = 0;
				return ;
			}
			// 食事回数判定
			if (p->eat_limit > 0 && p->eat_count[i] >= p->eat_limit)
				done++;
			i++;
		}
		// 全員達成で終了
		if (p->eat_limit > 0 && done == p->philo_count)
		{
			//log_complete(p->eat_limit);
			*(p->stop_flag) = 0;
			return ;
		}
		usleep(1000);
	}
}
