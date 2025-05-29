/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhara <nhara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:50:41 by nhara             #+#    #+#             */
/*   Updated: 2025/05/16 14:31:44 by nhara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define PHILO_MAX 200
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;

	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

int					ft_strlen(char *str);
int					ft_atoi(char *str);
void				input_init(t_philo *philo, char **av);
void				philos_init(t_philo *philos, t_program *program,
						pthread_mutex_t *forks, char **av);
void				forks_init(pthread_mutex_t *forks, int num_of_philos);
void				program_init(t_program *program, t_philo *philos);
void				*monitor(void *pointer);
int					dead_loop(t_philo *philo);
void				print_status(char *status, t_philo *philo, int id);
int					create_threads(t_program *program, pthread_mutex_t *forks);
void				destroy_all(char *message, t_program *program,
						pthread_mutex_t *forks);
int					ft_usleep(size_t ms);
size_t				get_ms_time(void);
void				think(t_philo *philo);
void				rest(t_philo *philo);
void				eat(t_philo *philo);
int					main(int ac, char **av);

#endif