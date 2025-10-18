NAME = scop

C++ = c++
CC = cc

C++FLAGS = -g -std=c++17
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I./includes

OBJDIR = obj

SRCS =	srcs/main.cpp srcs/Obj.cpp srcs/Shaders.cpp srcs/Vec3.cpp srcs/Matrix.cpp srcs/Texture.cpp \
		includes/imgui/imgui.cpp \
		includes/imgui/imgui_draw.cpp \
		includes/imgui/imgui_impl_glfw.cpp \
		includes/imgui/imgui_impl_opengl3.cpp \
		includes/imgui/imgui_tables.cpp \
		includes/imgui/imgui_widgets.cpp

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
OBJS := $(OBJS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/srcs
	@mkdir -p $(OBJDIR)/includes/imgui

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
	$(RM) imgui.ini
	@echo "\033[31m✔ $(NAME) suppressed\033[0m"

re: fclean all
