/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:38:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:59:55 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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