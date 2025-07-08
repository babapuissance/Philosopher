/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:39:10 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 18:16:23 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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