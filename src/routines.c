/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 15:50:57 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*         FORK ACTIONS        */

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

static void	release_forks_even_id(t_philo *philosopher)
{
	pthread_mutex_unlock(&philosopher->cfg->forks[philosopher->identifier]);
	pthread_mutex_unlock(&philosopher->cfg->forks[(philosopher->identifier + 1)
		% philosopher->cfg->count_philosophers]);
}

static void	release_forks_odd_id(t_philo *philosopher)
{
	pthread_mutex_unlock(&philosopher->cfg->forks[(philosopher->identifier + 1)
		% philosopher->cfg->count_philosophers]);
	pthread_mutex_unlock(&philosopher->cfg->forks[philosopher->identifier]);
}

short	action_release_forks(t_philo *philosopher)
{
	if (philosopher->identifier % 2 == 0)
		release_forks_even_id(philosopher);
	else
		release_forks_odd_id(philosopher);
	return (0);
}

/*        MEAL ACTIONS         */

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

/*        REST ACTIONS         */

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

/*      THINKING ACTIONS       */

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

/*      LIFECYCLE CONTROL      */

static short	check_simulation_status(t_philo *philosopher)
{
	return (fetch_termination_state(philosopher->cfg));
}

static short	execute_dining_sequence(t_philo *philosopher)
{
	if (action_acquire_forks(philosopher))
		return (1);
	if (action_consume_meal(philosopher))
	{
		action_release_forks(philosopher);
		return (1);
	}
	if (action_release_forks(philosopher))
		return (1);
	return (0);
}

static short	execute_rest_sequence(t_philo *philosopher)
{
	if (action_rest(philosopher))
		return (1);
	if (action_contemplate(philosopher))
		return (1);
	return (0);
}

void	*action_lifecycle(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	while (!check_simulation_status(philosopher))
	{
		if (execute_dining_sequence(philosopher))
			break ;
		if (execute_rest_sequence(philosopher))
			break ;
	}
	return (NULL);
}
