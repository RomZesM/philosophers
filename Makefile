NAME =	philosofers
CFLAGS =	-Wall -Werror -Wextra

all:
	gcc $(CFLAGS) -o $(NAME) -std=c99 -lpthread main.c

p1:
	gcc $(CFLAGS) -o phil_exe -std=c99 -lpthread phyl_struct.c