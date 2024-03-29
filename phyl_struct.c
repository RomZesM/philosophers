//
// Created by RomZes on 08.11.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define PH_AMOUNT 5 //дефайним количество философов, оно же количество вилок, нужно передвать через арг

typedef struct s_philosopher_info { //создаем структуру содержащую данные о философе
	const char *name; //имя философа, 1,2,3 и т.д
	unsigned left_vid;//??? тут непонятно, почему просто  unsigned, ne int?  для хранения номера вилки\мютекса
	unsigned right_vid;
} t_philosopher_info;

typedef struct s_table{ //стол на котором расополоагаются вилки (mutex)
	pthread_mutex_t forks[PH_AMOUNT]; //массив из мьютексов для инициализации
} t_table;

typedef struct s_philosopher_at_table { //общая структура для передачи все в функцию ??
	const t_philosopher_info *philosophers; //структрура с философами (имя, "руки'
	const t_table *table;
} t_philosopher_at_table;

//инициализация философов
void init_philosopher(t_philosopher_info *philosopher, const char *name, unsigned left_vid, unsigned right_vid) {
	philosopher->name = name;
	philosopher->left_vid = left_vid;
	philosopher->right_vid = right_vid;
}

void init_table(t_table *table) { //инициализация стола с мютексами для эмуляции
	size_t i;
	for (i = 0; i < PH_AMOUNT; i++) {
		pthread_mutex_init(&table->forks[i], NULL); //инициализация мьютекса и запись его в массив мьютексов
	}
}

void* eat (void * inf)
{
	t_philosopher_at_table * phil_table = (t_philosopher_at_table *)inf; //получаем данные о столе и философах
	const t_philosopher_info * phil = phil_table->philosophers;
	const t_table * table  = phil_table->table;

	printf("Philosofer %s - strart eating\n", phil->name);

	pthread_mutex_lock(&table->forks[phil->left_vid]);
	pthread_mutex_lock(&table->forks[phil->right_vid]);

	printf("%s is eating\n", phil->name);

	pthread_mutex_unlock(&table->forks[phil->left_vid]);
	pthread_mutex_unlock(&table->forks[phil->right_vid]);

	printf("%s finished dinner\n", phil->name);

}

int main()
{
	pthread_t threads[PH_AMOUNT]; //создаем массив для хранения н количества потоков
	t_philosopher_info philosofers[PH_AMOUNT]; //массив для хранения информации о философах, он же передается в ф. инициализации.
	t_table table;
	t_philosopher_at_table p_t[PH_AMOUNT]; //общая структура для хранения филосовово и стола, из тех что иницилизовали выше

	int i;

	init_table(&table); //инициализируем PH_AMOUNT мютексов на столе
	init_philosopher(&philosofers[0], "One", 0, 1); //иниц. философов каждому даем вилки
	init_philosopher(&philosofers[1], "Two", 1, 2);
	init_philosopher(&philosofers[2], "Three", 2, 3);
	init_philosopher(&philosofers[3], "Four", 3, 4);
	init_philosopher(&philosofers[4], "Five", 4, 0);


	i = 0;
	while (i < PH_AMOUNT)
	{
		p_t[i].philosophers = &philosofers[i];
		p_t[i].table = &table;
		i++;
	}
	for (i = 0; i < PH_AMOUNT; i++) {
		pthread_create(&threads[i], NULL, eat, &p_t[i]);
	}

	for (i = 0; i < PH_AMOUNT; i++) {
		pthread_join(threads[i], NULL);
	}
	wait(1);
}
