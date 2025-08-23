/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuopea <ssuopea@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:21:03 by ssuopea           #+#    #+#             */
/*   Updated: 2025/08/23 11:57:08 by ssuopea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	i(int x, int y)
{
	return(y * WIDTH + x);
}

int	center(void)
{
	return(i(WIDTH / 2, HEIGHT / 2));
}

int	x(int i)
{
	return (i % WIDTH);
}

int y(int i)
{
	return (i / WIDTH);
}
