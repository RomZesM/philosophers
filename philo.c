//
// Created by RomZes on 21.11.2021.
//
/*
 * 1- number of filosofers
 * 2- time_to_die - ms - время, через которое философ умирает, если не начал есть
 * 3 - time_to_eat - ms - время чтобы поесть, в это время у ф. должно быть 2 вилки
 * 4 - time_to_sleep - ms - время которое философ проведет во сне
 * 5 - number_of_times_each_philosopher_must_eat - сколько раз должны философы поесть, чтобы завершить программу, иначе должна рабоать,
 * пока философ не умрет
 *
 */

#include "philo.h"

int main(int argc, char * argv[])
{
	t_data data; //структура со стоартовыми параметрами в идеале надо инициализировать NULL и выделить память
	if (argc == 5)
	{
		data.num_of_phyl = atoi(argv[1]);
		data.time_to_die = atoi(argv[2]);
		data.time_to_eat = atoi(argv[3]);
		data.time_to_sleep = atoi(argv[4]);
	}

	return 0;
}