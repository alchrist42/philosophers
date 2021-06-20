NAME		=	philo

SRCS_FILES	= 	philo.c \
				logging.c \
				logging_utils.c \
				inicialise.c \
				ft_atoi_long.c \
				utils.c


SRCS_FOLDER	=	srcs/

SRCS		= 	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I./include

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -MMD
RM			=	rm -f


all:		$(NAME)

bonus:		$(NAME_B)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
		
$(NAME):	$(OBJS)
			$(CC) $(INCLUDE) -o $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
-include	$(OBJS:.o=.d)