/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 03:04:53 by aelbouss          #+#    #+#             */
/*   Updated: 2025/03/06 01:00:52 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_process(t_infos *p, int idx, int np, char *cmd)
{
	char	*path;
	int		fd;
	char	**paths;
	char	**splitedcmd;

	splitedcmd = ft_split(cmd, 32);
	fd = open(p->file[1], O_RDONLY, 0644);
	if (fd < 0)
		_error("error due opening infile");
	handle_redirections_pipes(fd, p->pfd[idx][1], np, p);
	close(fd);
	path = search_for_path(p->envp);
	if (!path)
		case_error(splitedcmd, NULL, p->pfd, "failed to reach (PATH)\n");
	paths = ft_split(path, ':');
	if (!paths || !splitedcmd)
		case_error(splitedcmd, paths, p->pfd, "bad allocation\n");
	path = extract_path(paths, splitedcmd[0]);
	if (!path)
		case_error(splitedcmd, paths, p->pfd, "command not found\n");
	execve(path, splitedcmd, p->envp);
	fail_case(splitedcmd, paths, p->pfd, "permission denied\n");
}

void	last_process(t_infos *p, int idx, int np, char *cmd)
{
	char	*path;
	int		fd;
	char	**paths;
	char	**splitedcmd;

	splitedcmd = ft_split(cmd, 32);
	fd = open(p->file[p->ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		_error("error due opening outfile");
	handle_redirections_pipes(p->pfd[idx][0], fd, np, p);
	close(fd);
	path = search_for_path(p->envp);
	if (!path)
		case_error(splitedcmd, NULL, p->pfd, "failed to reach (PATH)\n");
	paths = ft_split(path, ':');
	if (!paths || !splitedcmd)
		case_error(splitedcmd, paths, p->pfd, "bad allocation\n");
	path = extract_path(paths, splitedcmd[0]);
	if (!path)
		case_error(splitedcmd, paths, p->pfd, "command not found\n");
	execve(path, splitedcmd, p->envp);
	fail_case(splitedcmd, paths, p->pfd, "permission denied\n");
}

void	midle_process(t_infos *p, int idx, int np, char *cmd)
{
	char	**paths;
	char	**splitedcmd;
	char	*path;

	splitedcmd = ft_split(cmd, 32);
	handle_redirections_pipes(p->pfd[idx -1][0], p->pfd[idx][1], np, p);
	path = search_for_path(p->envp);
	if (!path)
		case_error(splitedcmd, NULL, p->pfd, "failed to reach (PATH)\n");
	paths = ft_split(path, ':');
	if (!paths || !splitedcmd)
		case_error(splitedcmd, paths, p->pfd, "bad allocation\n");
	path = extract_path(paths, splitedcmd[0]);
	if (!path)
		case_error(splitedcmd, paths, p->pfd, "command not found\n");
	execve(path, splitedcmd, p->envp);
	fail_case(splitedcmd, paths, p->pfd, "permission denied\n");
}

void	core_proess(t_infos *p, char **argsv)
{
	int	pid;
	int	i;

	i = 0;
	while (i < p->ac - 3)
	{
		pid = fork();
		if (pid == -1)
			_error("(FORK)");
		if (pid == 0)
		{
			if (i == 0)
				first_process(p, i, p->ac - 4, argsv[2]);
			else if (i == p->ac - 4)
				last_process(p, i - 1, p->ac - 4, argsv[i + 2]);
			else
				midle_process(p, i, p->ac - 4, argsv[i + 2]);
		}
		i++;
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int			**pipes;
	t_infos		instance;

	if (ac < 5)
		putstr_fd("invalid number of arguments\n", 2);
	pipes = open_pipes(ac - 4, ac - 3);
	if (!pipes)
		putstr_fd("bad allocation\n", 2);
	instance.envp = envp;
	instance.pfd = pipes;
	instance.file = av;
	instance.ac = ac;
	core_proess(&instance, av);
	close_pipes(pipes, ac - 4);
	wait_childs(ac - 3);
	clean_2d_array(pipes, ac - 3);
	return (0);
}
