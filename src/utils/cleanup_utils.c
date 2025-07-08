/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:39:40 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:44:19 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_fork_mutexes(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		pthread_mutex_destroy(&ctx->cfg->forks[index]);
		index++;
	}
}

static void	destroy_philosopher_mutexes(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		if (ctx->philosophers[index])
		{
			pthread_mutex_destroy(&ctx->philosophers[index]->lock_meal_time);
			pthread_mutex_destroy(&ctx->philosophers[index]->lock_meal_count);
		}
		index++;
	}
}

static void	destroy_coordination_mutexes(t_context *ctx)
{
	pthread_mutex_destroy(&ctx->cfg->lock_output);
	pthread_mutex_destroy(&ctx->cfg->lock_termination);
}

void	cleanup_resources(t_context *ctx)
{
	if (!ctx)
		return ;
	if (ctx->cfg)
	{
		destroy_fork_mutexes(ctx);
		destroy_coordination_mutexes(ctx);
	}
	if (ctx->philosophers)
		destroy_philosopher_mutexes(ctx);
	if (ctx->mem)
		memory_cleanup(ctx->mem);
}