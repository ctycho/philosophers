
NAME	:=	philo_one

#flags------------------------------------------------------------------------

CC		:=	gcc
FLAG	:=	-Wall -Wextra -Werror
RM		:=	rm -rf

#files------------------------------------------------------------------------

INC		:=	philo_one.h
SRCS	:=	main.c utils.c start.c

#colors----------------------------------------------------------------------

CYAN	:=	\033[0;36m
LGREEN	:=	\033[1;32m
LBLUE	:=	\033[1;34m	

#rules------------------------------------------------------------------------

all:		$(NAME)
	
${NAME}: $(SRCS) $(INC)
	@$(CC) -o $(NAME) $(SRCS) $(FALG)
	@echo "${CYAN}Library "${NAME}" succesfully compiled"

fclean:
	@rm -f ${NAME}
	@echo "${LGREEN}Everything is cleaned succesfully"

re:			fclean all
	@echo "${LBLUE}Library successfuly rebuilt"
