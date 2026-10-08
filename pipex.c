/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:30:04 by aelbouss          #+#    #+#             */
/*   Updated: 2025/03/03 23:31:13 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_parent_process(char **envp, char *file, int *pfd, char *pcmd)
{
	int		fd;
	char	*path;
	char	**paths;
	char	**cmdargs;

	close(pfd[1]);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		_error("error occcured while opening the output file");
	handle_redirections(pfd[0], fd);
	cmdargs = ft_split(pcmd, 32);
	path = search_for_path(envp);
	if (!path)
		arr_free(cmdargs, "failed to reach (PATH)\n");
	paths = ft_split(path, ':');
	if (!paths || !cmdargs)
		case_error(cmdargs, paths, "bad allocation 1\n");
	path = extract_path(paths, cmdargs[0]);
	if (!path)
		case_error(cmdargs, paths, "command not found\n");
	execve(path, cmdargs, envp);
	case_error(cmdargs, paths, "permission denied\n");
}

void	execute_child_process(char **envp, char *file, int *pfd, char *pcmd)
{
	int		fd;
	char	*path;
	char	**paths;
	char	**cmdargs;

	close(pfd[0]);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		_error("error occcured while opening the input file");
	handle_redirections(fd, pfd[1]);
	cmdargs = ft_split(pcmd, 32);
	path = search_for_path(envp);
	if (!path)
		arr_free(cmdargs, "failed to reach (PATH)\n");
	paths = ft_split(path, ':');
	if (!paths || !cmdargs)
		case_error(cmdargs, paths, "bad allocation 2\n");
	path = extract_path(paths, cmdargs[0]);
	if (!path)
		case_error(cmdargs, paths, "command not found\n");
	execve(path, cmdargs, envp);
	case_error(cmdargs, paths, "permission denied\n");
}

int	main(int ac, char *av[], char *envp[])
{
	if (ac == 5)
	{
		execute_processes(envp, av);
	}
	else
	{
		write(2, "invalid arguments\n", 18);
		exit(1);
	}
}
