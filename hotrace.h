/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:37:41 by lyeh              #+#    #+#             */
/*   Updated: 2023/10/15 20:48:45 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

/* for perror */
# include <stdio.h>
/* for malloc, free */
# include <stdlib.h>
/* for write */
# include <unistd.h>
/* for uintxx_t */
# include <stdint.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# define MAX_HASH_BITS 24
# define MAX_HASH_LEN 16777216

typedef uint64_t		t_hash_function(const char *);

typedef struct hash_node
{
	const char			*key;
	const char			*value;
	uint64_t			og_hash;
	struct hash_node	*next;
}						t_node;

typedef struct hash_table
{
	uint32_t			size;
	t_hash_function		*hash;
	t_node				**elements;

}						t_table;

t_table					*hash_table_create(uint32_t size, t_hash_function *f);
void					hash_table_destroy(t_table *ht);
void					hash_table_print(t_table *ht);
bool					hash_table_insert(t_table *ht, const char *key,
							const char *value);
void					*hash_table_lookup(t_table *ht, char *key);
void					*hash_table_delete(t_table *ht, const char *key);
uint32_t				convert_hash(uint64_t hash);
uint64_t				hash_djb2(const char *str);

void					*ft_calloc(size_t count, size_t size);
void					*ft_memset(void *dst, int val, size_t len);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *s1);
int						ft_strncmp(const char *s1, const char *s2, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t len);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
bool					is_empty(char *str);

char					*get_next_line(int fd);
void					save_free(void **f);
void					remove_last_newline(char **s);

#endif