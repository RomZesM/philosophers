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
 * timestamp N message
 *
 * timestamp N has taken a fork
 * timestamp N is eating
 * timestamp N is sleeping
 * timestamp N is waiting
 * timestamp N died
 *
 *#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
 *
 */

#include "philo.h"

int ft_print_message(t_p_inf * inf, unsigned long int time, char * msg)
{
	//чтобы не выводилось сообщение если кто то из философо умер ( нужна глобальная переменная), надо добавить проверку
	printf("%ld %d %s", time, inf->name, msg);
	//int time; // сюда надо посчитать текущее время, - время начала запуска симуляции
	return (0);
};

int ft_taking_forks(t_p_inf * inf)
{
	//берем минимальную вилку
	pthread_mutex_lock(&inf->data->forks[ft_min_fork(inf)]);
	pthread_mutex_lock(&inf->data->forks[ft_max_fork(inf)]);

	return 0;
}
int ft_eating(t_p_inf * inf)
{
	unsigned long time;
	time = ft_get_time_in_ms() - inf->data->start_time;
	ft_print_message(inf, time, "\033[32m is eating\033[0m\n" );
	//printf("%ld Philosopher %s: %d, lf-%d, rf-%d\n",  inf->data->start_time, "\033[32m is eating\033[0m\n",inf->name, inf->left_fork, inf->right_fork);
	ft_mod_usleep(inf->data->time_to_eat); //ждем время чтобы поесть
	inf->last_eat = ft_get_time_in_ms();//время, когда закончил есть, для проверки не умер ли он от голода
	//printf("Last - eating - %ld\n", inf->last_eat);
	return 0;
}

int ft_thinking(t_p_inf * inf)
{

	unsigned long time;
	time = ft_get_time_in_ms() - inf->data->start_time;
	ft_print_message(inf, time, "\033[35m is thinking\033[0m\n" );
	ft_mod_usleep(inf->data->time_to_sleep); //ждем время чтобы поесть

	return 0;
}

int ft_waiting(t_p_inf * inf)
{
	unsigned long time;
	time = ft_get_time_in_ms() - inf->data->start_time;
	ft_print_message(inf, time, "\033[34m is waiting\033[0m\n" );
	ft_mod_usleep(inf->data->time_to_sleep); //ждем время чтобы поесть

	return 0;
}

void * ft_d_check(void * arg)//добавить захват мютекса для проверки, чтобы в это время филосов не ел
{
	t_data * data;
	int i;
	int stop;
	data = (t_data *)arg;//передаем потоку общую структуру данных
	stop = 0;
	while (stop == 0)//нужен цикл который постоянно проверяет не умер ли кто то.
	{
		i = 0;
		while(i < data->num_of_phyl)
		{
			if(data->p_inf[i].dead_flag != 1)//если философ живой
			{
				printf("%ld %ld %ld\n", ft_get_time_in_ms(), data->p_inf[i].last_eat, data->time_to_die);
				if(data->p_inf[i].last_eat == 0 || ft_get_time_in_ms() - data->p_inf[i].last_eat <= data->time_to_die)
					printf("%d is alive, stop - %d\n", data->p_inf[i].name, stop);
				else
					printf("SOMEONE IS DEAD!!!\n");
					stop = 1;
					//exit(1);
			}
			i++;
		}
	}

	return (NULL);
}

void * ft_simulation (void * arg)
{
	int i = 0;//!удалить потом

	t_p_inf * inf;
	inf = (t_p_inf *)arg;

	while (i < 5)
	{
		ft_taking_forks(inf); //берем вилки (блокируем мютексы)

		ft_eating(inf); //отдельная функция еды.
		ft_thinking(inf);//думает после еды, пока заглушка без проверок
		ft_waiting(inf);

		pthread_mutex_unlock(&inf->data->forks[ft_max_fork(inf)]);
		pthread_mutex_unlock(&inf->data->forks[ft_min_fork(inf)]);
		i++;
	}

	return (NULL);
}

unsigned long    ft_get_time_in_ms(void) //функция получения текущего времени in ms (dan)
{
	struct timeval  cur_time; //структура куда gettimeofday записывает данные о времени

	gettimeofday(&cur_time, NULL); //0-удачно, 1 ошибка

	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000); //секунды на 1000 = миллисек., микросекунды наоборот увеличиваем.
}

void ft_mod_usleep(int sleep_time)//модифицированная функция ожидания вместо usleep, чтобы не прерывылась случайным сигналом
{								//получаем время в миллисекундах, сколько надо подождать.
	unsigned long int i;

	i = ft_get_time_in_ms();
	while (ft_get_time_in_ms() < i + sleep_time)
		{
			usleep(50); //ждем по 50 микросекунд
		}
	//return (0);
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
		data->p_inf[i].dead_flag = 0;
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

	pthread_t death_check; //поток  для проверки смерти философа
	int i;
	data->phylosophers = malloc(sizeof(pthread_t) * data->num_of_phyl);
	if(!data->phylosophers)
		exit(1);

	pthread_create(&death_check, NULL, ft_d_check, data); //запуск потока для проверки философов на смерть
	i = 0;

	while (i < data->num_of_phyl)
	{
		//запуск потоков, вместо функции пока что заглушка
		pthread_create(&data->phylosophers[i], NULL, ft_simulation, &data->p_inf[i]);
		i++;
	}
	pthread_join(death_check, NULL);
	return (0);
}

int ft_phil_thr_join(t_data *data) //звершение выполения потоков
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
void ft_start_time(t_data *data)//запоминаем время начала симуляции
{
	data->start_time = ft_get_time_in_ms();
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
	ft_start_time(&data);//время начала симуляции
	ft_philosophers_init(&data); //запускаем потоки
	ft_phil_thr_join(&data);//звершаем потоки
	//usleep(10000);
	return 0;
}