/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 17:44:19 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

short	initialize_simulation(t_context *ctx, char **argv)
{
	if (setup_config(ctx, argv))
		return (1);
	if (setup_forks(ctx))
		return (1);
	if (setup_philosophers(ctx))
		return (1);
	return (0);
}
