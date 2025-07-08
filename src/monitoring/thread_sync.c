/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sync.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:42:30 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:42:37 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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