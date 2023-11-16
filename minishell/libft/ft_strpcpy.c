/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:01:59 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/16 23:40:35 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// Copies substring of str up to ptr, returns new string, NULL if ptr not in str
char	*ft_strpcpy(char *str, char *ptr)
{
	char	*new_str;
	int		i;
	int		j;

	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[j] && &str[j] != ptr)
		j++;
	if (!str || &str[j] != ptr)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (j + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < j)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
