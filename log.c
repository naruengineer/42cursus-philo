/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:41:25 by nando             #+#    #+#             */
/*   Updated: 2025/08/29 12:45:03 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_death(int id, t_philo *p, long detect_ts)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	long					log_ts;

	pthread_mutex_lock(&mtx);
	log_ts = detect_ts - p->start_time;
	printf("%ld %d died\n", log_ts, id + 1);
	pthread_mutex_unlock(&mtx);
}

void	log_actions(int id, char *msg, t_philo *p)
{
	static pthread_mutex_t	action_mtx = PTHREAD_MUTEX_INITIALIZER;
	long					time_stamp;
	int						runnning;

	pthread_mutex_lock(&action_mtx);
	time_stamp = now_ms() - p->start_time;
	pthread_mutex_lock(p->state_mtx);
	runnning = *(p->stop_flag);
	pthread_mutex_unlock(p->state_mtx);
	if (runnning)
		printf("%ld %d %s\n", time_stamp, id + 1, msg);
	pthread_mutex_unlock(&action_mtx);
}
