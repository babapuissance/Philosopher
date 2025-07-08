/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 18:14:57 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static short	should_suppress_output(t_philo *philosopher, char *state)
{
	if (fetch_termination_state(philosopher->cfg) && state[0] != 'd')
		return (1);
	return (0);
}

void	log_philosopher_state(t_philo *philosopher, char *state,
	size_t timestamp)
{
	if (should_suppress_output(philosopher, state))
		return ;
	pthread_mutex_lock(&philosopher->cfg->lock_output);
	printf("%zu %zu %s\n", timestamp, philosopher->identifier + 1, state);
	pthread_mutex_unlock(&philosopher->cfg->lock_output);
}
