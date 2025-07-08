/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:40:20 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:44:19 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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