/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:09:53 by albaud            #+#    #+#             */
/*   Updated: 2023/12/08 00:35:15 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


char	*parenthese_trim(char *prompt)
{
	int	i;

	i = ft_strlen(prompt);
	prompt[0] = 0;
	if (prompt[i - 1] != ')')
		return (NULL);
	prompt[i - 1] = 0;
	return (&prompt[1]);
}

char	*trim_space(char *prompt)
{
	int	i;

	i = ft_strlen(prompt);
	while (--i >= 0 && prompt[i] == ' ') //TODO isspace
		;
	prompt[i + 1] = 0;
	i = -1;
	while (prompt[++i] == ' ') //TODO isspace
		;
	if (i > 0)
		prompt[i - 1] = 0;
	return (&prompt[i]);
}

/*comment ca marche si on a un seul tokken : c'est gerer dans le parser()
 * */
int	find_level(char *prompt, int level)
{
	int			i;
	int			parenthese_level;
	int			len;
	static char	*strings[] = {
			"&&", "||", "|", "<<", "<", ">>", ">" };

	len = ft_strlen(strings[level]);
	i = -1;
	parenthese_level = 0;
	while (prompt[++i])
	{
		parenthese_level += (prompt[i] == '(') - (prompt[i] == ')');//ignorer si elle est dans une double quote
		//TODO PARENTHESE ERROR CHECK
		if (parenthese_level != 0
			|| ft_strncmp(&prompt[i], strings[level], len))//ignorer si elle est dans une double quote
			continue ;
		prompt[i] = 0;
		prompt[i + (len > 1)] = 0;
		return (i + len);
	}
	//TODO PARENTHESE ERROR CHECK
	return (-1);
}

/*TODO:
 * if  REDIR then set the fd
 * if PIPE do the pipe[2] later
 * */
t_token	*parser(char *prompt)
{
	t_token	*res;
	int		i;
	int		index;

	if (!prompt || !*prompt)
		return (NULL);
	res = ft_calloc(1, sizeof(t_token));
	if (!res)
		return (NULL);
	prompt = trim_space(prompt);
	i = -1;
	index = -1;
	while (++i < 7 && index == -1)
		index = find_level(prompt, i);
	if (index == -1)
	{
		if (prompt[0] == '(')
			return (parser(parenthese_trim(prompt)));
		res->type = COMMAND;
		res->argv = strdup(prompt);
		return (res);
	}
	res->type = i - 1;
	if (prompt)
	{
		res->left = parser(prompt);
		if (res->left == NULL)
			; //TODO ERROR
	}
	if (prompt[index])
	{
		res->right = parser(&prompt[index]);
		if (res->right == NULL)
			; //TODO ERROR
	}
	return (res);
}
