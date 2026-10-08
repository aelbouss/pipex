/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_helpers3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 03:04:48 by aelbouss          #+#    #+#             */
/*   Updated: 2025/03/05 23:53:13 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**open_pipes(int np, int ncmds)
{
	int	i;
	int	**arr;

	arr = (int **)malloc(ncmds * sizeof(int *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < np)
	{
		arr[i] = (int *)malloc(2 * sizeof(int));
		if (! arr[i])
			_error("error");
		i++;
	}
	arr[i] = NULL;
	i = 0;
	while (arr[i])
	{
		if (pipe(arr[i]) < 0)
			_error("pipe creation fail");
		i++;
	}
	return (arr);
}

void	clean_2d_array(int **arr, int na)
{
	int	i;

	i = 0;
	while (i < na)
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

void	free_aop(int **aop)
{
	int	i;

	i = 0;
	while (aop[i])
	{
		free(aop[i]);
		i++;
	}
	if (aop)
		free(aop);
}

void	case_error(char **arr1, char **arr2, int **arr3, char *msg)
{
	int	i;

	i = 0;
	if (arr1)
	{
		while (arr1[i])
		{
			free(arr1[i]);
			i++;
		}
		free(arr1);
	}
	i = 0;
	if (arr2)
	{
		while (arr2[i])
		{
			free(arr2[i]);
			i++;
		}
		free(arr2);
	}
	free_aop(arr3);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(1);
}

void	handle_redirections_pipes(int rd_end, int wr_end, int np, t_infos *p)
{
	if (dup2(rd_end, STDIN_FILENO) == -1)
		_error("error due duplicating fds");
	if (dup2(wr_end, STDOUT_FILENO) == -1)
		_error("error due duplicating fds");
	close_pipes(p->pfd, np);
}
