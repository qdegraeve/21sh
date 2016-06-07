LIBPATH = libft
LIB = $(LIBPATH)/libft.a

NAME = 21sh

CC = clang

VPATH = src:src/command_line:src/lexer:src/parser
INCLUDES = include/

ifdef FLAGS
	ifeq ($(FLAGS), no)
		CFLAGS=
	endif
	ifeq ($(FLAGS), debug)
		CFLAGS= -Wall -Wextra -Werror -g
	endif
else
	CFLAGS = -Wall -Wextra -Werror
endif


LDFLAGS = -L libft -lft -ltermcap

SRC =  env.c \
	set_unset_env.c \
	main.c \
	get_path.c \
	command_cd.c \
	tools.c \
	prompt.c \
	get_env.c \
	do_fork.c \
	command_line_edit.c \
	command_line_read.c \
	term_control.c \
	signals.c \
	array_functions.c \
	move_cursor.c \
	quote_management.c \
	keys_actions.c \
	copy_paste.c \
	lexer.c \
	tools_lexer.c \
	parser.c \
	custom_strsplit.c \
	heredoc.c \
	exec_simple.c \
	dollar_option.c \
	exec_pipe.c \
	tools_lexer2.c \
	touch_func.c \
	exec_pipe2.c \
	clean_quote.c \
	redir.c \
	get_input.c \
	agregator.c \
	no_tty.c \
	tools_cmd_line.c \

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)

$(LIB):
	make -C $(LIBPATH)

clean:
	make clean -C $(LIBPATH)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBPATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean flcean

