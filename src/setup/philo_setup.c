/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:40:50 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:41:30 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	allocate_philosophers_array(t_context *ctx)
{
	ctx->philosophers = malloc(sizeof(t_philo) *
		ctx->cfg->count_philosophers);
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
	if (pthread_create(&philosopher->thread, NULL, action_lifecycle,
			philosopher) != 0)
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