/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:47:40 by jaurasma          #+#    #+#             */
/*   Updated: 2023/03/31 18:18:08 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
	{
		printf("How to use: [philo num] [ttd] [tte] [tts] [how many times]\n");
		return (1);
	}
	if (init_everything(&rules, argv) == 1)
		return (1);
	if (open_restaurant(&rules, -1, -1) == 1)
		return (1);
	return (0);
}
