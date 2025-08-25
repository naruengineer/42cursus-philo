/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:01:39 by nando             #+#    #+#             */
/*   Updated: 2025/08/25 21:20:58 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_ctx *c, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		fprintf(stderr, "args error\n");
		return (1);
	}
	c->philo_count = ft_atoi(argv[1]);
	c->time_to_die = ft_atoi(argv[2]);
	c->time_to_eat = ft_atoi(argv[3]);
	c->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		c->eat_limit = ft_atoi(argv[5]);
	else
		c->eat_limit = -1;
	c->stop_flag = 1;
	return (0);
}

static int	alloc_arrays(t_ctx *c)
{
	c->philo = malloc(sizeof * c->philo * c->philo_count);
	c->forks = malloc(sizeof * c->forks * c->philo_count);
	c->threads = malloc(sizeof * c->threads * c->philo_count);
	c->last_meal = malloc(sizeof * c->last_meal * c->philo_count);
	c->eat_count = malloc(sizeof * c->eat_count * c->philo_count);
	if (!c->philo || !c->forks || !c->threads || !c->last_meal || !c->eat_count)
	{
		free(c->philo);
		free(c->forks);
		free(c->threads);
		free(c->last_meal);
		free(c->eat_count);
		return (1);
	}
	return (0);
}

static void	init_arrays(t_ctx *c)
{
	int	i;

	i = 0;
	c->start_time = now_ms();
	while (i < c->philo_count)
	{
		pthread_mutex_init(&c->forks[i], NULL);
		c->last_meal[i] = c->start_time;
		c->eat_count[i] = 0;
		i++;
	}
}

static void	setup_philos_structs(t_ctx *c)
{
	int	i;

	i = 0;
	while (i < c->philo_count)
	{
		c->philo[i].id = i;
		c->philo[i].philo_count = c->philo_count;
		c->philo[i].time_to_die = c->time_to_die;
		c->philo[i].time_to_eat = c->time_to_eat;
		c->philo[i].time_to_sleep = c->time_to_sleep;
		c->philo[i].eat_limit = c->eat_limit;
		c->philo[i].eat_count = c->eat_count;
		c->philo[i].forks = c->forks;
		c->philo[i].last_meal_times = c->last_meal;
		c->philo[i].stop_flag = &c->stop_flag;
		c->philo[i].start_time = c->start_time;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_ctx	c;
	int		created;
	int		fail;
	int		i;

	i = 0;
	if (parse_args(&c, argc, argv) || alloc_arrays(&c))
		return (EXIT_FAILURE);
	init_arrays(&c);
	setup_philos_structs(&c);
	fail = create_thread(c.philo, c.threads, &created);
	if (fail)
	{
		cleaning_create_error_case(c.philo, c.threads, c.forks, created);
		return (EXIT_FAILURE);
	}
	monitoring(c.philo);
	cleaning(c.philo, c.threads, c.forks);
	return (0);
}
