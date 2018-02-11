/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 04:21:47 by esuits            #+#    #+#             */
/*   Updated: 2018/01/30 19:26:10 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_read_format_lc(va_list *args, char **ptr, t_form *form)
{
	int		l;
	int		len;
	void	*arg;

	if (**ptr != 'C' && !(**ptr == 'c' && form->mod[2]))
		return (ft_read_format(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	if ((len = ft_lenuchar((unsigned int)arg)) == -1)
		return (-1);
	l = (len > form->pre) ? len : form->pre;
	if (!form->flags[2])
		ft_putpad((form->flags[1] && form->pre == -1) ? '0' : ' ', form->w - l);
	while (form->pre-- > len)
		write(1, "0", 1);
	if (ft_putuchar((int)arg) == -1)
		return (-1);
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (long)form->w)
		l = form->w + 0 * (long)args++;
	return (l);
}

int		ft_read_format_c(va_list *args, char **ptr, t_form *form, int i)
{
	int		l;
	int		len;
	void	*arg;

	if ((**ptr != 'c' || (**ptr == 'c' && form->mod[2])) && !i)
		return (ft_read_format_lc(args, ptr, form));
	if (!i && !(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	else if (i)
		arg = (void*)(long)**ptr;
	len = 1;
	l = len;
	if (!form->flags[2])
		ft_putpad((form->flags[1]) ? '0' : ' ', form->w - l);
	ft_putchar((char)arg);
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (long)form->w)
		l = form->w + 0 * (long)args++;
	return (l);
}

int		ft_read_format_xx(va_list *args, char **ptr, t_form *form)
{
	void	*arg;

	if (**ptr != 'x' && **ptr != 'X' && **ptr != 'p')
		return (ft_read_format_c(args, ptr, form, 0));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	args++;
	(**ptr == 'p') ? form->flags[0] = 1 : form->flags[0];
	if (form->mod[0])
		return (ft_mod_xx((unsigned char)arg, form, ptr));
	if (form->mod[1])
		return (ft_mod_xx((unsigned short)arg, form, ptr));
	if (form->mod[2])
		return (ft_mod_xx((unsigned long)arg, form, ptr));
	if (form->mod[3])
		return (ft_mod_xx((unsigned long long)arg, form, ptr));
	if (form->mod[4])
		return (ft_mod_xx((uintmax_t)arg, form, ptr));
	if (form->mod[5])
		return (ft_mod_xx((size_t)arg, form, ptr));
	return (ft_mod_xx((unsigned int)arg, form, ptr));
}

int		ft_read_format_uu(va_list *args, char **ptr, t_form *form)
{
	void	*arg;

	if (**ptr != 'u' && **ptr != 'U')
		return (ft_read_format_xx(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	if ((++args || 1) && **ptr == 'U')
		return (ft_mod_uu((unsigned long)arg, form));
	if (form->mod[0])
		return (ft_mod_uu((unsigned char)arg, form));
	if (form->mod[1])
		return (ft_mod_uu((unsigned short)arg, form));
	if (form->mod[2])
		return (ft_mod_uu((unsigned long)arg, form));
	if (form->mod[3])
		return (ft_mod_uu((unsigned long long)arg, form));
	if (form->mod[4])
		return (ft_mod_uu((uintmax_t)arg, form));
	if (form->mod[5])
		return (ft_mod_uu((size_t)arg, form));
	return (ft_mod_uu((unsigned int)arg, form));
}
