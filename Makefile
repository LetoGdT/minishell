NAME		:=	minishell
SRCS		:=	srcs/env.c

HDRS		:=	includes/minishell.h

OBJS		:=	$(SRCS:srcs/%.c=objs/%.o)

LIBFT_DIR	:= libft
LIBS		:= $(LIBFT_DIR)/libft.a

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -Iincludes -O3
LDFLAGS		:= -lreadline
RM			:=	rm -f

all:			libs $(NAME)

$(NAME):		$(OBJS)
				@echo "Linking $(NAME)"
				@$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

objs/%.o:		srcs/%.c $(HDRS)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) -include $(HDRS) $(CFLAGS) -c $< -o $@

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
