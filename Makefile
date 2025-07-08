NAME = philo

SRCDIR = src
OBJDIR = obj
INCDIR = include

SRC = philo.c \
		init.c \
		routines.c \
		monitor.c \
		utils.c \
		lib/garbage_collector.c \
		lib/ft_atoll.c \
		lib/ft_strlen.c \
		lib/is_int.c

OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

BUILD = $(OBJDIR)/.build

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)

VERBOSE ?= 0
ifeq ($(VERBOSE),1)
  V := 
else
  V := @
endif

RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"

all: $(NAME)

$(NAME): $(BUILD)

$(BUILD): $(LIBFT) $(OBJ)
	@clear
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) -o $(NAME)
	$(V)echo $(GREEN)"[$(NAME)] Philo is ready! 🚀"$(RESET)
	@touch $@

$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

DEP = $(OBJ:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning obj'$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Complete project cleanup'$(RESET)
	$(V)rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.DEFAULT_GOAL := all
