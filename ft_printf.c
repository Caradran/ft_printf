/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:59:51 by esuits            #+#    #+#             */
/*   Updated: 2018/01/30 19:27:26 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putpstr(char *start, char *ptr)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = start;
	while (start++ != ptr)
		i++;
	start = tmp;
	write(1, tmp, i);
	return (i);
}

int		ft_read(const char *format, va_list *args)
{
	int		len;
	int		i;
	char	*ptr;
	char	*tmp;

	ptr = (char *)format;
	tmp = ptr;
	len = 0;
	while (*ptr != '\0')
		if (*ptr == '%')
		{
			len += ft_putpstr(tmp, ptr++);
			if ((i = ft_read_flag(args, &ptr)) == -1)
				return (-1);
			else
				len += i;
			if (*ptr)
				++ptr;
			tmp = ptr;
		}
		else
			ptr++;
	len += ft_putpstr(tmp, ptr);
	*ptr ? ++ptr : ptr;
	return (len);
}

int		ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	len = 0;
	if (!format)
		return (len);
	va_start(args, format);
	len = ft_read(format, &args);
	va_end(args);
	return (len);
}
