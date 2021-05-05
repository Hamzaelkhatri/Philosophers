
all: $(make)

make: 
	make philo_one
	
clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf $(OBJ_PATH) $(NAME) 
	@echo "\033[0;31m>> $(NAME) && all objects are deleted.\033[0m" 

re : fclean all