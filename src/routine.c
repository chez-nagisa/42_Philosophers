/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:08:58 by nhara             #+#    #+#             */
/*   Updated: 2025/05/14 15:32:14 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_status("is thinking", philo, philo->id);
}

void	rest(t_philo *philo)
{
	print_status("is sleeping", philo, philo->id);
}

void	eat(t_philo *philo)
{
	// 右のフォークを取得
	pthread_mutex_lock(philo->r_fork);
	print_status("has taken a fork", philo, philo->id);
	// 1人の場合は確実に死ぬ
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	// 左のフォークを取得
	pthread_mutex_lock(philo->l_fork);
	print_status("has taken a fork", philo, philo->id);
	// 食事開始
	philo->eating = 1;
	print_status("is eating", philo, philo->id);
	// 食事状態を記録
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_ms_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	// 食事時間中待機
	ft_usleep(philo->time_to_eat);
	// 食事終了
	philo->eating = 0;
	//フォークの解放
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
