/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restaurant.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:19:12 by jaurasma          #+#    #+#             */
/*   Updated: 2023/04/19 16:07:32 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	feed_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&(philo->rules->forks[philo->fork_right_num]));
	print_status(philo->rules, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(philo->rules->forks[philo->fork_left_num]));
	print_status(philo->rules, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(philo->rules->time_lock));
	print_status(philo->rules, philo->philo_id, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->rules->time_lock));
	smart_usleep((long long)(philo->rules->tte), philo);
	(philo->meal_num)++;
	pthread_mutex_unlock(&(philo->rules->forks[philo->fork_left_num]));
	pthread_mutex_unlock(&(philo->rules->forks[philo->fork_right_num]));
}

//how long should the modulo 2 guys wait
void	*routine(void *arg)
{
	t_rules	*rules;
	t_philo	*philo;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (philo->philo_id % 2)
		smart_usleep(rules->tte / 2, philo);
	while (death_status(rules, 0) == 0)
	{
		feed_philosopher(philo);
		if (rules->eat_check == 1)
			return (NULL);
		print_status(rules, philo->philo_id, "is sleeping");
		smart_usleep((long long)(rules->tts), philo);
		print_status(rules, philo->philo_id, "is thinking");
		usleep(500);
	}
	return (NULL);
}

void	exit_restaurant(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(rules->time_lock));
	pthread_mutex_destroy(&(rules->write_lock));
}

int	open_restaurant(t_rules *rules, int i, int j)
{
	t_philo	*philo;

	philo = rules->philosopher;
	rules->timestamp_start = get_time();
	while (++i < rules->philo_num)
	{
		print_status(rules, philo[i].philo_id, "is thinking");
		philo[i].last_meal = rules->timestamp_start;
		if (pthread_create(&(philo[i].tid), NULL, &routine, &(philo[i])))
		{
			printf("thread creation failed!\n");
			return (1);
		}
	}
	death_monitoring(rules, rules->philosopher, -1, 0);
	exit_restaurant(rules);
	while (++j < rules->philo_num)
	{
		if (pthread_join(philo[j].tid, NULL))
		{
			printf("joining failed!\n");
			return (1);
		}
	}
	return (0);
}
