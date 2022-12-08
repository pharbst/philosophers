/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:44:00 by pharbst           #+#    #+#             */
/*   Updated: 2022/05/17 20:44:00 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	register void	*calloc;

	if (nelem >= SIZE_MAX || elsize >= SIZE_MAX)
		return (NULL);
	if (nelem == 0 || elsize == 0)
	{
		nelem = 1;
		elsize = 1;
	}
	calloc = malloc(nelem * elsize);
	if (!calloc)
		return (NULL);
	ft_bzero(calloc, nelem * elsize);
	return (calloc);
}
