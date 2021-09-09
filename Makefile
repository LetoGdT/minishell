NAME		:=	minishell
SRCS		:=	

HDRS		:=	includes/minishell.h

OBJS		:=	$(SRCS:srcs/%.c=objs/%.o)

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -Iincludes -O3
RM			:=	rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo "Linking $(NAME)"
				@$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

objs/%.o:		srcs/%.c $(HDRS)
				@mkdir -p $(dir $@)
				@echo "Compiling $<"
				@$(CC) -include $(HDRS) $(CFLAGS) -c $< -o $@

clean:
				@echo "Deleting object files"
				@$(RM) -r objs

fclean:			clean
				@$(RM) $(NAME)

re: 			fclean all

.PHONY:			all clean fclean re libs
