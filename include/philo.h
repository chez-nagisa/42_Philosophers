/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:50:41 by nhara             #+#    #+#             */
/*   Updated: 2025/05/15 12:20:09 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define PHILO_MAX 300 // 200じゃないの？
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t thread;     // 哲学者のスレッドID（pthreadのスレッドオブジェクト）
	int id;               // 哲学者のID（1から哲学者の数までの整数）
	int eating;           // 現在食事中かを示すフラグ（1: 食事中, 0: それ以外）
	int meals_eaten;      // この哲学者がこれまでに食べた回数
	size_t last_meal;     // 最後に食事を開始した時刻（ミリ秒）
	size_t time_to_die;   // 死ぬまでの最大許容時間（ミリ秒）
	size_t time_to_eat;   // 食事にかかる時間（ミリ秒）
	size_t time_to_sleep; // 睡眠にかかる時間（ミリ秒）
	size_t start_time;    // シミュレーションの開始時刻（ミリ秒）
	int num_of_philos;    // 哲学者の総数
	int num_times_to_eat; // 各哲学者が食べる必要のある回数（-1 なら無制限）
	int *dead;            // 死亡フラグ（プログラム全体で共有する変数へのポインタ）

	// ミューテックス（スレッド間の排他制御用）
	pthread_mutex_t *r_fork;     // 右側のフォーク（ミューテックス）
	pthread_mutex_t *l_fork;     // 左側のフォーク（ミューテックス）
	pthread_mutex_t *write_lock; // 出力の排他制御（コンソールへの書き込み）
	pthread_mutex_t *dead_lock;  // 死亡フラグの排他制御
	pthread_mutex_t *meal_lock;  // 食事回数・最後の食事時間の排他制御
}		t_philo;

typedef struct s_program
{
	int dead_flag;              // 哲学者全体の死亡フラグ（1: 死亡あり, 0: 全員生存）
	pthread_mutex_t dead_lock;  // 死亡フラグの排他制御（ミューテックス）
	pthread_mutex_t meal_lock;  // 全哲学者の食事回数の排他制御（ミューテックス）
	pthread_mutex_t write_lock; // 標準出力の排他制御（ミューテックス）
	t_philo *philos;            // 哲学者（t_philo）の配列
}		t_program;

int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	input_init(t_philo *philo, char **av);
void	philos_init(t_philo *philos, t_program *program, pthread_mutex_t *forks,
			char **av);
void	forks_init(pthread_mutex_t *forks, int num_of_philos);
void	program_init(t_program *program, t_philo *philos);
void	*monitor(void *pointer);
int		dead_loop(t_philo *philo);
void	print_status(char *status, t_philo *philo, int id);
int		create_threads(t_program *program, pthread_mutex_t *forks);
void	destroy_all(char *message, t_program *program, pthread_mutex_t *forks);
int		ft_usleep(size_t ms);
size_t	get_ms_time(void);
void	think(t_philo *philo);
void	rest(t_philo *philo);
void	eat(t_philo *philo);
int		main(int ac, char **av);

#endif