/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:05:07 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/09 16:05:32 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	copy_realloc_del(char **res, char **envp, int index)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (envp[i])
	{
		if (i == index)
		{
			i++;
			continue;
		}
		j = 0;
		while (envp[i][j])
		{
			res[k][j] = envp[i][j];
			j++;
		}
		res[k][j] = '\0';
		k++;
		i++;
	}
}

char	**realloc_envp_del(int p, char *name, char **envp)
{
	int		i;
	int		j;
	char	**res;
	int		index;

	index = ft_getenv_index(name, envp);
	i = 0;
	j = 0;
	res = (char **)malloc(sizeof(char *) * (p + 1));
	while (i < p)
	{
		if (index == j)
			j++;
		res[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[j]) + 1));
		j++;
		i++;
	}
	res[i] = NULL;
	copy_realloc_del(res, envp, index);
	return (res);
}

int		ft_unsetenv(char **parse, char **envp)
{
	char	**new_env;
	int		p;

	new_env = NULL;
	p = count_pointers(parse);
	if (p == 2 && parse[1] != NULL)
	{
		if (ft_getenv(parse[1], envp) != NULL)
		{
			p = count_pointers(envp) - 1;
			new_env = realloc_envp_del(p, parse[1], envp);
			free_copy_envp(&envp);
			g_my_env = NULL;
			g_my_env = new_env;
			if (ft_strcmp("PATH", parse[1]) == 0)
			{
				free_hash_table(&g_table);
				g_table = create_table();
			}
			return (1);
		}
	}
	return (1);
}
