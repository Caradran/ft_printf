/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 06:53:44 by esuits            #+#    #+#             */
/*   Updated: 2018/01/30 19:27:37 by esuits           ###   ########.fr       */
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

int		ft_read_format(va_list *args, char **ptr, t_form *form)
{
	int		len;

	len = 0;
	if (**ptr)
		len += ft_read_format_c(args, ptr, form, 1);
	return (len);
}

int		ft_read_format_s(va_list *args, char **ptr, t_form *form)
{
	int		l;
	void	*arg;

	if (**ptr != 's' || form->mod[2])
		return (ft_read_format_ls(args, ptr, form));
	if (!(arg = va_arg(*args, void*)))
	{
		ft_memdel(arg);
		arg = "(null)";
	}
	if (form->pre >= 0)
		l = ((int)ft_strlen(arg) > form->pre) ? form->pre : ft_strlen(arg);
	else
		l = ft_strlen(arg);
	if (!form->flags[2])
		ft_putpad(form->flags[1] ? '0' : ' ', form->w - l);
	write(1, arg, l);
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (int)form->w)
		l = form->w;
	args++;
	return (l);
}

int		ft_read_mod(va_list *args, char **ptr, t_form *form)
{
	ft_bzero((void *)&(form->mod), 6);
	while ((**ptr == 'h' || **ptr == 'l' || **ptr == 'j' || **ptr == 'z' ||
			!ft_strncmp(*ptr, "ll", 2) || !ft_strncmp(*ptr, "hh", 2)))
	{
		if (!ft_strncmp(*ptr, "hh", 2))
		{
			form->mod[0] = 1;
			(*ptr)++;
		}
		else if (**ptr == 'h')
			form->mod[1] = 1;
		else if (!ft_strncmp(*ptr, "ll", 2))
		{
			form->mod[3] = 1;
			(*ptr)++;
		}
		else if (**ptr == 'l')
			form->mod[2] = 1;
		else if (**ptr == 'j')
			form->mod[4] = 1;
		else if (**ptr == 'z')
			form->mod[5] = 1;
		(*ptr)++;
	}
	return (ft_read_format_s(args, ptr, form));
}

int		ft_read_w_pre(va_list *args, char **ptr, t_form *form)
{
	form->w = (unsigned int)ft_atoi(*ptr);
	if (form->w)
		(*ptr) += ft_uintlen_base((unsigned long long)form->w, 10, 0);
	if (**ptr == '.')
	{
		(*ptr)++;
		form->pre = (unsigned int)ft_atoi(*ptr);
	}
	else
		form->pre = -1;
	while (**ptr == '0')
		(*ptr)++;
	if (form->pre > 0)
		(*ptr) += ft_uintlen_base((unsigned long long)form->pre, 10, 0);
	return (ft_read_mod(args, ptr, form));
}

int		ft_read_flag(va_list *args, char **ptr)
{
	t_form	form;

	ft_bzero((void *)&form.flags, 5);
	while (**ptr == '#' || **ptr == '0' || **ptr == '-' || **ptr == '+'
			|| **ptr == ' ')
	{
		if (**ptr == '#')
			form.flags[0] = 1;
		else if (**ptr == '0')
			form.flags[1] = 1;
		else if (**ptr == '-')
			form.flags[2] = 1;
		else if (**ptr == '+')
			form.flags[3] = 1;
		else if (**ptr == ' ')
			form.flags[4] = 1;
		(*ptr)++;
	}
	if (!**ptr)
		return (0);
	return (ft_read_w_pre(args, ptr, &form));
}
