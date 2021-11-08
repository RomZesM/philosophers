//
// Created by RomZes on 08.11.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define PH_AMOUNT 5 //дефайним количество философов, оно же количество вилок, нужно передвать через арг

typedef struct s_philosopher_atr { //создаем структуру содержащую данные о философе
	const char *name;
	unsigned left_vid;
	unsigned right_vid;
} t_philosopher_atr;

typedef struct s_table{ //стол на которое расополоагаются вилки (mutex)
	pthread_mutex_t forks[PH_AMOUNT]; //массив из мьютексов
} t_table;

typedef struct s_philosopher_at_table { //общая структура для передачи все в функцию ??
	const t_philosopher_atr *philosopher;
	const t_table *table;
} s_philosopher_at_table;

//инициализация философов
void init_philosopher(t_philosopher_atr *philosopher, const char *name, unsigned left_vid, unsigned right_vid) {
	philosopher->name = name;
	philosopher->left_vid = left_fork;
	philosopher->right_vid = right_fork;
}

void init_table(t_table *table) {
	size_t i;
	for (i = 0; i < PHT_SIZE; i++) {
		pthread_mutex_init(&table->forks[i], NULL); //инициализация мьютекса и запист его в архив
	}
}