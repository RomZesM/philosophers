//
// Created by Margo Clotilde on 12/5/21.
//

#include "philo.h"

int ft_min_fork(t_p_inf * inf)
{
	if (inf->left_fork < inf->right_fork)
		return(inf->left_fork);
	else
		return(inf->right_fork);
}

int ft_max_fork(t_p_inf * inf)
{
	if (inf->left_fork > inf->right_fork)
		return(inf->left_fork);
	else
		return(inf->right_fork);
}