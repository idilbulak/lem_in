NAME		:= lem_in
LIBDIR  	:= lib
INCDIR  	:= inc
SRCDIR  	:= src
OBJDIR  	:= obj
SRC     	:= $(shell find $(SRCDIR) -name '*.c')
OBJ     	:= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
HEAD    	:= $(wildcard inc/*.h)
LIB	    	:= lib/lib.a
CC      	:= gcc
# FLAGS   	:= -Wall -Wextra -Werror

all: $(NAME) 
$(NAME): $(LIB) $(OBJ)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(LIB) $(OBJ) -L./$(LIBDIR) -o $@
$(LIB):
	$(MAKE) -C $(LIBDIR)
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEAD)
	@mkdir -p $(@D)
	@$(CC) -g $(FLAGS) -c $< -o $@
# run: $(NAME)
# ./$(NAME) ...
clean:
	@rm -rf $(OBJDIR)
	#$(MAKE) -C ./$(LIB) clean
fclean: clean
	@rm -f $(NAME)
	$(MAKE) fclean -C $(LIBDIR)
re: fclean all
.PHONY: clean fclean re all