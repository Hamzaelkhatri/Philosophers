/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:24:26 by helkhatr          #+#    #+#             */
/*   Updated: 2021/05/04 15:09:35 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long check(int counter, int sign, int result)
{
    if (counter > 19)
    {
        if (sign > 0)
            return (-1);
        else
            return (0);
    }
    return (result * sign);
}

long long ft_atoi(const char *str)
{
    long long i;
    long long sign;
    long long result;
    long long counter;

    i = 0;
    sign = 1;
    result = 0;
    counter = 0;
    while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f' || str[i] == '\n' || str[i] == '\v' || str[i] == '\t')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1 * sign;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0';
        i++;
        counter++;
    }
    return (check(counter, sign, result));
}