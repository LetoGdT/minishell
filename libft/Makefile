NAME		:=	libft.a
SRCS		:=	printf/detecte_flags.c\
				printf/display.c\
				printf/format_vars.c\
				printf/ft_printf_utils.c\
				printf/ft_printf.c\
				printf/ft_printf_format.c\
				printf/misc.c

LIBS		:=	libft/libft.a
HDRS		:=	includes/libft.h\
					includes/ft_printf.h
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -Iincludes
OBJS		:=	$(SRCS:.c=.o)
RM			:=	rm -f

$(NAME):		$(OBJS) $(LIBS)
				cp $(LIBS) $(NAME)
				ar rcs $(NAME) $(OBJS)

$(OBJS): 		$(SRCS) $(HDRS)

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(LIBS):	
				$(MAKE) --directory=$(shell dirname $(LIBS))

all:			$(NAME)

clean:
				$(RM) $(OBJS)
				$(MAKE) -C$(shell dirname $(LIBS)) clean

fclean:			clean
				$(RM) $(NAME)
				$(MAKE) -C$(shell dirname $(LIBS)) fclean

re: 			fclean all

.PHONY:			all clean fclean re

