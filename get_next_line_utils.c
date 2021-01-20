/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrey <andrey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:21:45 by andrey            #+#    #+#             */
/*   Updated: 2020/12/03 20:58:53 by andrey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char			*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!res)
		return (NULL);
	while (*s1)
	{
		*res = *s1;
		s1++;
		res++;
	}
	while (*s2)
	{
		*res = *s2;
		s2++;
		res++;
	}
	*res = '\0';
	return (res - (i + j));
}

char			*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	if (!(res = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
