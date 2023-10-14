NAME	:= hotrace
SRCS	:= hotrace.c \
		hashmap.c \
		get_next_line.c \
		utils.c \
		string_utils.c \
		print_utils.c

TEST_SRCS	:= profile.c \
			hashmap.c \
			get_next_line.c \
			utils.c \
			string_utils.c \
			print_utils.c

OBJS	= 	${SRCS:.c=.o}
TEST_OBJS	= 	${TEST_SRCS:.c=.o}

CC		= 	cc
RM		= 	rm -f

CFLAGS	= 	-Wall -Wextra -Werror -g
TEST_CFLAGS	= 	-Wall -Wextra -Werror -O3 -flto -march=native -ffast-math

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

.PHONY:		all clean fclean re test

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

test:		${TEST_OBJS}
			${CC} ${TEST_CFLAGS} ${TEST_OBJS} -o test
			@echo "Profiling..."
			@./test | grep "PROFILE" > profile.log
			@echo "Done"
