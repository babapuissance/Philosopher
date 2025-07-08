/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:40:50 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 18:16:23 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	allocate_philosophers_array(t_context *ctx)
{
	ctx->philosophers = malloc(sizeof(t_philo)
		* ctx->cfg->count_philosophers);
	if (!ctx->philosophers)
		return (1);
	if (memory_add(ctx->mem, ctx->philosophers))
		return (1);
	return (0);
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