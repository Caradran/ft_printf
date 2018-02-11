/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 21:17:11 by esuits            #+#    #+#             */
/*   Updated: 2018/01/30 19:40:54 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../ft_printf.h"
#include "locale.h"
#include "../libft/libft.h"
#include <limits.h>
int main(int argc, char **argv)
{
	int i;
	int s[4];
	char c;

//	setlocale(LC_ALL, "");
	if (argv[1][0] == 's')
	{
		ft_putstr("my printf : ");
		i = ft_printf("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C","bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플');
		ft_putstr("return : ");
		ft_putnbr(i);
		ft_putstr("\n\nreal printf : ");
		i = printf("%s%d%p%%%S%D%i%o%O%u%U%x%X%c%C","bonjour", 42, &c, L"暖炉", LONG_MAX, 42, 42, 42, 100000, ULONG_MAX, 42, 42, 'c', L'플');
		printf("return :\n");
		ft_putnbr(i);
		ft_putchar('\n');
	}
	if (argv[1][0] == 'S')
	{
		i = 0;
		ft_putstr("my printf : ");
		i = ft_printf("%S\n", (wchar_t*)'a');
		printf("return : %i\n", i);
		ft_putstr("real printf : ");
		i = printf("%ls\n", (wchar_t*)'a');
		printf("return : %i\n", i);
	}
	if (argv[1][0] == '%')
	{
		ft_putstr("my printf : ");
		i = ft_printf("%.3%");
		printf("\nreturn : %i\n", i);
		ft_putstr("\nreal printf : ");
		i = printf("%.3%");
		printf("return : %i\n", i);
	}
	if (argv[1][0] == 'c')
	{
		ft_putstr("my printf : ");
		i = ft_printf("\n%-+-12.7Dt%0 4i %04.2% et %lc titi", 125, 124, 256);
		ft_putnbr(i);
		ft_putstr("\nreal printf : ");
		i = printf("\n%-+-12.7Dt%0 4i %04.2% et %lc titi", 125, 124, 256);
		ft_putnbr(i);
		ft_putchar('\n');
	}
	if (argv[1][0] == 'C')
	{
		ft_putstr("my printf : ");
		i = ft_printf("%.5lc\n", ft_atoi(argv[2]));
		ft_putnbr(i);
		ft_putstr("\nreal printf : ");
		i = printf("%.5lc\n", ft_atoi(argv[2]));
		ft_putnbr(i);
		ft_putchar('\n');
	}
	if (argv[1][0] == 'p')
	{
		ft_putstr("my printf : ");
		i = ft_printf(" %.5p\n",  ft_atoi(argv[2]));
		printf("return : %i\n", i);
		ft_putstr("real printf : ");
		i = printf(" %.5p\n", (void*)ft_atoi(argv[2]));
		printf("return : %i\n", i);
	}
	if (argv[1][0] == 'i')
	{
		ft_putstr("my printf : ");
		i = ft_printf(NULL);
		ft_putnbr(i);
//		ft_putstr("real printf : ");
//		printf(NULL);
	}
	if (argv[1][0] == 'd')
	{
		ft_putstr("my printf : ");
		i = ft_printf("'%05.d'\n", ft_atoi(argv[2]));
		ft_putnbr(i);
		ft_putstr("\nreal printf : ");
		i = printf("'%05.d'\n", (int)ft_atoi(argv[2]));
		ft_putnbr(i);
	}
	if (argv[1][0] == 'x')
	{
		ft_putstr("my printf : ");
		ft_printf("%x\n", ft_atoi(argv[2]));
		ft_putstr("real printf : ");
		printf("%x\n", (int)ft_atoi(argv[2]));
	}
	if (argv[1][0] == 'X')
	{
		ft_putstr("my printf : ");
		ft_printf("%X\n", ft_atoi(argv[2]));
		ft_putstr("real printf : ");
		printf("%X\n", (int)ft_atoi(argv[2]));
	}
	if (argv[1][0] == 'o')
	{
		ft_putstr("my printf : ");
		i = ft_printf("%#.o\n", ft_atoi(argv[2]));
		ft_putnbr(i);
		ft_putstr("\nreal printf : ");
		i = printf("%#.o\n", ft_atoi(argv[2]));
		ft_putnbr(i);
	}
	if (argv[1][0] == 'O')
	{
		ft_putstr("my printf : ");
		ft_printf("%O\n", ft_atoi(argv[2]));
		ft_putstr("real printf : ");
		printf("%O\n", (long)ft_atoi(argv[2]));
	}
	if (argv[1][0] == 'D')
	{
		ft_putstr("my printf : ");
//		i = ft_printf("%.5D\n", ft_atoi(argv[2]));
		i = ft_printf("% 20.12ld et % 05D% 4.8hi !", 0x11ffaa147, 24, (short)-2345);
		printf("%i \nreal printf : ", i);
//		i = printf("%.5D\n", (long)ft_atoi(argv[2]));
		i = printf("% 20.12ld et % 05D% 4.8hi !", 0x11ffaa147, 24, (short)-2345);
		printf("%i \n", i);
	}
	if (argv[1][0] == 'u')
	{
		ft_putstr("my printf : ");
		i = ft_printf("%.5u\n", (unsigned int)ft_atoi(argv[2]));
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putstr("real printf : ");
		i = printf("%.5u\n", (unsigned int)ft_atoi(argv[2]));
		ft_putnbr(i);
		ft_putchar('\n');
	}
	if (argv[1][0] == 'U')
	{
		ft_putstr("my printf : ");
		ft_printf("%U\n", (unsigned long)ft_atoi(argv[2]));
		ft_putstr("real printf : ");
		printf("%U\n", (unsigned long)ft_atoi(argv[2]));
	}
	return (0);
}
