cmake_minimum_required(VERSION 3.20)
project(philosofers C)

set(CMAKE_C_STANDARD 99)

add_executable(philosofers main.c phyl_struct.c raborka.c philo.c philo.h utils.c)
