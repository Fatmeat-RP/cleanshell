# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 18:00:59 by cben-bar          #+#    #+#              #
#    Updated: 2022/07/09 01:21:51 by acarle-m         ###   ########.fr        #
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

SRCSDIR		=	./srcs/
\
SRCS 		=	$(SRCSDIR)check_consec_pipe.c\
				$(SRCSDIR)check_empty_line.c\
				$(SRCSDIR)check_first_pipe.c\
				$(SRCSDIR)check_last_chev.c\
				$(SRCSDIR)check_last_pipe.c\
				$(SRCSDIR)check_multi_chev.c\
				$(SRCSDIR)check_multi_node_chev.c\
				$(SRCSDIR)check_no_file_name.c\
				$(SRCSDIR)check_quote.c\
				$(SRCSDIR)cleaner.c\
				$(SRCSDIR)cmd_utils.c\
				$(SRCSDIR)cut_redir.c\
				$(SRCSDIR)dispatch_var.c\
				$(SRCSDIR)dollar.c\
				$(SRCSDIR)exec_add_back.c\
				$(SRCSDIR)exec.c\
				$(SRCSDIR)execcmd.c\
				$(SRCSDIR)exec_last.c\
				$(SRCSDIR)exec_split.c\
				$(SRCSDIR)fill_var.c\
				$(SRCSDIR)first_check.c\
				$(SRCSDIR)flaggeur_file_name.c\
				$(SRCSDIR)flaggeur_redir.c\
				$(SRCSDIR)free_memory.c\
				$(SRCSDIR)ft_itoa.c\
				$(SRCSDIR)ft_split_it.c\
				$(SRCSDIR)ft_strcmp.c\
				$(SRCSDIR)ft_strcpy.c\
				$(SRCSDIR)ft_strdup.c\
				$(SRCSDIR)ft_strjoin.c\
				$(SRCSDIR)ft_strlen.c\
				$(SRCSDIR)ft_utils.c\
				$(SRCSDIR)ident_cmd.c\
				$(SRCSDIR)init.c\
				$(SRCSDIR)init_exec.c\
				$(SRCSDIR)lst_last.c\
				$(SRCSDIR)lst_size.c\
				$(SRCSDIR)minishell_main.c\
				$(SRCSDIR)parse_add_back.c\
				$(SRCSDIR)parse.c\
				$(SRCSDIR)parsing.c\
				$(SRCSDIR)parsing_printer.c\
				$(SRCSDIR)printer_error.c\
				$(SRCSDIR)quote_supp.c\
				$(SRCSDIR)redirection.c\
				$(SRCSDIR)re_flaggeur.c\
				$(SRCSDIR)set_pars.c\
				$(SRCSDIR)set_parseur.c\
				$(SRCSDIR)set_var.c\
				$(SRCSDIR)signal.c\
				$(SRCSDIR)split_block.c\
				$(SRCSDIR)struct2.c\
				$(SRCSDIR)supp_empty_node.c\
				$(SRCSDIR)tote.c\
				$(SRCSDIR)universal_flaggeur.c\
				$(SRCSDIR)utils2.c\
				$(SRCSDIR)utils.c


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
			@$(CC) -fsanitize=address $(OBJS) ${CFLAGS} $(HEADER) -o $(NAME) $(LIBS)

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
