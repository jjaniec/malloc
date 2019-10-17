# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 18:15:37 by jjaniec           #+#    #+#              #
#    Updated: 2019/10/17 14:25:58 by jjaniec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LNK		=	libft_malloc.so
TESTS_EXEC = $(addprefix $(LNK),.tests)

SRC_NAME = ft_malloc.c \
			ft_calloc.c \
			ft_free.c \
			ft_realloc.c \
			free_alloc.c \
			get_alloc_header.c \
			show_alloc_mem.c \
			ft_free_all.c \
			ft_putnbr_base.c \
			write_header.c \
			get_alloc_type.c

INCLUDES_NAME = malloc.h

TESTS_SRC_NAME = main.c

SRC_DIR = ./srcs/
INCLUDES_DIR = ./includes/
TESTS_DIR = ./tests/
OBJ_DIR = ./objs/
LIBFT_DIR = ./libft/
LIBTAP_DIR = ./libtap/

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))
TESTS_OBJ = $(addprefix $(TESTS_DIR),$(TESTS_SRC_NAME:.c=.o))
TESTS_SRCS_OBJS_NAME = $(subst ./objs/main.o,,$(OBJ)) $(TESTS_OBJ) $(addprefix $(LIBTAP_DIR),"/tap.o")
LIBFT = $(addprefix $(LIBFT_DIR),"/libft.a")

###### COMPILATION ######
CC = gcc
CFLAGS = -Wall -Wextra -g -D_GNU_SOURCE -std=c11 -fPIC # -Werror -O3
ADDITIONAL_FLAGS = # Used to know when running on travis-ci
CFLAGS += $(ADDITIONAL_FLAGS)
IFLAGS = -I./libft -I./$(INCLUDES_DIR)
LFLAGS = -L./libft/ -lft
LDFLAGS = -fPIC -shared

###### FLAGS ######
DEV_FLAGS = #-fsanitize=address -fno-omit-frame-pointer
CFLAGS += $(DEV_FLAGS)
COVERAGE_CFLAGS = -coverage -O0
LIBTAP_FLAGS = -I$(LIBTAP_DIR)

MAKEFILE_STATUS = $(addprefix $(LIBFT_DIR),"/.makefile_status.sh")

UNAME_S := $(shell uname -s)

define ui_line
    $(MAKEFILE_STATUS) $(1) $(2) || true
endef

# RULES

all : $(NAME) $(LNK)

re: fclean all

# OBJ RULES

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(INCLUDES_DIR), $(INCLUDES_NAME))
	@mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ_SUBDIRS))
	@$(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@ && $(call ui_line, $@, $(NAME))

$(TESTS_DIR)%.o: $(TESTS_DIR)%.c $(addprefix $(TESTS_DIR),/tests.h)
	$(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@

$(NAME): $(LIBFT) $(OBJ)
ifeq ($(UNAME_S),Linux)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LFLAGS)
endif
ifeq ($(UNAME_S),Darwin)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
endif

$(TESTS_DIR)%.o: $(TESTS_DIR)%.c $(addprefix $(TESTS_DIR),/tests.h)
	$(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@

$(LIBFT): $(LIBFT_DIR)
	@make -C ./libft/

$(LNK): $(NAME)
	[ -L $(LNK) ] || (ln -s $(NAME) $(LNK))

# TESTS RULES

$(TESTS_EXEC): $(LIBFT) $(OBJ) $(TESTS_OBJ)
	@$(CC) $(CFLAGS) -c $(IFLAGS) $(addprefix $(LIBTAP_DIR),"/tap.c") -o $(addprefix $(LIBTAP_DIR),"/tap.o")
	@$(CC) $(CFLAGS) $(TESTS_SRCS_OBJS_NAME) $(LIBFT) -o $(TESTS_EXEC) $(LFLAGS)

tests: CFLAGS += $(COVERAGE_CFLAGS) $(LIBTAP_FLAGS)
tests: all $(LIBTAP_DIR) $(TESTS_EXEC)

tests_malloc1:
	git clone https://github.com/mmeisson/tests_malloc.git tests_malloc1
	make -C tests_malloc1

tests_malloc2:
	git clone https://github.com/bnoufel/malloc_test.git tests_malloc2

tests_full: all tests_malloc1 tests_malloc2
	(cd tests_malloc1 && ./test_malloc)
	(cd tests_malloc2 && ./test.sh --all --debug <<<'9')

coverage: tests
	gcov $(subst ./objs/log.o,,$(TESTS_SRCS_OBJS_NAME))

# CLEAN RULES

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(TESTS_EXEC)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(LNK)

# LIBS RULES

$(LIBFT_DIR):
	git clone https://github.com/jjaniec/libft $(LIBFT_DIR) || true

$(LIBTAP_DIR):
	git clone https://github.com/zorgnax/libtap.git $(LIBTAP_DIR) || true

.PHONY : clean re tests all
