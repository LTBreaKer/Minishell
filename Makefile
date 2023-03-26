NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address #-lreadline

RM = rm -f

LDFLAGS= -L /Users/aharrass/goinfre/homebrew/opt/readline/lib

CPPFLAGS= -I /Users/aharrass/goinfre/homebrew/opt/readline/include

LIBFT = ./libft

LIBFT_AR = ./libft/libft.a

SR_PATH = ./src/

OB_PATH = ./obj/

INCLUDE = -I ./includes

SR =	echo.c		\
			pwd.c			\
			cd.c			\
			env.c			\
			export.c	\
			export_utils.c	\
			unset.c		\
			ft_lst.c	\
			ft_lst2.c	\
			err.c			\
			exit.c		\
			heredoc.c	\
			sigs.c		\
			execution.c	\
			execution_utlis.c	\
			execution_utils2.c	\
			execution_utils3.c	\
			here_expnd.c	\
			get_next_line.c	\
			get_next_line_utils.c	\
			pars_fill_list.c	\
			pars_flist_utils.c	\
			pars_open_files.c \
			pars_ofiles_utils.c \
			pars_flist_stack.c	\
			pars_lexer.c	\
			pars_lexer_utils.c	\
			pars_stack_func.c	\
			pars_syntax_error.c	\
			pars_syntax_utils.c \
			pars_expander.c	\
			pars_expander_utils.c \
			pars_expander_cases.c \
			pars_main.c	\
			pars_qcleaner.c \
			pars_clone_qcleaner.c \
			
SRCS = $(addprefix ${SR_PATH}, ${SR})

OBJS = $(addprefix ${OB_PATH}, ${SR:.c=.o})

all	: ${NAME}

${OB_PATH}%.o	:	${SR_PATH}%.c
			@mkdir -p ${OB_PATH}
			cc ${CFLAGS} ${INCLUDE} -c $< -o $@ 

${NAME}	:	${OBJS}
	make -C ${LIBFT}
	cc ${CFLAGS} ${CPPFLAGS} ${LDFLAGS} ${INCLUDE} ${OBJS} ${LIBFT_AR} -lreadline -o ${NAME}

clean:
			make clean -C ${LIBFT}
			${RM} ${OBJS}
			${RM} -r ${OB_PATH}

fclean: clean
			make fclean -C ${LIBFT}
			${RM} ${NAME}

re:	fclean all

.PHONY: clean fclean re