/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 03:04:59 by aelbouss          #+#    #+#             */
/*   Updated: 2025/03/03 17:23:14 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct pipex_bonus
{
	char	**envp;
	int		**pfd;
	char	**file;
	int		ac;
}	t_infos;

//prototypes sectipn 
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char const *str);
char	*extract_path(char **e_path, char *cmd);
void	first_process(t_infos *p, int idx, int np, char *cmd);
void	last_process(t_infos *p, int idx, int np, char *cmd);
void	midle_process(t_infos *all, int idx, int np, char *cmd);
void	core_proess(t_infos *p, char **argsv);
char	*search_for_path(char **envp);
void	putstr_fd(char *str, int fd);
void	_error(char *str);
int		**open_pipes(int np, int ncmds);
void	wait_childs(int n);
void	clean_2d_array(int **arr, int na);
void	close_pipes(int **arr, int np);
void	fail_case(char **arr1, char **arr2, int **arr3, char *msg);
void	case_error(char **arr1, char **ar2, int **arr3, char *msg);
void	handle_redirections_pipes(int input, int output, int np, t_infos *p);
int		check_valid_cmd(char *cmd);
#endif
