/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:41:25 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 13:42:10 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_death(int id)
{
	static pthread_mutex_t	death_mutex = PTHREAD_MUTEX_INITIALIZER;
	long					time_stamp;

	time_stamp = now_ms();
	pthread_mutex_lock(&death_mutex);
	printf("%ld %d is died\n", time_stamp, id);
	pthread_mutex_unlock(&death_mutex);
}

void	log_actions(int id, char *log)
{
	static pthread_mutex_t	p_mutex = PTHREAD_MUTEX_INITIALIZER;
	long					time_stamp;

	time_stamp = now_ms();
	pthread_mutex_lock(&p_mutex);
	printf("%ld %d %s\n", time_stamp, id + 1, log);
	pthread_mutex_unlock(&p_mutex);
}
