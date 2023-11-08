/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:35:44 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/08 12:15:52 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copies str until c is encountered and return the new string
char	*ft_strccpy(char *str, char c)
{
	char	*new_str;
	int		i;

	new_str = NULL;
	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str && str[i] && str[i] != c)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

