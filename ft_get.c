/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajrhou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:17:11 by ayajrhou          #+#    #+#             */
/*   Updated: 2019/10/29 01:47:59 by ayajrhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 60
char *ft_stock(char *line, char *buff, int i)
{
	char *newline;
	int len;
	int j;

	j = 0;
	len = (line ? strlen(line) : 0);
	newline = (char *)malloc(len + i + 1);
	while (j < len)
	{
		newline[j] = line[j];
		j++;
	}
	if (line)
		free(line);
	while (j < len + i)
	{
		newline[j] = buff[j - len];
		j++;
	}
	newline[j] = '\0';
	return(newline);
}
int ft_yfarini(char ***line, char **str, char**buff)
{
	char *tmp;
	int i = 0;
	if ((*str))
	{
		i = 0;
		while ((*str)[i] && (*str)[i] != '\n')
			i++;
		if ((*str)[i] == '\n')
		{
			*(*line) = ft_stock(*(*line), (*str), i);
			tmp = (*str);
			(*str) = ft_stock(0, (*str) + i + 1, strlen((*str)) - i - 1);
			free(tmp);
			tmp = NULL;
			free(*buff);
			*buff = NULL;
			return (1);
		}
		if ((*str)[i] == '\0')
		{
			*(*line) = ft_stock(*(*line), (*str), i);
			free((*str));
			(*str) = NULL;
		}
	}
	return (0);
}
int get_next_line(int fd, char **line)
{
	int i;
	int ret;
	static char *str;
	char *buff;
	char	*tmp;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	*line = strdup("");
	if (ft_yfarini(&line, &str, &buff) == 1)
		return (1);
	while ((ret = read(fd, buff, BUFFER_SIZE)))
	{
		i = 0;
		if (buff[ret] != -1)
			buff[ret] = '\0';
		while(buff[i] && buff[i] != '\n')
			i++;
		if (buff[i] == '\n'  || buff[i] == -1)
		{
			*line = ft_stock(*line, buff, i);
			tmp = str;
			str = ft_stock(str, buff + i + 1, ret - i - 1);
			free(tmp);
			tmp = NULL;
			free(buff);
			return (1);
		}
		if (buff[i] == '\0')
			*line = ft_stock(*line, buff, i);
	}
	free(buff);
	buff = NULL;
	return (0);
}
