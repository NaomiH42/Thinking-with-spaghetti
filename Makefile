NAME = philo
NAME_B = philo_b

SRCS =	philosophers.c philo_utilities.c philo_utilities2.c philo_utilities3.c philo_utilities4.c
SRCS_B = philosophers_bonus.c philo_b_utilities.c philo_b_utilities2.c
FLAGS = -pthread
CC_FLAGS = -Wall -Werror -Wextra ${FLAGS}

all:	${NAME}

${NAME}:
	cc ${CC_FLAGS} ${SRCS} -o ${NAME}

bonus:
	cc ${CC_FLAGS} ${SRCS_B} -o ${NAME_B}

clean:
	rm -rf ${NAME}
	rm -rf ${NAME_B}

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re
