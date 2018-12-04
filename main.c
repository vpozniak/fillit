/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:02:29 by vpozniak          #+#    #+#             */
/*   Updated: 2018/12/04 14:02:30 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


char *read_1(int fd)
{
    int file;
    int i;
    char str;
    char *src;

    i = 0;
    if ((file = read(fd, &str, 1)) < 0)
        return (NULL);
    else
    {
        src = (char *)malloc(sizeof(char) * 545);
        while (file != '\0')
        {
            src[i] = str;
            i++;
            file = read(fd, &str, 1);
        }
        src[i] = '\0';
    }
    return (src);
}

int check(char *conect, int q)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (i + q < 20 + q)
    {
        if (conect[i + q] == '#')
        {
            if ((i + q + 1) < (20 + q) && conect[i + q + 1] == '#')
                count++;
            if ((i + q - 1) >= (0 + q) && conect[i + q - 1] == '#')
                count++;
            if ((i + q + 5) < (20 + q) && conect[i + q + 5] == '#')
                count++;
            if ((i + q - 5) >= (0 + q) && conect[i + q - 5] == '#')
                count++;
        }
        i++;
    }
    if (count == 6 || count == 8)
        return (1);
    return (0);
}

int ft_count(char *conect, int q)
{
    int point;
    int hesh;
    int line;
    int i;

    i = 0;
    point = 0;
    hesh = 0;
    line = 0;
    while (i + q < 20 + q && conect[i + q] != '\0')
    {
        if (conect[i + q] == '.')
            point++;
        if (conect[i + q] == '#')
            hesh++;
        if (conect[i + q] == '\n')
            line++;
        i++;
    }
    if (point == 12 && hesh == 4 && line == 4)
        return (1);
    return (0);
}

int validity(char *conect)
{
    int i;
    int q;

    i = 0;
    q = 0;
    if (!conect)
        return (0);
    while(conect[i + q] != '\0')
    {
        if (!(check(conect, q) && ft_count(conect, q)))
            return (0);
        i = 19;
        if (conect[i + q] == '\n' && conect[i + q + 1] == '\0')
            return (1);
        if (conect[i + q] == '\n' && conect[i + q + 1] == '\n'
                && (conect[i + q + 2] == '.' || conect [i + q + 2] == '#'))
            q = 21 + q;
        else
            return (0);
        i = 0;
    }
    return (1);
}

int main()

{
    int fd;
    fd = open("../test", O_RDONLY);
    if (validity(read_1(fd)) == 0)
        printf("error\n");
    else
        printf("finish\n");
    return (0);
}