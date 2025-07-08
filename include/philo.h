/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:41:49 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 18:15:47 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*           DEFINE            */
# define STATE_TAKE_FORK "has taken a fork"
# define STATE_EATING "is eating"
# define STATE_SLEEPING "is sleeping"
# define STATE_THINKING "is thinking"
# define STATE_DECEASED "died"

# define VALIDATION_MIN 1

# define INT_MIN -2147483648
# define INT_MAX 2147483647

/*        CONFIGURATION        */
short		setup_forks(t_context *ctx);
short		setup_config(t_context *ctx, char **argv);
short		setup_philosophers(t_context *ctx);
short		initialize_simulation(t_context *ctx, char **argv);
t_philo		*create_philosopher_instance(t_context *ctx, size_t id);

/*          WATCHER            */
short		launch_watcher(t_context *ctx);
short		await_threads(t_context *ctx);
short		validate_meal_times(t_context *ctx);
short		validate_meal_counts(t_context *ctx);

/*          ACTIONS            */
void		*action_lifecycle(void *arg);
short		action_acquire_forks(t_philo *philosopher);
short		action_consume_meal(t_philo *philosopher);
short		action_release_forks(t_philo *philosopher);
short		action_rest(t_philo *philosopher);
short		action_contemplate(t_philo *philosopher);

/*          HELPERS            */
// Mutex Handlers
size_t		fetch_meal_timestamp(t_philo *philosopher);
void		set_meal_timestamp(t_philo *philosopher, size_t new_value);
short		fetch_termination_state(t_config *cfg);
void		set_termination_state(t_config *cfg, int new_value);
void		increment_meal_count(t_philo *philosopher);
size_t		fetch_meal_count(t_philo *philosopher);
// Utilities
void		cleanup_resources(t_context *ctx);
void		precise_delay(size_t time);
size_t		current_timestamp(void);
size_t		calculate_time_since_meal(t_philo *philosopher);
size_t		calculate_simulation_time(t_philo *philosopher);
void		log_philosopher_state(t_philo *philosopher, char *state,
				size_t timestamp);

/*            DEBUG            */
void		debug_display_config(t_context *ctx);

/*          LIBRARY            */
long long	ft_atoll(const char *str);
short		is_int(size_t size, char **arg);
size_t		ft_strlen(char *s);
void		cleanup_resources(t_context *ctx);

/*       MEMORY MANAGER        */
t_memory	*memory_init(void);
short		memory_add(t_memory *mem, void *ptr);
short		memory_remove_one(t_memory *mem, void *ptr);
void		memory_cleanup(t_memory *mem);
void		memory_debug_display(t_memory *mem);

#endif