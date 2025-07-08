/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 15:50:57 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*        CONFIG SETUP         */

static short	allocate_config_memory(t_context *ctx)
{
	ctx->cfg = malloc(sizeof(t_config));
	if (!ctx->cfg)
		return (1);
	if (memory_add(ctx->mem, ctx->cfg))
		return (1);
	return (0);
}

static void	parse_timing_parameters(t_context *ctx, char **argv)
{
	ctx->cfg->count_philosophers = ft_atoll(argv[1]);
	ctx->cfg->deadline_time = ft_atoll(argv[2]);
	ctx->cfg->duration_eat = ft_atoll(argv[3]);
	ctx->cfg->duration_sleep = ft_atoll(argv[4]);
}

static void	configure_meal_requirements(t_context *ctx, char **argv)
{
	if (argv[5])
		ctx->cfg->meals_required = ft_atoll(argv[5]);
	else
		ctx->cfg->meals_required = -1;
}

static void	initialize_simulation_state(t_context *ctx)
{
	ctx->cfg->simulation_start = current_timestamp();
	ctx->cfg->termination_flag = 0;
}

short	setup_config(t_context *ctx, char **argv)
{
	if (allocate_config_memory(ctx))
		return (1);
	parse_timing_parameters(ctx, argv);
	configure_meal_requirements(ctx, argv);
	initialize_simulation_state(ctx);
	return (0);
}

/*         FORKS SETUP         */

static short	allocate_forks_array(t_context *ctx)
{
	ctx->cfg->forks = malloc(sizeof(pthread_mutex_t) * ctx->cfg->count_philosophers);
	if (!ctx->cfg->forks)
		return (1);
	if (memory_add(ctx->mem, ctx->cfg->forks))
		return (1);
	return (0);
}

static void	initialize_fork_mutexes(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		pthread_mutex_init(&ctx->cfg->forks[index], NULL);
		index++;
	}
}

static void	initialize_coordination_mutexes(t_context *ctx)
{
	pthread_mutex_init(&ctx->cfg->lock_forks, NULL);
	pthread_mutex_init(&ctx->cfg->lock_output, NULL);
	pthread_mutex_init(&ctx->cfg->lock_termination, NULL);
}

short	setup_forks(t_context *ctx)
{
	if (allocate_forks_array(ctx))
		return (1);
	initialize_fork_mutexes(ctx);
	initialize_coordination_mutexes(ctx);
	return (0);
}

/*     PHILOSOPHERS SETUP      */

static short	allocate_philosophers_array(t_context *ctx)
{
	ctx->philosophers = malloc(sizeof(t_philo) * ctx->cfg->count_philosophers);
	if (!ctx->philosophers)
		return (1);
	if (memory_add(ctx->mem, ctx->philosophers))
		return (1);
	return (0);
}

static short	initialize_philosopher_mutexes(t_philo *philosopher)
{
	if (pthread_mutex_init(&philosopher->lock_meal_time, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philosopher->lock_meal_count, NULL) != 0)
	{
		pthread_mutex_destroy(&philosopher->lock_meal_time);
		return (1);
	}
	return (0);
}

static t_philo	*create_philosopher_instance(t_context *ctx, size_t id)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (!philosopher)
		return (NULL);
	philosopher->identifier = id;
	philosopher->timestamp_last_meal = 0;
	philosopher->meals_consumed = 0;
	philosopher->cfg = ctx->cfg;
	if (initialize_philosopher_mutexes(philosopher))
	{
		free(philosopher);
		return (NULL);
	}
	if (pthread_create(&philosopher->thread, NULL, action_lifecycle, philosopher) != 0)
	{
		pthread_mutex_destroy(&philosopher->lock_meal_time);
		pthread_mutex_destroy(&philosopher->lock_meal_count);
		free(philosopher);
		return (NULL);
	}
	return (philosopher);
}

static short	launch_even_philosophers(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		ctx->philosophers[index] = create_philosopher_instance(ctx, index);
		if (!ctx->philosophers[index])
			return (1);
		if (memory_add(ctx->mem, ctx->philosophers[index]))
			return (1);
		index += 2;
	}
	return (0);
}

static short	launch_odd_philosophers(t_context *ctx)
{
	size_t	index;

	index = 1;
	while (index < ctx->cfg->count_philosophers)
	{
		ctx->philosophers[index] = create_philosopher_instance(ctx, index);
		if (!ctx->philosophers[index])
			return (1);
		if (memory_add(ctx->mem, ctx->philosophers[index]))
			return (1);
		index += 2;
	}
	return (0);
}

short	setup_philosophers(t_context *ctx)
{
	if (allocate_philosophers_array(ctx))
		return (1);
	if (launch_even_philosophers(ctx))
		return (1);
	if (launch_odd_philosophers(ctx))
		return (1);
	return (0);
}
