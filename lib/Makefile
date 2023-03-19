NAME		:= lib.a
INCDIR  	:= inc
SRCDIR  	:= src
OBJDIR  	:= obj
SRC     	:= $(shell find $(SRCDIR) -name '*.c')
OBJ     	:= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
HEAD    	:= $(wildcard inc/*.h)
CC      	:= gcc
FLAGS   	:= -Wall -Wextra -Werror

all: $(NAME) 
$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEAD)
	@mkdir -p $(@D)
	@$(CC) -g $(FLAGS) -c $< -o $@
clean:
	@rm -rf $(OBJDIR)
fclean: clean
	@rm -f $(NAME)
re: fclean all
.PHONY: clean fclean re all