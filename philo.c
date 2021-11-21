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

unsigned long    ft_get_time_in_ms(void) //функция получения текущего времени in ms (dan)
{
	struct timeval  cur_time; //структура куда gettimeofday записывает данные о времени

	gettimeofday(&cur_time, NULL); //0-удачно, 1 ошибка

	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000); //секунды на 1000 = миллисек., микросекунды наоборот увеличиваем.
}

void ft_mod_usleep(int sleep_time)//модифицирвоанная функция ожидания вместо usleep, чтобы не прерывылась случайным сигналом
{								//получаем время в миллисекундах, сколько надо подождать.
	unsigned long int i;

	i = ft_get_time_in_ms();
	while (ft_get_time_in_ms() < i + sleep_time)
		usleep(50); //ждем по 50 микросекунд
}

int main(int argc, char * argv[])
{
	t_data data; //структура со стоартовыми параметрами в идеале надо инициализировать NULL и выделить память
	if (argc == 5)//тут добавть защиту ввоода
	{
		data.num_of_phyl = atoi(argv[1]);
		data.time_to_die = atoi(argv[2]);
		data.time_to_eat = atoi(argv[3]);
		data.time_to_sleep = atoi(argv[4]);
	}

	return 0;
}