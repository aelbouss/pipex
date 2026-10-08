/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:54:40 by aelbouss          #+#    #+#             */
/*   Updated: 2025/03/03 01:51:36 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//headers section
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>

//prototypes sectipn 
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char const *str);
char	*extract_path(char **e_path, char *cmd);
void	execute_parent_process(char **envp, char *file, int *pfd, char *pcmd);
void	execute_child_process(char **envp, char *file, int *pfd, char *pcmd);
char	*search_for_path(char **envp);
void	free_arrays(char **ptr);
void	_error(char *str);
void	case_error(char **arr1, char **arr2, char *msg);
void	arr_free(char **arr, char *msg);
void	handle_redirections(int wrend, int rdend);
void	execute_processes(char	**envp, char **av);
#endif 
