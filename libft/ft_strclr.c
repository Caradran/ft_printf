/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:10:44 by esuits            #+#    #+#             */
/*   Updated: 2017/11/12 18:14:53 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strclr(char *s)
{
	unsigned long i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		s[i++] = '\0';
}
