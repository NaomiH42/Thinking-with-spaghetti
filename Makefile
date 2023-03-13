NAME = philo

SRCS =	philosophers.c philo_utilities.c philo_utilities2.c philo_utilities3.c

FLAGS = -pthread
CC_FLAGS = -Wall -Werror -Wextra ${FLAGS}

all:	${NAME}

${NAME}:	${SRCS}
	cc ${CC_FLAGS} ${SRCS} -o ${NAME}

clean:
	rm -rf ${NAME}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re
