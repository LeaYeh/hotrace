NAME	:= hotrace
SRCS	:= hotrace.c \
		hashmap.c \
		get_next_line.c \
		utils.c \
		string_utils.c

OBJS	= 	${SRCS:.c=.o}

CC		= 	cc
RM		= 	rm -f

CFLAGS	= 	-Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

.PHONY:		all clean fclean re

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all