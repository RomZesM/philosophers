
#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include <stdio.h> //мжно использовать, но лучше write
typedef struct s_data //сюда кладем стартовые данные
{
	int num_of_phyl;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times;

}t_data;


#endif //PHILOSOFERS_PHILO_H
