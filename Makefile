NAME = Gomoku2/Extern.dll

SRC = Extern.cpp Rules.class.cpp GameManager.class.cpp \
		PossibleMove.class.cpp Heuristic.class.cpp MinMax.cpp \
		TranspositionTable.class.cpp

OBJ = $(addprefix $(O_DIR)/,$(SRC:.cpp=.o))

O_DIR = ./objs

S_DIR = ./srcs

CFLAGS = -std=c++11 -stdlib=libc++ -g -Wall -Wextra -Werror -O3 -ferror-limit=2 -I includes

CC = g++

RM = rm -rf

$(NAME): $(OBJ)
	@$(CC) -shared -o $(NAME) $(CFLAGS) $(OBJ)

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	@mkdir -p $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

test: 
	@g++ srcs/* $(CFLAGS) -I includes

clean:
	@$(RM) $(OBJ)
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re