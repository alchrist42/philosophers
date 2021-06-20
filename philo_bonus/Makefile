NAME_B		=	philo_bonus

SRCS_FILES	= 	philo_main.c \
				philo_fork.c \
				inicialise.c \
				ft_atoi_long.c \
				out_msg.c \
				utils.c


SRCS_FOLDER	=	srcs/

SRCS_B		= 	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
OBJS_B		=	$(patsubst %.c,%.o,$(SRCS_B))

INCLUDE		=	-I./include

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -MMD
RM			=	rm -f


all:		$(NAME_B)

bonus:		all

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
		

$(NAME_B):	$(OBJS_B)
			$(CC) $(INCLUDE) $(LIB) -o $(NAME_B) $(OBJS_B)

clean:
			$(RM) $(OBJS_B) $(OBJS_B:.o=.d)

fclean:		clean
			$(RM) $(NAME_B)

re:			fclean all

.PHONY:		all clean fclean re bonus
-include	$(OBJS_B:.o=.d)
