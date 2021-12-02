//
// Created by RomZes on 21.11.2021.
//
/*
 * 1- number of phylosofers
 * 2- time_to_die - ms - время, через которое философ умирает, если не начал есть
 * 3 - time_to_eat - ms - время чтобы поесть, в это время у ф. должно быть 2 вилки
 * 4 - time_to_sleep - ms - время которое философ проведет во сне
 * 5 - number_of_times_each_philosopher_must_eat - сколько раз должны философы поесть, чтобы завершить программу, иначе должна рабоать,
 * пока философ не умрет
 *
 */

#include "philo.h"


void * ft_simulation (void * arg)
{
	t_p_inf * inf;
	inf = (t_p_inf *)arg;
	pthread_mutex_lock(&inf->data->forks[inf->left_fork]);
	pthread_mutex_lock(&inf->data->forks[inf->right_fork]);


		printf("Philosopher eat: %d, lf-%d, rf-%d\n", inf->name, inf->left_fork, inf->right_fork);
		ft_mod_usleep(inf->data->time_to_eat); //ждем время чтобы поесть

	pthread_mutex_unlock(&inf->data->forks[inf->right_fork]);
	pthread_mutex_unlock(&inf->data->forks[inf->left_fork]);
	return (NULL);
}

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

int ft_table_init(t_data * data)//инициализируем массив вилок
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_phyl);//защита и очистка ?!
	while (i < data->num_of_phyl)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		printf("fork %d init\n", i);
		i++;
	}
	return (0);
}

int ft_phyl_init_data(t_data * data)
{
	int i;

	data->p_inf = malloc(sizeof (t_p_inf) * data->num_of_phyl);//выделяем память под массив структур t_p_inf
	i = 0;
	while (i < data->num_of_phyl)
	{
		data->p_inf[i].data = data;
		data->p_inf[i].name = i;
		data->p_inf[i].left_fork = i;
		if (i == data->num_of_phyl - 1)
		{
			data->p_inf[i].right_fork = 0;
		}
		else
			data->p_inf[i].right_fork = i + 1;
		printf("name - %d, left_fork - %d, right_fork - %d\n", data->p_inf[i].name, data->p_inf[i].left_fork, data->p_inf[i].right_fork);
		i++;
	}
	return (0);
}

int ft_philosophers_init(t_data *data)
{
	//pthread_t *phylosophers;

	data->phylosophers = malloc(sizeof(pthread_t) * data->num_of_phyl);
	int i;

	i = 0;

	while (i < data->num_of_phyl)
	{
		pthread_create(&data->phylosophers[i], NULL, ft_simulation, &data->p_inf[i]);
		i++;
	}
	return (0);
}

int ft_phil_thr_join(t_data *data)
{
	int i2;
	i2 = 0;
	while (i2 < data->num_of_phyl)
	{
		pthread_join(data->phylosophers[i2], NULL);
		i2++;
	}

	return (0);
}

int main(int argc, char * argv[])
{
	t_data data; //структура со стартовыми параметрами в идеале надо инициализировать NULL и выделить память
	if (argc == 5)//тут добавть защиту ввоода
	{
		data.num_of_phyl = atoi(argv[1]); //заменить атои на свою реализацию и в нее добавить защиту
		data.time_to_die = atoi(argv[2]);
		data.time_to_eat = atoi(argv[3]);
		data.time_to_sleep = atoi(argv[4]);
		data.phylosophers = NULL;
	}
	ft_phyl_init_data(&data);//иницализируем данные имя философов и номера вилок
	ft_table_init(&data);//инициализируем массив мьютексов
	ft_philosophers_init(&data); //запускаем потоки
	ft_phil_thr_join(&data);
	//usleep(10000);
	return 0;
}