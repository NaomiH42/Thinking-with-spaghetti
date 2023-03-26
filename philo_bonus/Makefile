NAME_B = philo_bonus

SRCS_B = philosophers_bonus.c philo_b_utilities.c philo_b_utilities2.c

FLAGS = -pthread
CC_FLAGS = -Wall -Werror -Wextra ${FLAGS}

all:	${NAME_B}

${NAME_B}:
	cc ${CC_FLAGS} ${SRCS_B} -o ${NAME_B}

clean:
	rm -rf ${NAME_B}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re
