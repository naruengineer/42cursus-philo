/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:01:39 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 14:34:42 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleaning(t_philo *philo, pthread_t *threads, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
		pthread_join(threads[i++], NULL);
	i = 0;
	while (i < philo->philo_count)
		pthread_mutex_destroy(&forks[i++]);
	free(philo->eat_count);
	free(philo->forks);
	free(philo->last_meal);
	free(philo->threads);
	free(philo);
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
	free(philo->eat_count);
	free(philo->forks);
	free(philo->last_meal);
	free(philo->threads);
	free(philo);
}

int	create_thread(t_philo *p, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < p->philo_count)
	{
		p[i].id = i;
		p[i].philo_count = p->philo_count;
		p[i].time_to_die = p->time_to_die;
		p[i].time_to_eat = p->time_to_eat;
		p[i].time_to_sleep = p->time_to_sleep;
		p[i].eat_limit = p->eat_limit;
		p[i].eat_count = p->eat_count;
		p[i].forks = p->forks;
		p[i].last_meal_times = p->last_meal;
		p[i].stop_flag = &(p->stop_flag);
		if (pthread_create(&threads[i], NULL, philosopher, &p[i]) != 0)
		{
			perror("pthread_create");
			return (i);
		}
		i++;
	}
	return (0);
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
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				is_failed;
	int				i;

	// check args count
	if (argc < 5 || argc > 6)
	{
		printf("Usage:
			./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	eat_limit = -1;
	stop_flag = 1;
	// read params
	philo_count = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
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
	if (!eat_count || !forks || !last_meal || !threads || !philo)
		return (EXIT_FAILURE);
	// init mutex and timestump
	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		last_meal[i++] = now_ms();
	}
	is_failed = create_thread(philo, threads, forks);
	if (is_failed)
		cleaning_create_error_case(philo, threads, forks, is_failed);
	monitoring(philo);
	cleaning(philo, threads, forks);
	return (0);
}
