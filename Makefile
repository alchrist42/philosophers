NAME		=	philo
NAME_B		=	philo_bonus

SRCS_FILES	= 	philo.c \
				logging.c \
				inicialise.c \
				ft_atoi_long.c \
				utils.c

SRCS_B_FILES	= 	

SRCS_FOLDER	=	srcs/

SRCS		= 	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
SRCS_B		= 	$(addprefix $(SRCS_FOLDER),$(SRCS_B_FILES))
OBJS		=	$(patsubst %.c,%.o,$(SRCS))
OBJS_B		=	$(patsubst %.c,%.o,$(SRCS_B))

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

$(NAME_B):	$(OBJS_B)
			$(MAKE) -C $(dir $(LIB))
			$(CC) $(INCLUDE) $(LIB) -o $(NAME_B) $(OBJS_B)

clean:
			$(RM) $(OBJS) $(OBJS:.o=.d) $(OBJS_B) $(OBJS_B:.o=.d)

fclean:		clean
			$(RM) $(NAME) $(NAME_B)

re:			fclean all

.PHONY:		all clean fclean re bonus
-include	$(OBJS:.o=.d)
-include	$(OBJS_B:.o=.d)
