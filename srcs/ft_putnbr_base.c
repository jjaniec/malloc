/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:17:29 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/14 13:57:47 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void ft_putnbr_base(int n, unsigned int base)
{
	char *charset = "0123456789ABCDEF";

	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n < (int)base)
		ft_putchar(charset[n]);
	if (n >= (int)base)
	{
		ft_putnbr(n / base);
		ft_putchar(charset[n % base]);
	}
}
