# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 18:00:59 by cben-bar          #+#    #+#              #
#    Updated: 2022/05/09 14:40:25 by acarle-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

ECHO		=	$(BIN)echo

PWD			=	$(BIN)pwd

ENV			=	$(BIN)env

#$(EXIT)	=	$(BIN)exit

#$(CD)		=	$(BIN)cd

#$(EXPORT)	=	$(BIN)export

#$(UNSET)	=	$(BIN)unset

SRCSDIR		= ./srcs/

SRCS 		=		$(SRCSDIR)*.c

ECHO_SRCS	=	./builtins/built_in_echo.c

PWD_SRCS	=	./builtins/built_in_pwd.c

ENV_SRCS	=	./builtins/built_in_env.c

OBJS 		=	${SRCS:.c=.o}

HEADER		=	-I includes -I ~/.brew/opt/readline/include

CC 			=	gcc

CFLAGS 		=	-Wall -Wextra -Werror

LIBS		=	-L ~/.brew/opt/readline/lib -lreadline

BIN			=	./bin/

OBJSDIR		=	./objs/

DEPS		=	./includes/builtins.h	\
				./includes/minishell.h	\

OBJS		=	$(SRCS:$(SRCSDIR)%.c=$(OBJSDIR)%.o)

all			: 	${NAME} #builtins

echo		:	${DEPS} $(ECHO_SRCS)
			@mkdir -p $(BIN)
			@$(CC) $(ECHO_SRCS) $(HEADER) -o $(ECHO) $(LIBS)

pwd			:	${DEPS} $(PWD_SRCS)
			@mkdir -p $(BIN)
			@$(CC) $(PWD_SRCS) $(HEADER) -o $(PWD) $(LIBS)

env			:	${DEPS} $(PWD_SRCS)
			@mkdir -p $(BIN)
			@$(CC) $(PWD_SRCS) $(HEADER) -o $(PWD) $(LIBS)

#exit		:	${DEPS} $(PWD_SRCS)
#			@mkdir -p $(BIN)
#			@$(CC) $(PWD_SRCS) $(HEADER) -o $(PWD) $(LIBS)

#cd			:	${DEPS} $(PWD_SRCS)
#			@mkdir -p $(BIN)
#			@$(CC) $(PWD_SRCS) $(HEADER) -o $(PWD) $(LIBS)

#export		:	${DEPS} $(PWD_SRCS)
#			@mkdir -p $(BIN)
#			@$(CC) $(PWD_SRCS) $(HEADER) -o $(PWD) $(LIBS)

#unset		:	${DEPS} $(PWD_SRCS)
#			@mkdir -p $(BIN)
#			@$(CC) $(PWD_SRCS) $(HEADER) -o $(PWD) $(LIBS)


${NAME}		:	${OBJS} ${DEPS} Makefile
			@$(CC) $(OBJS) ${CFLAGS} $(HEADER) -o $(NAME) $(LIBS)

$(OBJS)		:	$(OBJSDIR)%.o	:	$(SRCSDIR)%.c ${DEPS} Makefile
			@mkdir -p $(OBJSDIR)
			@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

builtins	:	$(DEPS) echo pwd env #exit cd export unset

clean		:
			@rm -rf ${OBJSDIR}

fclean		: 	clean
			@rm -rf ${NAME} $(BIN)

re			:	fclean all

.PHONY		:	all clean fclean re
