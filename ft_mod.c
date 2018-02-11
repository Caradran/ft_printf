/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:16:01 by esuits            #+#    #+#             */
/*   Updated: 2018/01/30 19:25:59 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_mod_id2(long long arg, t_form *form, int l, int len)
{
	if ((form->flags[3] || form->flags[4]) && (int)arg >= 0)
		form->flags[3] ? write(1, "+", 1) : write(1, " ", 1);
	if (!form->flags[2] && (form->flags[1] && (form->pre < len ||
		(((int)form->w > form->pre) && (form->flags[3] || form->flags[4])))))
		ft_putpad('0', form->w - l);
	while (form->pre-- > (len - (arg < 0)))
		write(1, "0", 1);
	if (form->pre != -1 || ((int)arg != 0))
		ft_putnbr_base(arg, 10, 2);
	else if (form->w)
		write(1, " ", 1);
	else
		--l;
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (int)form->w)
		l = form->w;
	return (l);
}

int		ft_mod_id(long long arg, t_form *form)
{
	int len;
	int l;

	len = ((arg < 0) ? ft_intlen(arg) : ft_intlen(arg));
	l = ((len >= form->pre) ? len : form->pre);
	if (form->pre != -1)
		form->flags[1] = 0;
	if (len > form->pre && arg)
		form->pre = -1;
	l += ((form->pre >= (int)form->w) && (arg < 0)) || ((form->flags[3]
				|| form->flags[4]) && (arg >= 0) && (((int)form->w >= len
						|| (int)form->w >= form->pre)));
	if (!form->flags[2] && !(form->flags[1] && (form->pre <= len ||
					(((int)form->w > form->pre) && (form->flags[3] ||
						form->flags[4])))))
		ft_putpad(' ', form->w - l - (arg < 0 && (form->pre < (int)form->w)
					&& form->pre != -1));
	if (arg < 0)
		write(1, "-", 1);
	return (ft_mod_id2(arg, form, l, len));
}

int		ft_mod_oo(unsigned long long arg, t_form *form)
{
	int l;
	int len;

	len = ft_uintlen_base(arg, 8, form->flags[0] && arg);
	l = (((len -= (!form->pre && arg == 0)) > form->pre) ? len : form->pre);
	if (!form->flags[2])
		ft_putpad((form->flags[1] && form->pre == -1) ? '0' : ' ', form->w - l);
	while (form->pre-- > len)
		write(1, "0", 1);
	if (((form->pre == -1 && (++l || 1)) || (arg)) && form->flags[0])
		write(1, "0", 1);
	if (form->pre != -1 || !(--l || 1))
		ft_putnbr_base(arg, 8, 0);
	else if (arg && !((form->pre > len) && (++l || 1)))
		ft_putnbr_base((unsigned int)arg, 8, 0);
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (long)form->w)
		l = form->w;
	return (l + (form->pre == -1 && !arg && form->flags[0]));
}

int		ft_mod_uu(unsigned long long arg, t_form *form)
{
	int len;
	int l;

	len = ft_uintlen_base(arg, 10, 0);
	l = (len > form->pre) ? len : form->pre;
	if (!form->flags[2])
		ft_putpad((form->flags[1] && form->pre == -1) ? '0' : ' ', form->w - l);
	while (form->pre-- > len)
		write(1, "0", 1);
	if (!(arg == 0 && form->pre == -1))
		ft_putnbr_base(arg, 10, 0);
	else
		l--;
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (long)form->w)
		l = form->w;
	return (l);
}

int		ft_mod_xx(unsigned long long arg, t_form *form, char **ptr)
{
	int len;
	int l;

	len = ft_uintlen_base(arg, 16, 0) - (!form->pre && !arg);
	l = (len > form->pre) ? len : form->pre;
	if (!form->flags[2] && !(form->flags[1] && form->pre == -1))
		ft_putpad(' ', form->w - l - form->flags[0] * 2);
	if (form->flags[0] && arg)
		((l += 2) && **ptr == 'x') ? write(1, "0x", 2) : write(1, "0X", 2);
	if (!form->flags[2] && form->flags[1] && form->pre == -1)
		ft_putpad('0', form->w - l);
	while (form->pre-- > len)
		write(1, "0", 1);
	if (!(!arg && form->pre == -1))
		(**ptr == 'x') ? ft_putnbr_base(arg, 16, 0) :
			ft_putnbr_base(arg, 16, 1);
	if (form->flags[2])
		ft_putpad(' ', form->w - l);
	if (l < (long)form->w)
		l = form->w;
	return (l);
}
