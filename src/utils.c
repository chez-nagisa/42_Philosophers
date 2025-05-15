/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:22:27 by nhara             #+#    #+#             */
/*   Updated: 2025/05/15 12:07:06 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	destroy_all(char *message, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
// usleepはマイクロ秒単位でスリープから、指定時間が長いと誤差が大きい。そのため自作する。
int	ft_usleep(size_t ms)
{
	size_t	start_time;

	// 現在の時刻を取得
	start_time = get_ms_time();
	// 指定された時間だけスリープ
	while (get_ms_time() - start_time < ms)
		usleep(500);
	return (0);
}
size_t	get_ms_time(void)
{
	struct timeval	time;

	// 現在時刻を秒（s）とマイクロ秒（μs）で取得
	if (gettimeofday(&time, NULL) == -1) // 失敗した場合
		write(2, "Error: gettimeofday failed\n", 28);
	// 秒とマイクロ秒をミリ秒に変換
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
