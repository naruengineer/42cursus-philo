/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:00:37 by nando             #+#    #+#             */
/*   Updated: 2025/08/31 12:22:30 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_stop(t_philo *p)
{
	int	res;

	pthread_mutex_lock(p->state_mtx);
	res = *(p->stop_flag);
	pthread_mutex_unlock(p->state_mtx);
	return (res);
}

static void	set_stop(t_philo *p, int flag)
{
	pthread_mutex_lock(p->state_mtx);
	*(p->stop_flag) = flag;
	pthread_mutex_unlock(p->state_mtx);
}

static int	check_done(t_philo *p, int i, int *done)
{
	long	now;
	long	last;
	int		e_count;

	now = now_ms();
	pthread_mutex_lock(p->state_mtx);
	last = p->last_meal_times[i];
	e_count = p->eat_count[i];
	pthread_mutex_unlock(p->state_mtx);
	if (now - last > p->time_to_die)
	{
		log_death(i, p, now);
		set_stop(p, 0);
		return (1);
	}
	if (p->eat_limit > 0 && e_count >= p->eat_limit)
		(*done)++;
	return (0);
}

void	monitoring(t_philo *p)
{
	int	i;
	int	done;

	while (get_stop(p))
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
			set_stop(p, 0);
			return ;
		}
		usleep(1000);
	}
}
