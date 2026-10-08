/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:30:06 by aelbouss          #+#    #+#             */
/*   Updated: 2025/02/27 16:00:03 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arrays(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*search_for_path(char **envp)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	path = "PATH=/";
	while (envp[i])
	{
		if (envp[i][0] == 'P')
		{
			j = 0;
			while (j <= 5)
			{
				if (envp[i][j] != path[j])
					break ;
				j++;
			}
			if (path[j] == '\0')
				return (envp[i]);
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	new_str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!new_str)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	return (new_str);
}

char	*extract_path(char **e_path, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (ft_strlen(cmd) == 0 || cmd[0] == '/' || cmd [0] == '.')
		return (NULL);
	i = 0;
	while (e_path[i])
	{
		tmp = ft_strjoin(e_path[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
