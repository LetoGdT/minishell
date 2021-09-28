NAME		:=	minishell
SRCS_DIR	:=	srcs
SRCS_FILES	:=	minishell.c \
				env.c \
				env_2.c\
				clear.c \
				parsing/parsing.c \
				parsing/var_env.c \
				parsing/states/is_special_state.c \
				parsing/utils/is_separator.c \
				parsing/utils/is_bracket_quote.c \
				parsing/errors/error_multi_line.c \
				init/init.c \
				init/init_struct_cmd.c\
				builtins/export.c
SRCS		:=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))

HDRS_DIR	:=	includes
HDRS_FILES	:=	minishell.h
HDRS		:=	$(addprefix $(HDRS_DIR)/,$(HDRS_FILES))

OBJS		:=	$(SRCS:srcs/%.c=objs/%.o)

LIBFT_DIR	:= libft
LIBS		:= $(LIBFT_DIR)/libft.a

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -Iincludes -g
SANFLAGS	:=	-fsanitize=address -g3
LDFLAGS		:= -lreadline
RM			:=	rm -f

all:			$(NAME)

$(NAME):		libs $(OBJS)
				@echo "Linking $(NAME)"
#				@$(CC) $(SANFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
				@$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

objs/%.o:		$(SRCS_DIR)/%.c $(HDRS)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) -include $(HDRS) $(CFLAGS) -c $< -o $@
#				@$(CC) $(SANFLAGS) -include $(HDRS) $(CFLAGS) -c $< -o $@

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
