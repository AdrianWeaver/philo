NAME			=	philo
SANITIZE_NAME	=	philo_sanitize

CC				=	cc
CFLAGS			=	-MMD -Wall -Wextra -Werror -pthread -g3
INC				=	-I ./includes

SRCS			=	main.c\
					philo_utils.c\
					list_utils.c\
					list_utils2.c\
					list_init.c\
					time_functions.c\
					threads_functions.c\
					philo_utils2.c

OBJS			=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
DEPS			=	$(OBJS:.o=.d)

OBJS_PATH		=	./objects/
SRCS_PATH		=	./sources/

all: $(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -o $@

$(SANITIZE_NAME):				$(OBJS)
					$(CC) -fsanitize=thread $(CFLAGS) $(OBJS) -o $@

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

vtest:				$(NAME)
					valgrind ./$(NAME) "2" "2" "3" "4" "5"

sanitize:			$(SANITIZE_NAME)
					./$(NAME) "2" "2" "3" "4" "5"

-include $(DEPS)
.PHONY:	clean fclean re test sanity sanitize