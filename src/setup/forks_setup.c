/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:40:40 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:44:19 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	allocate_forks_array(t_context *ctx)
{
	ctx->cfg->forks = malloc(sizeof(pthread_mutex_t) *
		ctx->cfg->count_philosophers);
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