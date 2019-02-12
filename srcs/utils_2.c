/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 06:38:57 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 09:25:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"

int		split_n_count(char *str, char c, char ***split)
{
	int		count;

	count = 0;
	if (str != NULL)
	{
		*split = ft_strsplit(str, c);
		if (*split == NULL)
			return (0);
		while ((*split)[count] != NULL)
			count++;
	}
	return (count);
}

int		is_number(char *str)
{
	int	idx;

	idx = 0;
	if (str != NULL)
	{
		if (str[idx] == '+' || str[idx] == '-')
			idx += 1;
		if (str[idx] == '\0' || ft_isdigit(str[idx]) == 0)
			return (0);
		while (str[idx] != '\0')
		{
			if (ft_isdigit(str[idx]) == 0)
				return (0);
			idx += 1;
		}
	}
	return (str != NULL);
}

int		is_float(char *str)
{
	int	idx;

	idx = 0;
	if (str != NULL)
	{
		if (str[idx] == '+' || str[idx] == '-')
			idx += 1;
		if (str[idx] == '\0' || ft_isdigit(str[idx]) == 0)
			return (0);
		while (str[idx] != '\0' && str[idx] != '.')
		{
			if (ft_isdigit(str[idx]) == 0)
				return (0);
			idx += 1;
		}
		if (str[idx++] == '\0')
			return (0);
		while (str[idx] != '\0')
		{
			if (ft_isdigit(str[idx]) == 0)
				return (0);
			idx += 1;
		}
	}
	return (str != NULL);
}

double		ft_atof(char *str)
{
	int		idx;
	int		jdx;
	double	res;

	res = 0.;
	idx = 0;
	while (str[idx] != '.' && str[idx] != '\0')
		idx++;
	if (str[idx] == '.')
		idx += 1;
	jdx = 1;
	while (str[idx] != '\0')
	{
		res += (str[idx] - '0') / ft_pow(10, jdx);
		idx += 1;
	}
	res += (double)ft_atoi(str);
	return (res);
}

void		delsplit(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i += 1;
	}
	free(split);
}

int			is_v3(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		if (is_float(split[i]) == 0 && is_number(split[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
