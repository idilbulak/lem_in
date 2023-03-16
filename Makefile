NAME		:= lem_in
INCDIR  	:= inc
SRCDIR  	:= src
OBJDIR  	:= obj
SRC     	:= $(shell find $(SRCDIR) -name '*.c')
OBJ     	:= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
HEAD    	:= $(wildcard inc/*.h)
CC      	:= gcc
FLAGS   	:= -Wall -Wextra -Werror

all: $(NAME) 
$(NAME): $(OBJ) $(ERR)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(OBJ) -o $@
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEAD)
	@mkdir -p $(@D)
	@$(CC) -g $(FLAGS) -c $< -o $@
# run: $(NAME)
# ./$(NAME) ...
clean:
	@rm -rf $(OBJDIR)
fclean: clean
	@rm -f $(NAME)
re: fclean all
.PHONY: clean fclean re all