/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:37:46 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 15:37:47 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "hotrace.h"

bool	is_empty(char *str)
{
	if (str && *str == '\n')
		return (true);
	return (false);
}

bool	gnl(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line != NULL)
		return (true);
	return (false);
}

bool	build_hashmap(t_table **ht)
{
	char	*line;
	char	*key;
	char	*value;

	*ht = hash_table_create(MAX_HASH_LEN, hash_djb2);
	if (!*ht)
	{
		perror("Error: Create hash table failed.");
		return (false);
	}
	while (gnl(STDIN_FILENO, &line))
	{
		if (is_empty(line))
		{
			free(line);
			break ;
		}
		key = line;
		if (!gnl(STDIN_FILENO, &line) || is_empty(line))
			return (true);
		value = line;
		// printf("insert %s: %s\n", key, value);
		hash_table_insert(*ht, key, value);
	}
	return (true);
}

void	search(t_table **ht)
{
	int		i;
	char	*key;
	char	*value;

	while (gnl(STDIN_FILENO, &key))
	{
		// printf("searching key: %s", key);
		value = (char *)hash_table_lookup(*ht, key);
		if (value)
		{
			ft_putstr_fd(value, STDOUT_FILENO);
			save_free((void**)&key);
		}
		else
		{
			i = 0;
			while (key[i] && key[i] != '\n')
				ft_putchar_fd(key[i++], STDOUT_FILENO);
			ft_putstr_fd(": Not found.\n", STDOUT_FILENO);
		}
		save_free((void**)&key);
	}
}

void process_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    t_table	*ht;
	clock_t start_time, end_time;
    double elapsed_time;

    if (fd) {
        printf("Open file name: %s\n", filename);
        dup2(fd, STDIN_FILENO);
		start_time = clock();
        if (!build_hashmap(&ht))
            return ;
        search(&ht);
        hash_table_destroy(ht);
		end_time = clock();
		elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
		printf("[PROFILE] Time taken for processing file %s: %f seconds\n", filename, elapsed_time);
        close(fd);
    } else {
        fprintf(stderr, "Could not open file: %s\n", filename);
    }
}

void process_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_REG) {
            char filename[1024];
            snprintf(filename, sizeof(filename), "%s/%s", path, entry->d_name);
            process_file(filename);
			// break;
        }
    }
    closedir(dir);
}

int main() {
    const char *directory_path = "./tests";  // Replace with the desired directory path
    process_directory(directory_path);

    return 0;
}