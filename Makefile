NAME = Gomoku2/Extern.dll

SRC = Extern.cpp Rules.class.cpp GameManager.class.cpp

OBJ = $(addprefix $(O_DIR)/,$(SRC:.cpp=.o))

O_DIR = ./objs

S_DIR = ./srcs

CFLAGS = -I includes

CC = nvcc

RM = rm -rf

$(NAME): $(OBJ)
	$(CC) -shared -o $(NAME) $(CFLAGS) $(OBJ)

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	mkdir -p $(O_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re