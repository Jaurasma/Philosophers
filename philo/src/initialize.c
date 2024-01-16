/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:23:24 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/09 18:19:55 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_exit(t_rules *rules)
{
	if (rules->philo_num == 1)
	{
		printf("0 1 is thinking\n");
		usleep(rules->ttd);
		printf("%d 1 died\n", rules->ttd);
		return (1);
	}
	printf("phil num = 1 - 250 && ttd, tte, tts > 0\n");
	return (1);
}

int	init_everything(t_rules *rules, char **argv)
{
	rules->philo_num = ft_atoi(argv[1]);
	rules->ttd = ft_atoi(argv[2]);
	rules->tte = ft_atoi(argv[3]);
	rules->tts = ft_atoi(argv[4]);
	rules->rounds = 0;
	rules->death_status = 0;
	rules->eat_check = 0;
	if (rules->philo_num <= 1 || rules->ttd <= 0 || \
	rules->tte <= 0 || rules->tts <= 0 || rules->philo_num > 250)
		return (error_exit(rules));
	if (argv[5])
	{
		rules->how_hungry = ft_atoi(argv[5]);
		if (rules->how_hungry < 1)
			return (1);
	}
	else
		rules->how_hungry = -1;
	if (init_mutex(rules) == 1)
		return (1);
	init_phils(rules);
	return (0);
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num - 1)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(rules->time_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(rules->time_lock2), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(rules->write_lock), NULL) != 0)
		return (1);
	return (0);
}

void	init_phils(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		rules->philosopher[i].philo_id = i;
		rules->philosopher[i].fork_right_num = i;
		rules->philosopher[i].fork_left_num = (i + 1) % rules->philo_num;
		rules->philosopher[i].last_meal = 0;
		rules->philosopher[i].meal_num = 0;
		rules->philosopher[i].time = 0;
		rules->philosopher[i].end_time = 0;
		rules->philosopher[i].rules = rules;
		i++;
	}
}
