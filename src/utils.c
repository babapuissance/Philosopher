/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:50:00 by nbariol-          #+#    #+#             */
/*   Updated: 2025/07/08 15:50:57 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*         TIME UTILS          */

static size_t	get_system_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

size_t	current_timestamp(void)
{
	return (get_system_time_ms());
}

size_t	calculate_simulation_time(t_philo *philosopher)
{
	return (current_timestamp() - philosopher->cfg->simulation_start);
}

size_t	calculate_time_since_meal(t_philo *philosopher)
{
	size_t	current_sim_time;
	size_t	last_meal_time;

	current_sim_time = calculate_simulation_time(philosopher);
	last_meal_time = fetch_meal_timestamp(philosopher);
	return (current_sim_time - last_meal_time);
}

void	precise_delay(size_t duration_ms)
{
	size_t	start_time;

	start_time = current_timestamp();
	while ((current_timestamp() - start_time) < duration_ms)
		usleep(100);
}

/*        OUTPUT UTILS         */

static short	should_suppress_output(t_philo *philosopher, char *state)
{
	if (fetch_termination_state(philosopher->cfg) && state[0] != 'd')
		return (1);
	return (0);
}

void	log_philosopher_state(t_philo *philosopher, char *state, size_t timestamp)
{
	if (should_suppress_output(philosopher, state))
		return ;
	pthread_mutex_lock(&philosopher->cfg->lock_output);
	printf("%zu %zu %s\n", timestamp, philosopher->identifier + 1, state);
	pthread_mutex_unlock(&philosopher->cfg->lock_output);
}

/*        SYNC UTILS           */

size_t	fetch_meal_timestamp(t_philo *philosopher)
{
	size_t	meal_time;

	pthread_mutex_lock(&philosopher->lock_meal_time);
	meal_time = philosopher->timestamp_last_meal;
	pthread_mutex_unlock(&philosopher->lock_meal_time);
	return (meal_time);
}

void	set_meal_timestamp(t_philo *philosopher, size_t new_timestamp)
{
	pthread_mutex_lock(&philosopher->lock_meal_time);
	philosopher->timestamp_last_meal = new_timestamp;
	pthread_mutex_unlock(&philosopher->lock_meal_time);
}

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

size_t	fetch_meal_count(t_philo *philosopher)
{
	size_t	meal_count;

	pthread_mutex_lock(&philosopher->lock_meal_count);
	meal_count = philosopher->meals_consumed;
	pthread_mutex_unlock(&philosopher->lock_meal_count);
	return (meal_count);
}

void	increment_meal_count(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->lock_meal_count);
	philosopher->meals_consumed++;
	pthread_mutex_unlock(&philosopher->lock_meal_count);
}

/*       CLEANUP UTILS         */

static void	destroy_fork_mutexes(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		pthread_mutex_destroy(&ctx->cfg->forks[index]);
		index++;
	}
}

static void	destroy_philosopher_mutexes(t_context *ctx)
{
	size_t	index;

	index = 0;
	while (index < ctx->cfg->count_philosophers)
	{
		if (ctx->philosophers[index])
		{
			pthread_mutex_destroy(&ctx->philosophers[index]->lock_meal_time);
			pthread_mutex_destroy(&ctx->philosophers[index]->lock_meal_count);
		}
		index++;
	}
}

static void	destroy_coordination_mutexes(t_context *ctx)
{
	pthread_mutex_destroy(&ctx->cfg->lock_output);
	pthread_mutex_destroy(&ctx->cfg->lock_termination);
}

void	cleanup_resources(t_context *ctx)
{
	if (!ctx)
		return ;
	if (ctx->cfg)
	{
		destroy_fork_mutexes(ctx);
		destroy_coordination_mutexes(ctx);
	}
	if (ctx->philosophers)
		destroy_philosopher_mutexes(ctx);
	if (ctx->mem)
		memory_cleanup(ctx->mem);
}

/*         DEBUG UTILS         */

void	debug_display_config(t_context *ctx)
{
	printf("Configuration Parameters:\n");
	printf(" count_philosophers: %ld\n", ctx->cfg->count_philosophers);
	printf(" deadline_time: %ld\n", ctx->cfg->deadline_time);
	printf(" duration_eat: %ld\n", ctx->cfg->duration_eat);
	printf(" duration_sleep: %ld\n", ctx->cfg->duration_sleep);
	printf(" meals_required: %ld\n", ctx->cfg->meals_required);
	printf(" termination_flag: %d\n", ctx->cfg->termination_flag);
}
