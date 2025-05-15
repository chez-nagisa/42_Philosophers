/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:20:39 by nhara             #+#    #+#             */
/*   Updated: 2025/05/14 09:45:34 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock); //ロックする
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock); //ロックを解除
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0) //偶数IDの哲学者を少し遅れて開始させることでデッドロックを防ぐ
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
	return (pointer);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	// program->philosは監視対象（全ての哲学者）
	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destroy_all("Error: Thread creation failed", program, forks);
	i = 0;
	//各哲学者のスレッドを作成
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destroy_all("Error: Thread creation failed", program, forks);
		i++;
	}
	i = 0;
	//監視スレッドが正常に終了しなかった場合
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Error: Thread join failed", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		//各哲学者のスレッドが正常に終了しなかった場合
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("Error: Thread join failed", program, forks);
		i++;
	}
	return (0);
}
