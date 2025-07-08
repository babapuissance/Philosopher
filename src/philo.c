/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:41:49 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:42:01 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	validate_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (is_int(argc, argv))
		return (1);
	return (0);
}

static void	display_usage_error(void)
{
	write(2,
		"Usage: ./philo [number_of_philosophers]"
		"[time_to_die] [time_to_eat] [time_to_sleep] "
		"[number_of_times_each_philosopher_must_eat (optional)]\n",
		138);
}

static short	initialize_context(t_context *ctx)
{
	ctx->mem = memory_init();
	if (!ctx->mem)
		return (1);
	return (0);
}

static short	run_simulation(t_context *ctx, char **argv)
{
	if (initialize_simulation(ctx, argv))
		return (1);
	if (launch_watcher(ctx))
		return (1);
	await_threads(ctx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (validate_arguments(argc, argv))
	{
		display_usage_error();
		return (1);
	}
	if (initialize_context(&ctx))
	{
		write(2, "Error: Memory initialization failed.\n", 37);
		return (1);
	}
	if (run_simulation(&ctx, argv))
	{
		cleanup_resources(&ctx);
		write(2, "Error: Simulation failed.\n", 26);
		return (1);
	}
	cleanup_resources(&ctx);
	return (0);
}
