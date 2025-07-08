/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:15:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 18:14:44 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	get_system_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

size_t	current_timestamp(void)
{
	return (get_system_time_ms());
}

size_t	calculate_simulation_time(t_philo *philosopher)
{
	return (current_timestamp() - philosopher->cfg->simulation_start);
}

size_t	calculate_time_since_meal(t_philo *philosopher)
{
	size_t	current_sim_time;
	size_t	last_meal_time;

	current_sim_time = calculate_simulation_time(philosopher);
	last_meal_time = fetch_meal_timestamp(philosopher);
	return (current_sim_time - last_meal_time);
}

void	precise_delay(size_t duration_ms)
{
	size_t	start_time;

	start_time = current_timestamp();
	while ((current_timestamp() - start_time) < duration_ms)
		usleep(100);
} 