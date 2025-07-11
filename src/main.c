/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:49:40 by nhara             #+#    #+#             */
/*   Updated: 2025/05/16 14:41:46 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_arg(char **av)
{
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| check_arg(av[1]) == 1)
		return (write(2, "Error: Invalid number of philosophers\n", 36), 1);
	if (ft_atoi(av[2]) <= 0 || check_arg(av[2]) == 1)
		return (write(2, "Error: Invalid time to die\n", 27), 1);
	if (ft_atoi(av[3]) <= 0 || check_arg(av[3]) == 1)
		return (write(2, "Error: Invalid time to eat\n", 27), 1);
	if (ft_atoi(av[4]) <= 0 || check_arg(av[4]) == 1)
		return (write(2, "Error: Invalid time to sleep\n", 29), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || check_arg(av[5]) == 1))
		return (write(2,
				"Error: Invalid number of times each philosopher must eat\n",
				52), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac != 5 && ac != 6)
		return (write(2, "Error: Invalid number of arguments\n", 36), 1);
	if (check_valid_arg(av) == 1)
		return (1);
	program_init(&program, philos);
	forks_init(forks, ft_atoi(av[1]));
	philos_init(philos, &program, forks, av);
	create_threads(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
