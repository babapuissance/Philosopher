/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:41:49 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 15:46:38 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}					t_node;

typedef struct s_memory
{
	t_node			*head;
}					t_memory;

typedef struct s_config
{
	size_t			count_philosophers;
	size_t			deadline_time;
	size_t			duration_eat;
	size_t			duration_sleep;
	size_t			meals_required;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_forks;
	size_t			simulation_start;
	volatile int	termination_flag;
	pthread_mutex_t	lock_termination;
	pthread_mutex_t	lock_output;
}					t_config;

typedef struct s_philo
{
	size_t			identifier;
	pthread_t		thread;
	size_t			timestamp_last_meal;
	pthread_mutex_t	lock_meal_time;
	size_t			meals_consumed;
	pthread_mutex_t	lock_meal_count;
	struct s_config	*cfg;
}					t_philo;

typedef struct s_context
{
	t_config		*cfg;
	t_memory		*mem;
	t_philo			**philosophers;
	pthread_t		watcher_thread;
}					t_context;

#endif