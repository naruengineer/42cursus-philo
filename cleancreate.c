/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleancreate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:12:11 by nando             #+#    #+#             */
/*   Updated: 2025/08/29 13:11:56 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_philo *p, pthread_t *threads, int *created)
{
	int	i;

	i = 0;
	while (i < p->philo_count)
	{
		if (pthread_create(&threads[i], NULL, philosopher, &p[i]) != 0)
		{
			*created = i;
			return (1);
		}
		i++;
	}
	*created = i;
	return (0);
}

void	cleaning(t_philo *philo, pthread_t *threads, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < philo->philo_count)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(philo->state_mtx);
	free(philo->eat_count);
	free(philo->last_meal_times);
	free(philo->state_mtx);
	free(philo);
	free(threads);
	free(forks);
}

void	cleaning_create_error_case(t_philo *philo, pthread_t *threads,
		pthread_mutex_t *forks, int create_count)
{
	int	i;

	i = 0;
	while (i < create_count)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < create_count)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(philo->state_mtx);
	free(philo->eat_count);
	free(philo->last_meal_times);
	free(philo->state_mtx);
	free(philo);
	free(threads);
	free(forks);
}
