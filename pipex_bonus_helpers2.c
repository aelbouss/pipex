/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_helpers2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 03:04:45 by aelbouss          #+#    #+#             */
/*   Updated: 2025/03/06 00:47:45 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	fail_case(char **arr1, char **arr2, int	**arr3, char *msg)
{
	int	i;

	i = 0 ;
	while (arr1[i])
	{
		free(arr1[i]);
		i++;
	}
	free(arr1);
	i = 0 ;
	while (arr2[i])
	{
		free(arr2[i]);
		i++;
	}
	free(arr2);
	i = 0;
	while (arr3[i])
	{
		free(arr3[i]);
		i++;
	}
	free(arr3);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	close_pipes(int **arr, int np)
{
	int	i;

	i = 0;
	while (i < np)
	{
		close(arr[i][0]);
		close(arr[i][1]);
		i++;
	}
}

void	wait_childs(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
}
