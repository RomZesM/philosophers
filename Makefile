NAME =	philo
CFLAGS =	-Wall -Wextra

all:
	gcc $(CFLAGS) -o $(NAME) -std=c99 -lpthread philo.c utils.c

p1:
	gcc $(CFLAGS) -o phil_exe -std=c99 -lpthread phyl_struct.c