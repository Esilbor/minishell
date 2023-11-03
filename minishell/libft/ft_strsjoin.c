/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:59:30 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/03 16:04:52 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Calculate total length needed
// Start with 1 for the null terminator
// Allocate memory for the new string
// Set the first character to the null terminator

// Concatenate all strings into new_str
char	*ft_strsjoin(char **strs)
{
	size_t	total_len;
	char	*new_str;
	int		i;

	total_len = 1;
	i = -1;
	while (strs[++i])
		total_len += ft_strlen(strs[i]);
	new_str = (char *)malloc(total_len * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	i = -1;
	while (strs[++i])
		ft_strlcat(new_str, strs[i], total_len);
	return (new_str);
}
