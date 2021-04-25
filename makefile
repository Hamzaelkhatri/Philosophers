NAME= philo_1
SRC_PATH=philo_one
HDR_PATH= includes
OBJ_PATH= obj
TOOLS_PATH= obj/tools

TOOLS= /tools/ft_atoi.c /tools/ft_itoa.c
SRC= philo.c init.c $(TOOLS)
HDR_NAME= philosophers.h

OBJ_NAME= $(SRC:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

H_FLAG= -I $(HDR_PATH)

COMP= gcc -pthread

FLAGS = #-Wall -Wextra -Werror

all: $(NAME) 

$(NAME) : $(OBJ)
	@$(COMP) -g $(H_FLAG) $(OBJ) -o $@
	@echo "						Compilation of $(NAME):  \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c 
	@mkdir -p $(OBJ_PATH) $(TOOLS_PATH)
	@$(COMP) -g $(FLAGS) $(H_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf $(OBJ_PATH) $(NAME) 
	@echo "\033[0;31m>> $(NAME) && all objects are deleted.\033[0m" 

re : fclean all