/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:12:12 by nando             #+#    #+#             */
/*   Updated: 2025/08/29 12:33:22 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	process_think(t_philo *p)
{
	log_actions(p->id, "is thinking", p);
	usleep(100);
}

static void	process_take_fork(t_philo *p, int left, int right)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->forks[left]);
		log_actions(p->id, "has taken a fork", p);
		pthread_mutex_lock(&p->forks[right]);
		log_actions(p->id, "has taken a fork", p);
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(&p->forks[right]);
		log_actions(p->id, "has taken a fork", p);
		pthread_mutex_lock(&p->forks[left]);
		log_actions(p->id, "has taken a fork", p);
	}
}

static void	process_eat_meal(t_philo *p)
{
	log_actions(p->id, "is eating", p);
	pthread_mutex_lock(p->state_mtx);
	p->last_meal_times[p->id] = now_ms();
	p->eat_count[p->id]++;
	pthread_mutex_unlock(p->state_mtx);
	usleep(p->time_to_eat * 1000);
}

static void	process_put_down_fork_and_sleep(t_philo *p, int left, int right)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_unlock(&p->forks[right]);
		pthread_mutex_unlock(&p->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&p->forks[left]);
		pthread_mutex_unlock(&p->forks[right]);
	}
	log_actions(p->id, "is sleeping", p);
	usleep(p->time_to_sleep * 1000);
}



void	*philosopher(void *arg)
{
	t_philo	*p;
	int		left;
	int		right;

	p = (t_philo *)arg;
	left = p->id;
	right = (p->id + 1) % p->philo_count;
	if (p->philo_count == 1)
	{
		log_actions(p->id, "is thinking", p);
		pthread_mutex_lock(&p->forks[left]);
		log_actions(p->id, "has taken a fork", p);
		while (is_running(p))
			usleep(1000);
		pthread_mutex_unlock(&p->forks[left]);
		return (NULL);
	}
	while (is_running(p))
	{
		process_think(p);
		process_take_fork(p, left, right);
		process_eat_meal(p);
		process_put_down_fork_and_sleep(p, left, right);
	}
	return (NULL);
}
