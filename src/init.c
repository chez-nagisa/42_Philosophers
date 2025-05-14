/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:54:26 by nhara             #+#    #+#             */
/*   Updated: 2025/05/14 09:57:47 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//ユーザーの入力を設定
void	input_init(t_philo *philo, char **av, int ac)
{
	philo->num_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_times_to_eat = ft_atoi(av[5]);
	else
		//無制限に食事を続ける
		philo->num_times_to_eat = -1;
}

void	philos_init(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1])) //哲学者の人数分
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		input_init(&philos[i], av);           //各哲学者に各時間の設定
		philos[i].start_time = get_ms_time(); //シュミレーション開始時刻
		philos[i].last_meal = get_ms_time();  //最後に食事を開始した時間
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag; //誰かが死んだら、皆がそれを確認
		philos[i].l_fork = &forks[i];         //左手に自分のフォークを持つ
		if (i == 0)                           //はじめの哲学者は、最後のフォークを右手に持つ
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			//自分の左の哲学者のフォークを右手に持つ。i+1にすると、最後の哲学者は存在しないフォークを持とうとしてしまう＝アクセスしてはいけないメモリにアクセス
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	forks_init(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL); //各フォーク(ミューテックス)の初期化
		i++;
	}
}

void	program_init(t_program *program, t_philo *philos)
{
	program->dead_flag = 0; //哲学者全体の死亡フラグ
	program->philos = philos;
	pthread_mutex_init(&program->dead_lock, NULL);  //死亡フラグの初期化
	pthread_mutex_init(&program->meal_lock, NULL);  //食事回数の初期化
	pthread_mutex_init(&program->write_lock, NULL); //標準出力の初期化
}
