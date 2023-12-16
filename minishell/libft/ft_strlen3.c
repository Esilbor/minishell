/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaquedev <zaquedev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:34:43 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/16 17:20:05 by zaquedev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strlen3(const char *s)
{
	ssize_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}



// size_t	ft_strlen3(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s && s[i])
// 		i++;
// 	return (i);
// }
