/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:49:40 by nhara             #+#    #+#             */
/*   Updated: 2025/05/12 13:32:21 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int check_arg(char *av)
{
	int i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int check_valid_arg(char **av)
{
	if(ft_atoi(av[1] > PHILO_MAX) || ft_atoi(av[1])<= 0 || check_arg(av[1]) == 1)
		return(write(2, "Error: Invalid number of philosophers\n", 36), 1);
	if(ft_atoi(av[2]) <= 0 || check_arg(av[2]) == 1)
		return(write(2, "Error: Invalid time to die\n", 27), 1);
	if(ft_atoi(av[3]) <= 0 || check_arg(av[3]) == 1)
		return(write(2, "Error: Invalid time to eat\n", 27), 1);
	if(ft_atoi(av[4]) <= 0 || check_arg(av[4]) == 1)
		return(write(2, "Error: Invalid time to sleep\n", 29), 1);
	if(av[5] && (ft_atoi(av[5]) <= 0 || check_arg(av[5]) == 1))
		return(write(2, "Error: Invalid number of times each philosopher must eat\n", 52), 1);
	return (0);
}

int main(int ac, char **av){
	if(ac != 5 && ac != 6)
		return(write(2, "Error: Invalid number of arguments\n", 36), 1);
	if(check_valid_arg(av) == 1)
		return (1);
	
}
