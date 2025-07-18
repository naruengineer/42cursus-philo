/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:12:12 by nando             #+#    #+#             */
/*   Updated: 2025/07/15 11:38:44 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = arg;
	left = philo.id;
	right = (philo->id + 1) % philo->philo_count;
	while (*(philo->stop_flag))
	{
		// forks mutex lock
		pthread_mutex_lock(&philo->forks[left]);
		pthread_mutex_lock(&philo->forks[right]);
		// eat -> log -> timestump -> usleep(philo->time_to_eat * 1000)
		// forks mutex unlock
		pthread_mutex_unlock(&philo->forks[left]);
		pthread_mutex_unlock(&philo->forks[right]);
		// sleep -> log -> usleep
		// think -> log
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	long			*last_meal;
	int				*eat_count;
	int				philo_count;
	int				eat_limit;
	int				stop_flag;
	int				time_to_die;
	int				eat_done_count;
	int				i;

	// check args count
	if (argc < 5 || argc > 6)
	{
		printf("Usage:
			./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	// read params
	philo_count = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	stop_flag = 1;
	if (argc == 6)
		eat_limit = ft_atoi(argv[5]);
	// dynamic array allocation
	eat_count = malloc(sizeof *eat_count * philo_count);
	i = 0;
	while (i < philo_count)
		eat_count[i++] = 0;
	forks = malloc(sizeof *forks * philo_count);
	last_meal = malloc(sizeof *last_meal * philo_count);
	threads = malloc(sizeof *threads * philo_count);
	philo = malloc(sizeof *philo * philo_count);
	if (!forks || !last_meal || !threads || !philo)
		return (EXIT_FAILURE);
	// init mutex and timestump
	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		last_meal[i++] = now_ms();
	}
	// create threads
	i = 0;
	while (i < philo_count)
	{
		philo[i].id = i;
		philo[i].philo_count = philo_count;
		philo[i].time_to_die = time_to_die;
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].eat_limit = eat_limit;
		philo[i].eat_count = eat_count;
		philo[i].forks = forks;
		philo[i].last_meal_times = last_meal;
		philo[i].stop_flag = &stop_flag;
		if (pthread_create(&threads[i], NULL, philosopher, &philo[i]) != 0)
		{
			perror("pthread_create");
			return (EXIT_FAILURE);
		}
		i++;
	}
	// monitoring
	while (stop_flag)
	{
		i = 0;
		eat_done_count = 0;
		while (i < philo_count)
		{
			if (now_ms() - last_meal[i] > time_to_die)
			{
				log_death(i);
				stop_flag = 0;
				break ;
			}
			if (eat_limit > 0 && eat_count[i] >= eat_limit)
				eat_done_count++;
			if (eat_done_count == philo_count)
			{
				stop_flag = 0;
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	// delete threads
	i = 0;
	while (i < philo->philo_count)
		pthread_join(threads[i++], NULL);
	// delete mutex
	i = 0;
	while (i < philo->philo_count)
		pthread_mutex_destroy(&forks[i++]);
	// free dynamic array
	free(forks);
	free(last_meal);
	free(threads);
	free(philo);
	return (0);
}
