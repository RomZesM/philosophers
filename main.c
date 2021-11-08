#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

pthread_mutex_t vid1; //объявляем переменные для мютекса, придется сделать их глобальными
pthread_mutex_t vid2;


unsigned long    get_time_in_ms(void) //функция получения текущего времени in ms (dan)
{
	struct timeval  time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void * eat(void *nm)
{
	int i;
	i = 0;
	pthread_mutex_lock(&vid1);
	pthread_mutex_lock(&vid2);
//	while (i < 10)
//	{
		printf("Phylosopher - %d is eating\n", *(int *)nm);
		usleep(500);//ждем пока философ поест.
		i++;
//	}
	pthread_mutex_unlock(&vid1);
	pthread_mutex_unlock(&vid2);
//	printf("Stop eating\n");
	return(NULL);

}

int main()
{
	pthread_t	phyl1; //создаем сами потоки, вероятно нужно чтобы это была глобальная переменная
	pthread_t	phyl2;
	int nm1 = 1;
	int nm2 = 2;

	printf("Time: %ld\n", get_time_in_ms());
	pthread_mutex_init(&vid1, NULL); //инициализируем мьютексы для использования
	pthread_mutex_init(&vid2, NULL);

	pthread_create(&phyl1, NULL, eat, (void *)&nm1);
	pthread_create(&phyl2, NULL, eat, (void *)&nm2);
	//pthread_detach(phyl2);
	//pthread_detach(phyl1);
	pthread_mutex_init(&vid1, NULL);
	pthread_mutex_init(&vid2, NULL);

	pthread_join(phyl1, NULL); //дожидаемся завершения выполнения потока
	pthread_join(phyl2, NULL);
	//usleep(5000000);
	printf("Time 2: %ld\n", get_time_in_ms());
	write(1, "EXIT\n", 5);
	return 0;
}
