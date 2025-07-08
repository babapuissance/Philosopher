/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 15:50:57 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*      MEAL VALIDATION        */

static short	check_all_philosophers_fed(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		if (fetch_meal_count(ctx->philosophers[index]) < ctx->cfg->meals_required)
			return (0);
		index++;
	}
	return (1);
}

short	validate_meal_counts(t_context *ctx)
{
	if (ctx->cfg->meals_required == (size_t)-1)
		return (0);
	if (fetch_meal_count(ctx->philosophers[0]) >= ctx->cfg->meals_required)
	{
		if (check_all_philosophers_fed(ctx))
		{
			set_termination_state(ctx->cfg, 1);
			return (1);
		}
	}
	return (0);
}

static short	check_philosopher_starvation(t_context *ctx, size_t index)
{
	size_t	starvation_time;

	starvation_time = calculate_time_since_meal(ctx->philosophers[index]);
	if (starvation_time > ctx->cfg->deadline_time && 
		fetch_meal_count(ctx->philosophers[index]) < ctx->cfg->meals_required)
	{
		return (1);
	}
	return (0);
}

static void	announce_philosopher_death(t_context *ctx, size_t index)
{
	size_t	death_timestamp;

	death_timestamp = calculate_simulation_time(ctx->philosophers[index]);
	set_termination_state(ctx->cfg, 1);
	usleep(300);
	log_philosopher_state(ctx->philosophers[index], STATE_DECEASED, death_timestamp);
}

short	validate_meal_times(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		if (check_philosopher_starvation(ctx, index))
		{
			announce_philosopher_death(ctx, index);
			return (1);
		}
		index++;
	}
	return (0);
}

/*     SURVEILLANCE HANDLER    */

static short	perform_surveillance_checks(t_context *ctx)
{
	if (validate_meal_times(ctx))
		return (1);
	if (validate_meal_counts(ctx))
		return (1);
	return (0);
}

static void	*surveillance_routine(void *arg)
{
	t_context	*ctx;

	ctx = (t_context *)arg;
	while (1)
	{
		if (fetch_termination_state(ctx->cfg))
			break ;
		if (perform_surveillance_checks(ctx))
			break ;
		usleep(50);
	}
	return (NULL);
}

short	launch_watcher(t_context *ctx)
{
	if (pthread_create(&ctx->watcher_thread, NULL, surveillance_routine, ctx) != 0)
		return (1);
	return (0);
}

/*     THREAD SYNCHRONIZATION  */

static short	synchronize_philosopher_threads(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		if (pthread_join(ctx->philosophers[index]->thread, NULL) != 0)
			return (1);
		index++;
	}
	return (0);
}

static short	synchronize_watcher_thread(t_context *ctx)
{
	if (pthread_join(ctx->watcher_thread, NULL) != 0)
		return (1);
	return (0);
}

short	await_threads(t_context *ctx)
{
	if (synchronize_philosopher_threads(ctx))
		return (1);
	if (synchronize_watcher_thread(ctx))
		return (1);
	return (0);
}
