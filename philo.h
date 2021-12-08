
#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <stdio.h> //мжно использовать, но лучше write

struct s_p_inf;


typedef struct s_data //сюда кладем стартовые данные
{
	int num_of_phyl;
	unsigned long time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times;//сколько раз поел
	struct s_p_inf * p_inf;
	pthread_mutex_t * forks; //указатель для хранения всех вилок = кол-во философов
	pthread_t *phylosophers;
	unsigned long start_time;//время запуска философоф

}t_data;

typedef struct s_p_inf
{
	int name;
	int left_fork; //какая вилка ПРИНАДЛЕЖИТ конкретному философУ
	int right_fork;//используется как индекс для доступа к массиву мьютексов
	t_data * data;
	unsigned long last_eat;//время когда поел, для проверки смерти
	pthread_mutex_t eat_now; //мютекс для блокирование ф. на время еды
	int dead_flag; //флаг для проверки на смерть
}t_p_inf;


unsigned long	ft_get_time_in_ms(void);
void			ft_mod_usleep(int sleep_time);
int				ft_table_init(t_data * data);
int				ft_phyl_init_data(t_data * data);
int				ft_phil_thr_join(t_data *data);
int				ft_philosophers_init(t_data *data);
int				ft_max_fork(t_p_inf * inf);
int 			ft_min_fork(t_p_inf * inf);
int				ft_taking_forks(t_p_inf * inf);
int				ft_eating(t_p_inf * inf);
int				ft_print_message(t_p_inf * inf, unsigned long int time, char * msg);
int				ft_thinking(t_p_inf * inf);
int				ft_waiting(t_p_inf * inf);
void * 			ft_d_check(void * arg);//для потока, проверяющего смерть ф.
void * 			ft_simulation (void * arg);

#endif //PHILOSOFERS_PHILO_H
