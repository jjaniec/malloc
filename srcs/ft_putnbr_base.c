/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:17:29 by jjaniec           #+#    #+#             */
/*   Updated: 2019/10/17 16:07:06 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		ft_putnbr_base(int n, unsigned int base)
{
	char	*charset;

	charset = "0123456789ABCDEF";
	if (n < 0)
	{
		ft_putchar_fd('-', 2);
		n = -n;
	}
	if (n < (int)base)
		ft_putchar_fd(charset[n], 2);
	if (n >= (int)base)
	{
		ft_putnbr_fd(n / base, 2);
		ft_putchar_fd(charset[n % base], 2);
	}
}
