/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:30:36 by aelbouss          #+#    #+#             */
/*   Updated: 2025/03/03 02:34:55 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	_error(char *str)
{
	perror(str);
	exit(1);
}

void	case_error(char **arr1, char **arr2, char *msg)
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
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	arr_free(char **arr, char *msg)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	handle_redirections(int rdend, int wrend)
{
	if (dup2(rdend, STDIN_FILENO) == -1)
		_error("error due duplication");
	if (dup2(wrend, STDOUT_FILENO) == -1)
		_error("error due duplication");
}

void	execute_processes(char	**envp, char **av)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		_error("(PIPE)");
	pid = fork();
	if (pid == -1)
		_error("(FORK)");
	if (pid == 0)
		execute_child_process(envp, av[1], fd, av[2]);
	else
	{
		pid = fork();
		if (pid == -1)
			_error("(FORK)");
		if (pid == 0)
			execute_parent_process(envp, av[4], fd, av[3]);
		else
			wait(NULL);
	}
}
