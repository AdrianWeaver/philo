NAME			=	philo

CC				=	cc
CFLAGS			=	-MMD -Wall -Wextra -Werror -pthread
INC				=	-I ./includes

SRCS			=	main.c\
					philo_utils.c\
					philo_utils2.c

OBJS			=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
DEPS			=	$(OBJS:.o=.d)

OBJS_PATH		=	./objects/
SRCS_PATH		=	./sources/

all: $(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
					@rm -rf $(OBJS_PATH)

fclean:				clean
					@rm -rf $(NAME)

re:					fclean
					@make $(NAME)

test:				$(NAME)
					./$(NAME) "2" "2" "3" "4" "5"

.PHONY:	clean fclean re test
