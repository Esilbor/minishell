/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:47:04 by esilbor           #+#    #+#             */
/*   Updated: 2023/12/30 18:05:48 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// .limiter_index_k
char	*name_heredoc(char *limiter, int index, int k)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = ft_itoa(index);
	tmp = ft_strdup(limiter);
	if (!tmp && limiter)
		return (free (tmp3), NULL);
	tmp2 = ft_strjoin(tmp, "_");
	free (tmp);
	tmp = ft_strjoin(tmp2, tmp3);
	free (tmp2);
	free (tmp3);
	tmp2 = ft_strjoin(tmp, "_");
	free (tmp);
	tmp3 = ft_itoa(k);
	tmp = ft_strjoin(tmp2, tmp3);
	free (tmp2);
	free (tmp3);
	return (tmp);
}

// Helper function to handle limiter nodes
static int	handle_limiter_node(t_lexer *lst, t_env *env, int index, int *k)
{
	char	*limiter;
	char	*tmp;

	limiter = ft_strdup(lst->word);
	if (!limiter)
		return (-1);
	tmp = name_heredoc(lst->word, index, (*k)++);
	if (!tmp)
	{
		free(limiter);
		return (-1);
	}
	free(lst->word);
	lst->word = ft_strjoin(".", tmp);
	free(tmp);
	create_heredoc(env, lst, limiter);
	free(limiter);
	return (0);
}

int	modify_limiter_nodes(t_env *env, t_lexer *lst, int index)
{
	int	k;

	k = 1;
	while (lst)
	{
		if (lst->type == LIMITER)
			if (handle_limiter_node(lst, env, index, &k) < 0)
				return (-1);
		lst = lst->next;
	}
	return (0);
}
