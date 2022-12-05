/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 03:57:05 by pharbst           #+#    #+#             */
/*   Updated: 2022/12/05 07:34:22 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_strchr(char *str, int ch)
{
	if (!str || !ch)
		return (NULL);
	while (*str != ((unsigned char)ch))
		if (*str++ == '\0')
			return (NULL);
	return (str);
}

long	philo_atoi(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (ft_strchr("+-0123456789", str[i]))
	{
		if (ft_strchr("+-", str[i]))
			return (write(2, "Error: \"+-\" is not allowed\n", 27), -1);
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > 2147483647)
		return (-1);
	return (nbr);
}
