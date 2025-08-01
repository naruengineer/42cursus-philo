/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:01:39 by nando             #+#    #+#             */
/*   Updated: 2025/07/30 15:00:34 by nando            ###   ########.fr       */
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
	free(philo->last_meal_times);
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
	free(philo->eat_count);
	free(philo->last_meal_times);
	free(philo);
	free(threads);
	free(forks);
}

int	create_thread(t_philo *p, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < p->philo_count)
	{
		if (pthread_create(&threads[i], NULL, philosopher, &p[i]) != 0)
			return (i);
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
	int				stop_flag;
	int				is_failed;
	int				i;
	long			start_time;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;

	/* 1) 引数チェック */
	if (argc < 5 || argc > 6)
	{
		fprintf(stderr,
			"usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [eat_limit]\n");
		return (EXIT_FAILURE);
	}
	/* 2) ローカル変数にパラメータ格納 */
	philo_count = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	eat_limit = (argc == 6) ? ft_atoi(argv[5]) : -1;
	stop_flag = 1;
	start_time = now_ms();
	/* 3) 動的配列確保 */
	philo = malloc(sizeof *philo * philo_count);
	forks = malloc(sizeof *forks * philo_count);
	threads = malloc(sizeof *threads * philo_count);
	last_meal = malloc(sizeof *last_meal * philo_count);
	eat_count = malloc(sizeof *eat_count * philo_count);
	if (!philo || !forks || !threads || !last_meal || !eat_count)
		return (EXIT_FAILURE);
	/* 4) 初期化 */
	for (i = 0; i < philo_count; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
		last_meal[i] = start_time;
		eat_count[i] = 0;
	}
	/* 5) 構造体にデータ設定 */
	for (i = 0; i < philo_count; i++)
	{
		philo[i].id = i;
		philo[i].philo_count = philo_count;
		philo[i].time_to_die = time_to_die;
		philo[i].time_to_eat = time_to_eat;
		philo[i].time_to_sleep = time_to_sleep;
		philo[i].eat_limit = eat_limit;
		philo[i].eat_count = eat_count;
		philo[i].forks = forks;
		philo[i].last_meal_times = last_meal;
		philo[i].stop_flag = &stop_flag;
		philo[i].start_time = start_time;
	}
	/* 6) スレッド生成 */
	is_failed = create_thread(philo, threads);
	if (is_failed)
	{
		cleaning_create_error_case(philo, threads, forks, is_failed);
		return (EXIT_FAILURE);
	}
	monitoring(philo);
	cleaning(philo, threads, forks);
	return (0);
}
