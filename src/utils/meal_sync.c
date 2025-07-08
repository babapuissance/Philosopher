/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_sync.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:10:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 18:14:09 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	fetch_meal_timestamp(t_philo *philosopher)
{
	size_t	meal_time;

	pthread_mutex_lock(&philosopher->lock_meal_time);
	meal_time = philosopher->timestamp_last_meal;
	pthread_mutex_unlock(&philosopher->lock_meal_time);
	return (meal_time);
}

void	set_meal_timestamp(t_philo *philosopher, size_t new_timestamp)
{
	pthread_mutex_lock(&philosopher->lock_meal_time);
	philosopher->timestamp_last_meal = new_timestamp;
	pthread_mutex_unlock(&philosopher->lock_meal_time);
}

size_t	fetch_meal_count(t_philo *philosopher)
{
	size_t	meal_count;

	pthread_mutex_lock(&philosopher->lock_meal_count);
	meal_count = philosopher->meals_consumed;
	pthread_mutex_unlock(&philosopher->lock_meal_count);
	return (meal_count);
}

void	increment_meal_count(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->lock_meal_count);
	philosopher->meals_consumed++;
	pthread_mutex_unlock(&philosopher->lock_meal_count);
} 