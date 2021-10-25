NAME		:=	minishell
SRCS_DIR	:=	srcs
SRCS_FILES	:=	minishell.c \
				env/env.c \
				env/env_2.c\
				clear.c \
				parsing/parsing.c \
				parsing/var_env.c \
				parsing/tokenizing.c \
				parsing/trim_space.c \
				parsing/signal.c\
				parsing/export_quote.c\
				parsing/utils/is_quotes_pipe.c \
				parsing/utils/is_separator.c \
				parsing/utils/is_bracket_quote.c \
				parsing/utils/is_pipe.c \
				parsing/utils/print_cmds.c \
				parsing/utils/print_content_cmd.c \
				parsing/utils/is_state_symbol.c \
				parsing/utils/is_space_and_next.c \
				parsing/utils/trim_space_export.c \
				parsing/utils/is_space.c \
				parsing/utils/fill_esc_quote.c \
				parsing/errors/error_multi_line.c \
				parsing/states/state_default.c \
				parsing/states/state_redir.c \
				parsing/states/state_quotes.c \
				init/init.c \
				init/init_content.c \
				builtins/builtin.c\
				builtins/echo.c\
				builtins/cd.c\
				builtins/export.c\
				builtins/exit.c\
				exec/exec.c\
				exec/heredocs.c\
				exec/redir_pipe.c\
				exec/misc.c\
				exec/get_path.c\
				exec/child_process.c\

SRCS		:=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))

HDRS_DIR	:=	includes
HDRS_FILES	:=	minishell.h
HDRS		:=	$(addprefix $(HDRS_DIR)/,$(HDRS_FILES))

OBJS		:=	$(SRCS:srcs/%.c=objs/%.o)

LIBFT_DIR	:= libft
LIBS		:= $(LIBFT_DIR)/libft.a

ifneq ($(shell uname), Linux)
READLINE_LIB_DIR_FLAG := -L$(shell brew --prefix readline)/lib
READLINE_INC_DIR_FLAG := -I$(shell brew --prefix readline)/include
endif

CC			:=	gcc 
CFLAGS		:=	-Wall -Wextra -Werror -Iincludes -g
SANFLAGS	:=	-fsanitize=address -g3
LDFLAGS		:= -lreadline
RM			:=	rm -f

ifeq ($(ASAN), 1)
CFLAGS := $(CFLAGS) $(SANFLAGS)
LDFLAGS := $(LDFLAGS) $(SANFLAGS)
endif

all:			$(NAME)

$(NAME):		libs $(OBJS)
				@echo "Linking $(NAME)"
				@$(CC) $(READLINE_LIB_DIR_FLAG) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

objs/%.o:		$(SRCS_DIR)/%.c $(HDRS)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) -include $(HDRS) $(CFLAGS) $(READLINE_INC_DIR_FLAG) -c $< -o $@

libs:
				@echo "Making libft"
				@$(MAKE) -s -C $(LIBFT_DIR)

clean:
				@echo "Deleting object files"
				@$(RM) -r objs
				@echo	"Cleaning libs"
				@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean:			clean
				@$(RM) $(NAME)
				@echo	"Force cleaning libs"
				@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: 			fclean all

.PHONY:			all clean fclean re libs
