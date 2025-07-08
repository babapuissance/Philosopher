/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:42:10 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:42:22 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	check_all_philosophers_fed(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		if (fetch_meal_count(ctx->philosophers[index]) <
			ctx->cfg->meals_required)
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
		fetch_meal_count(ctx->philosophers[index]) <
		ctx->cfg->meals_required)
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
	log_philosopher_state(ctx->philosophers[index], STATE_DECEASED,
		death_timestamp);
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