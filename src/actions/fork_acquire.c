/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_acquire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:59:42 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	handle_single_philosopher(t_philo *philosopher)
{
	if (philosopher->cfg->count_philosophers == 1)
	{
		log_philosopher_state(philosopher, STATE_TAKE_FORK,
			calculate_simulation_time(philosopher));
		precise_delay(philosopher->cfg->deadline_time);
		return (1);
	}
	return (0);
}

static void	acquire_forks_even_id(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->cfg->forks[philosopher->identifier]);
	pthread_mutex_lock(&philosopher->cfg->forks[(philosopher->identifier + 1)
		% philosopher->cfg->count_philosophers]);
}

static void	acquire_forks_odd_id(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->cfg->forks[(philosopher->identifier + 1)
		% philosopher->cfg->count_philosophers]);
	pthread_mutex_lock(&philosopher->cfg->forks[philosopher->identifier]);
}

static void	announce_fork_acquisition(t_philo *philosopher)
{
	log_philosopher_state(philosopher, STATE_TAKE_FORK,
		calculate_simulation_time(philosopher));
	log_philosopher_state(philosopher, STATE_TAKE_FORK,
		calculate_simulation_time(philosopher));
}

short	action_acquire_forks(t_philo *philosopher)
{
	if (handle_single_philosopher(philosopher))
		return (1);
	if (philosopher->identifier % 2 == 0)
		acquire_forks_even_id(philosopher);
	else
		acquire_forks_odd_id(philosopher);
	announce_fork_acquisition(philosopher);
	return (0);
}