/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:06:32 by jaurasma          #+#    #+#             */
/*   Updated: 2023/04/19 16:19:23 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_philosopher_death(t_rules *rules, t_philo *philo, int i)
{
	pthread_mutex_lock(&(rules->time_lock));
	if ((get_time() - philo[i].last_meal) > (long long)rules->ttd)
	{
		print_status(rules, philo[i].philo_id, "died");
		death_status(rules, 1);
	}
	pthread_mutex_unlock(&(rules->time_lock));
}

void	wait_for_philosophers(t_rules *rules, t_philo *philo, int *i)
{
	while (++(*i) < rules->philo_num && death_status(rules, 0) == 0)
	{
		check_philosopher_death(rules, philo, *i);
		usleep(1000);
	}
	*i = -1;
}

void	check_if_all_philosophers_ate(t_rules *rules, t_philo *philo, int *j)
{
	if (rules->how_hungry != -1 && \
		philo[rules->philo_num - 1].meal_num == rules->how_hungry)
	{
		while (*j < rules->philo_num)
		{
			if (philo[*j].meal_num == rules->how_hungry)
				(*j)++;
			if (*j == rules->philo_num - 1)
			{
				rules->eat_check = 1;
				break ;
			}
		}
	}
}

void	death_monitoring(t_rules *rules, t_philo *philo, int i, int j)
{
	while (rules->eat_check == 0)
	{
		wait_for_philosophers(rules, philo, &i);
		if (rules->death_status == 1)
			break ;
		pthread_mutex_lock(&(rules->time_lock));
		check_if_all_philosophers_ate(rules, philo, &j);
		pthread_mutex_unlock(&(rules->time_lock));
		if (rules->eat_check == 1)
			break ;
	}
}
