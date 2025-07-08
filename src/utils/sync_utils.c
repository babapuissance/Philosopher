/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:39:10 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:39:34 by nbariol-         ###   ########.fr       */
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

short	fetch_termination_state(t_config *cfg)
{
	short	current_state;

	pthread_mutex_lock(&cfg->lock_termination);
	current_state = cfg->termination_flag;
	pthread_mutex_unlock(&cfg->lock_termination);
	return (current_state);
}

void	set_termination_state(t_config *cfg, int new_state)
{
	pthread_mutex_lock(&cfg->lock_termination);
	cfg->termination_flag = new_state;
	pthread_mutex_unlock(&cfg->lock_termination);
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