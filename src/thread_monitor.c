/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:54:28 by nhara             #+#    #+#             */
/*   Updated: 2025/05/15 12:23:30 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(char *status, t_philo *philo, int id)
{
	size_t	time;

	//ミューテックス（書き込みロック）を取得
	pthread_mutex_lock(philo->write_lock);
	//経過時間の計算
	time = get_ms_time() - philo->start_time;
	//哲学者が死亡していない場合のみメッセージを表示
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, status);
	pthread_mutex_unlock(philo->write_lock);
}

//ある哲学者が死亡したかどうかを確認する
int	check_if_one_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	//死亡条件の確認（最後の食事からの経過時間がtimetodieを超えている＆食事中でない）
	if (get_ms_time() - philo->last_meal >= time_to_die && philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		//死亡したを返す
		return (1);
	}
	//死亡していないを返す
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

//全哲学者を確認し、誰かが死亡したかどうかを確認する
int	check_all_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (check_if_one_dead(&philos[i], philos[i].time_to_die))
		{
			print_status("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1; //死亡フラグを立てる
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1); //死亡した
		}
		i++;
	}
	return (0); //死亡していない
}

int	check_all_if_ate(t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	//食べ終えた哲学者の数
	count = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0); //無制限に食事を続ける場合は、全員が食べたかどうかを確認しない
	//全員が指定回数食事をしたか確認
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		//哲学者の食事回数が指定回数以上が確認
		if (philos[i].meals_eaten >= philos[0].num_times_to_eat)
			count++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (count == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*(philos[0].dead) = 1; //死亡フラグを立て、全員食べたという状態を全スレッドに通知
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1); //全員が食べた
	}
	return (0); //全員が食べていない場合、ループを続行
}

// シュミレーターの終了条件を確認
void	*monitor(void *pointer)
{
	t_philo	*philos;

	//構造体ポインタにキャスト
	philos = (t_philo *)pointer;
	while (1) //無限ループ
		if (check_all_if_dead(philos) == 1 || check_all_if_ate(philos) == 1)
			break ; //死亡したか、全員が食べた場合、ループを終了
	return (pointer);
}
