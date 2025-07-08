/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rest_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:38:40 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:38:49 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	validate_resting_conditions(t_philo *philosopher)
{
	if (fetch_termination_state(philosopher->cfg))
		return (1);
	return (0);
}

static void	announce_resting_state(t_philo *philosopher)
{
	log_philosopher_state(philosopher, STATE_SLEEPING,
		calculate_simulation_time(philosopher));
}

short	action_rest(t_philo *philosopher)
{
	if (validate_resting_conditions(philosopher))
		return (1);
	announce_resting_state(philosopher);
	precise_delay(philosopher->cfg->duration_sleep);
	return (0);
}

static short	validate_contemplation_conditions(t_philo *philosopher)
{
	if (fetch_termination_state(philosopher->cfg))
		return (1);
	return (0);
}

static void	announce_contemplation_state(t_philo *philosopher)
{
	log_philosopher_state(philosopher, STATE_THINKING,
		calculate_simulation_time(philosopher));
}

static size_t	calculate_contemplation_duration(t_philo *philosopher)
{
	return (philosopher->cfg->duration_sleep);
}

short	action_contemplate(t_philo *philosopher)
{
	size_t	contemplation_time;

	if (validate_contemplation_conditions(philosopher))
		return (1);
	announce_contemplation_state(philosopher);
	contemplation_time = calculate_contemplation_duration(philosopher);
	precise_delay(contemplation_time);
	return (0);
} 