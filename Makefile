NAME       := philo

CC         := cc

CPPFLAGS   := -I./includes

CFLAGS     := -Wall -Wextra -Werror

SRCS       := main.c monitor.c philo.c log.c utils.c

OBJDIR     := object
OBJS       := $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c philo.h | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
