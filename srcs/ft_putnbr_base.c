/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:17:29 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/19 22:33:01 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

/*
** Print a number in a given base without calling printf as it calls malloc()
*/

void		ft_putnbr_base_fd(int n, unsigned int base, int fd)
{
	char	*charset;

	charset = "0123456789ABCDEF";
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < (int)base)
		ft_putchar_fd(charset[n], fd);
	if (n >= (int)base)
	{
		ft_putnbr_fd(n / base, fd);
		ft_putchar_fd(charset[n % base], fd);
	}
}
