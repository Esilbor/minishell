/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 03:07:02 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/04 03:07:25 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// check if str is numerical (allow one - or + sign before)
bool	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if ((str[0] == '-' || str[0] == '+') && str[1] && ft_isdigit(str[1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}