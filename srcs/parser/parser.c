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

/*
int	find_level(char *prompt, int level)
{
	int			i;
	int			parenthese_level;
	int			len;
	static char	*strings[] = {
		"&&", "||", "|", "<", "<<", ">", ">>" };

	len = ft_strlen(strings[level]);
	i = -1;
	parenthese_level = 0;
	while (prompt[++i])
	{
		parenthese_level += (prompt[i] == '(') - (prompt[i] == ')');
		//TODO PARENTHESE ERROR CHECK
		if (parenthese_level != 0
			|| ft_strncmp(&prompt[i], strings[level], len))
			continue ;
		prompt[i] = 0;
		prompt[i + (len > 1)] = 0;
		return (i + len);
	}
	//TODO PARENTHESE ERROR CHECK
	return (-1);
}

char	*parenthese_trim(char *prompt)
{
	int	i;

	i = ft_strlen(prompt);
	prompt[0] = 0;
	if (prompt[i - 1] != ')')
		; //TODO ERROR
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

t_token	*parser(char *prompt)
{
	t_token	*res;
	int		i;
	int		index;

	if (!prompt || !*prompt)
		return (NULL);
	res = calloc(1, sizeof(t_token));
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
	res->left = parser(prompt);
	if (res->left == NULL)
		; //TODO ERROR Tu as oublié de mettre un point virgule
	res->right = parser(&prompt[index]);
	if (res->right == NULL)
		; //TODO ERROR
	return (res);
}

void	print_tree(t_token *tree)
{
	if (!tree)
		return ;
	print_tree(tree->left);
	if (tree->type == COMMAND)
		printf("%s ", tree->argv);
	if (tree->type == AND)
		printf("AND ");
	if (tree->type == OR)
		printf("OR ");
	if (tree->type == PIPE)
		printf("PIPE ");
	if (tree->type == INPUT_REDIRECTION)
		printf("INPUT_REDIRECTION ");
	if (tree->type == HERDOC_REDIRECTION)
		printf("HERDOC_REDIRECTION ");
	if (tree->type == OUTPUT_REDIRECTION)	
		printf("OUTPUT_REDIRECTION ");
	if (tree->type == OUTPUT_ADD_REDIRECTION)
		printf("OUTPUT_ADD_REDIRECTION ");
	printf("\n");
	print_tree(tree->right);
}

void	print_intree(t_token *tree)
{
	if (!tree)
		return ;
	if (tree->type == COMMAND)
		printf("%s ", tree->argv);
	if (tree->type == AND)
		printf("AND ");
	if (tree->type == OR)
		printf("OR ");
	if (tree->type == PIPE)
		printf("PIPE ");
	if (tree->type == INPUT_REDIRECTION)
		printf("INPUT_REDIRECTION ");
	if (tree->type == HERDOC_REDIRECTION)
		printf("HERDOC_REDIRECTION ");
	if (tree->type == OUTPUT_REDIRECTION)	
		printf("OUTPUT_REDIRECTION ");
	if (tree->type == OUTPUT_ADD_REDIRECTION)
		printf("OUTPUT_ADD_REDIRECTION ");
	printf("\n");
	print_tree(tree->left);
	print_tree(tree->right);
}

void	print_posttree(t_token *tree)
{
	if (!tree)
		return ;
	print_tree(tree->left);
	print_tree(tree->right);
	if (tree->type == COMMAND)
		printf("%s ", tree->argv);
	if (tree->type == AND)
		printf("AND ");
	if (tree->type == OR)
		printf("OR ");
	if (tree->type == PIPE)
		printf("PIPE ");
	if (tree->type == INPUT_REDIRECTION)
		printf("INPUT_REDIRECTION ");
	if (tree->type == HERDOC_REDIRECTION)
		printf("HERDOC_REDIRECTION ");
	if (tree->type == OUTPUT_REDIRECTION)	
		printf("OUTPUT_REDIRECTION ");
	if (tree->type == OUTPUT_ADD_REDIRECTION)
		printf("OUTPUT_ADD_REDIRECTION ");
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_token	*token;

	token = parser(argv[1]);
	print_tree(token);
	printf("next\n\n");
	print_intree(token);
	printf("next\n\n");
	print_posttree(token);
	printf("next\n\n");
	
	return (0);
}
*/