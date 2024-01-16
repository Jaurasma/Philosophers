/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:00:52 by jaurasma          #+#    #+#             */
/*   Updated: 2023/03/31 18:17:20 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > 2147483647)
			return (-1);
		if (res * sign < -2147483648)
			return (0);
		str++;
	}
	return (res * sign);
}

void	print_status(t_rules *rules, int phil_id, char *str)
{
	pthread_mutex_lock(&(rules->write_lock));
	if (death_status(rules, 0) == 0)
		printf("%lli %d %s\n", get_time() - rules->timestamp_start, \
		phil_id + 1, str);
	pthread_mutex_unlock(&(rules->write_lock));
	return ;
}

long long	get_time(void)
{
	struct timeval	time;
	long long		result;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (result);
}

void	smart_usleep(long long time_to, t_philo *philo)
{
	philo->time = get_time();
	philo->end_time = philo->time + time_to - 1;
	while (get_time() <= philo->end_time)
		usleep(500);
}

int	death_status(t_rules *rules, int flag)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(rules->time_lock2));
	if (flag == 1)
		rules->death_status = 1;
	ret = rules->death_status;
	pthread_mutex_unlock(&(rules->time_lock2));
	return (ret);
}
