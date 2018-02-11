/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_form.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 12:55:42 by esuits            #+#    #+#             */
/*   Updated: 2018/01/30 19:34:19 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** flags : "#0-+ "
** width : unsigned int
** precision : .unsigned int
** modifier : "hh, h, l, ll, j, z"
** format : "sSpdDioOuUxXcC"
*/

int		ft_read_format_oo(va_list *args, char **ptr, t_form *form)
{
	void	*arg;

	if (**ptr != 'o' && **ptr != 'O')
		return (ft_read_format_uu(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	if ((++args || 1) && **ptr == 'O')
		return (ft_mod_oo((unsigned long)arg, form));
	if (form->mod[0])
		return (ft_mod_oo((unsigned char)arg, form));
	if (form->mod[1])
		return (ft_mod_oo((unsigned short)arg, form));
	if (form->mod[2])
		return (ft_mod_oo((unsigned long)arg, form));
	if (form->mod[3])
		return (ft_mod_oo((unsigned long long)arg, form));
	if (form->mod[4])
		return (ft_mod_oo((uintmax_t)arg, form));
	if (form->mod[5])
		return (ft_mod_oo((size_t)arg, form));
	return (ft_mod_oo((unsigned int)arg, form));
}

int		ft_read_format_d(va_list *args, char **ptr, t_form *form)
{
	void	*arg;

	if (**ptr != 'D')
		return (ft_read_format_oo(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	return (ft_mod_id((long)arg, form));
}

int		ft_read_format_id(va_list *args, char **ptr, t_form *form)
{
	void	*arg;

	if (**ptr != 'd' && **ptr != 'i')
		return (ft_read_format_d(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	args++;
	if (form->mod[0])
		return (ft_mod_id((char)arg, form));
	if (form->mod[1])
		return (ft_mod_id((short)arg, form));
	if (form->mod[2])
		return (ft_mod_id((long)arg, form));
	if (form->mod[3])
		return (ft_mod_id((long long)arg, form));
	if (form->mod[4])
		return (ft_mod_id((intmax_t)arg, form));
	if (form->mod[5])
		return (ft_mod_id((ssize_t)arg, form));
	return (ft_mod_id((int)arg, form));
}

int		ft_read_format_p(va_list *args, char **ptr, t_form *form)
{
	int		l;
	void	*arg;

	if (**ptr != 'p')
		return (ft_read_format_id(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = 0;
	}
	l = ft_uintlen_base((long long int)arg, 16, 1);
	if (!form->flags[2] && !form->flags[1])
		ft_putpad(form->flags[1] ? '0' : ' ', form->w - l);
	ft_putstr("0x");
	if (!form->flags[2] && form->flags[1])
		ft_putpad(form->flags[1] ? '0' : ' ', form->w - l);
	ft_putnbr_base((long long int)arg, 16, 0);
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (int)form->w)
		l = form->w;
	args++;
	return (l);
}

int		ft_read_format_ls(va_list *args, char **ptr, t_form *form)
{
	int		l;
	void	*arg;

	if (**ptr != 'S' && !(**ptr == 's' && form->mod[2]))
		return (ft_read_format_p(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = L"(null)";
	}
	if (form->pre >= 0)
		l = ft_lenunstri(arg, form->pre);
	else
		l = ft_lenustri(arg);
	if (l == -1)
		return (-1);
	if (!form->flags[2])
		ft_putpad(form->flags[1] ? '0' : ' ', form->w - l);
	(void)ft_putnustr(arg, l);
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (int)form->w)
		l = form->w;
	args++;
	return (l);
}
