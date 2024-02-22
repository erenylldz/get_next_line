/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryildiz <eryildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:45:37 by eryildiz          #+#    #+#             */
/*   Updated: 2023/12/21 13:00:34 by eryildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*str[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = processes_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = line_control(str[fd]);
	str[fd] = string(str[fd]);
	return (line);
}

char	*processes_str(int fd, char *str)
{
	char	*temp;
	int		readbyte;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp == NULL)
		return (0);
	readbyte = 1;
	while (!ft_strchr(str, '\n') && readbyte != 0)
	{
		readbyte = read(fd, temp, BUFFER_SIZE);
		if (readbyte == -1)
		{
			free (temp);
			free(str);
			return (0);
		}
		temp[readbyte] = '\0';
		str = ft_strjoin(str, temp);
	}
	free (temp);
	return (str);
}

char	*line_control(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*string(char *str)
{
	char	*str1;
	int		a;
	int		b;

	a = 0;
	while (str[a] && str[a] != '\n')
		a++;
	if (!str[a])
	{
		free(str);
		return (NULL);
	}
	str1 = (char *)malloc(sizeof(char) * (ft_strlen(str) - a + 1));
	if (!str1)
		return (NULL);
	a++;
	b = 0;
	while (str[a])
		str1[b++] = str[a++];
	str1[b] = '\0';
	free(str);
	return (str1);
}
