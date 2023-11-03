/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:54:53 by bbresil           #+#    #+#             */
/*   Updated: 2022/11/30 11:15:59 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_isset(s1[i], set) && s1[i])
		i++;
	while (ft_isset(s1[len - 1], set) && s1[i])
		len--;
	str = malloc(sizeof(*str) * (ft_strlen(s1) - i -(ft_strlen(s1) - len) + 1));
	if (!str)
		return (NULL);
	while (s1[i] && i < len)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str [j] = '\0';
	return (str);
}
