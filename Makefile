NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g #-lreadline

RM = rm -f

LIBFT = ./libft

LIBFT_AR = ./libft/libft.a

SR_PATH = ./src/

OB_PATH = ./obj/

INCLUDE = -I ./includes

SR =	echo.c		\
			test.c		\
			pwd.c			\
			cd.c			\
			env.c			\
			export.c	\
			unset.c		\
			ft_lst.c	\
			err.c			\
			execution.c	\

SRCS = $(addprefix ${SR_PATH}, ${SR})

OBJS = $(addprefix ${OB_PATH}, ${SR:.c=.o})

all	:	${NAME}

${OB_PATH}%.o	:	${SR_PATH}%.c
			@mkdir -p ${OB_PATH}
			cc ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJS}
	make -C ${LIBFT}
	cc ${CFLAGS} ${INCLUDE} -o ${NAME} ${OBJS} ${LIBFT_AR}

clean:
			make clean -C ${LIBFT}
			${RM} ${OBJS}
			${RM} -r ${OB_PATH}

fclean: clean
			make fclean -C ${LIBFT}
			${RM} ${NAME}

re:	fclean all

.PHONY: clean fclean re