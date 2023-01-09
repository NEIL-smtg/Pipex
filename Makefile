NAME		=	pipex
LIBFT		=	libft.a
LIBFT_DIR	=	Libft
GCC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
SAN			=	-fsanitize=address -g
FILES		=	main
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/
SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
RM			=	rm -rf
RED			:= $(shell tput -Txterm setaf 1)
RESET		:= $(shell tput -Txterm sgr0)

all:
	@mkdir -p $(OBJS_DIR)
	@make $(LIBFT)
	@make $(NAME)
	@echo "$(RED)PIPEX is ready hehe..."

bonus:
	mkdir -p $(OBJS_DIR)
	libft
	make $(NAME)
	@echo "$(RED)PIPEX (bonus) is ready hehe..."

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(GCC) -c $< -o $@

$(NAME): $(OBJS)
	@$(GCC) $(CFLAGS) $(SAN) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS_DIR)

fclean:
	@make clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleted everything hehe..."

re:
	@make fclean
	@make all

norm:
	@norminette -R CheckForbidenSourceHeader $(SRCS)
	@make norm -C $(LIBFT_DIR)