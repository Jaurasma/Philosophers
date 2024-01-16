/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:47:28 by jaurasma          #+#    #+#             */
/*   Updated: 2023/04/19 16:52:35 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define  PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

struct	s_rules;
typedef struct s_philo
{
	pthread_t		tid;
	int				philo_id;
	int				fork_right_num;
	int				fork_left_num;
	long long		last_meal;
	int				meal_num;
	long long		time;
	long long		end_time;
	struct s_rules	*rules;
}	t_philo;

typedef struct s_rules
{
	int				philo_num;
	int				ttd;
	int				tte;
	int				tts;
	int				rounds;
	int				death_status;
	int				how_hungry;
	long long		timestamp_start;
	int				eat_check;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	time_lock2;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks[250];
	t_philo			philosopher[250];
}	t_rules;

int			ft_atoi(const char *str);
int			init_everything(t_rules *rules, char **argv);
int			init_mutex(t_rules *rules);
void		init_phils(t_rules *rules);
int			open_restaurant(t_rules *rules, int i, int j);
long long	get_time(void);
void		*routine(void *arg);
void		print_status(t_rules *rules, int phil_id, char *str);
void		exit_restaurant(t_rules *rules);
int			death_status(t_rules *rules, int flag);
void		smart_usleep(long long time_to, t_philo *philo);
int			error_exit(t_rules *rules);
void		death_monitoring(t_rules *rules, t_philo *philo, int i, int j);
void		check_if_all_philosophers_ate(t_rules *rules, \
t_philo *philo, int *j);
void		wait_for_philosophers(t_rules *rules, t_philo *philo, int *i);
void		check_philosopher_death(t_rules *rules, t_philo *philo, int i);

#endif
