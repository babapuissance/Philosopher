/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:38:30 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:44:19 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	validate_eating_conditions(t_philo *philosopher)
{
	if (fetch_termination_state(philosopher->cfg))
		return (1);
	return (0);
}

static void	record_meal_consumption(t_philo *philosopher)
{
	size_t	current_time;

	current_time = calculate_simulation_time(philosopher);
	set_meal_timestamp(philosopher, current_time);
	increment_meal_count(philosopher);
}

static void	announce_eating_state(t_philo *philosopher)
{
	log_philosopher_state(philosopher, STATE_EATING,
		calculate_simulation_time(philosopher));
}

short	action_consume_meal(t_philo *philosopher)
{
	if (validate_eating_conditions(philosopher))
		return (1);
	record_meal_consumption(philosopher);
	announce_eating_state(philosopher);
	precise_delay(philosopher->cfg->duration_eat);
	return (0);
} 