/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:44:19 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
