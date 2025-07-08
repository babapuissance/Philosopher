/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:42:51 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_create(&ctx->watcher_thread, NULL, surveillance_routine,
			ctx) != 0)
		return (1);
	return (0);
}
