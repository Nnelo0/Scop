NAME = scop

C++ = c++
CC = cc

C++FLAGS = -g -std=c++17
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -Iincludes

OBJDIR = obj

SRCS = srcs/main.cpp
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
OBJS := $(OBJS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/srcs

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(C++) $(C++FLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(C++) $(C++FLAGS) $(OBJS) -lglfw -ldl -lGL -lGLU -lGLEW -lm -o $(NAME)
	@echo "\033[32m✔ Compilation completed\033[0m"

clean:
	$(RM) -r $(OBJDIR)
	@echo "\033[33m✔ $(OBJDIR) suppressed\033[0m"

fclean: clean
	$(RM) $(NAME)
	@echo "\033[31m✔ $(NAME) suppressed\033[0m"

re: fclean all
