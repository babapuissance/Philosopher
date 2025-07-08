/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:16:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 18:15:20 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo	*create_philosopher_instance(t_context *ctx, size_t id)
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