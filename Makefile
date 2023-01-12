NAME		=	pipex
LIBFT		=	libft.a
LIBFT_DIR	=	Libft
GCC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
SAN			=	-fsanitize=address -g
FILES		=	main process utils
BONUS_FILES	=	main process utils here_doc
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/
BONUS_DIR	=	bonus_srcs/
BOJS_DIR	=	bonus_objs/
SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
BONUS_SRCS	=	$(addprefix $(BONUS_DIR), $(addsuffix .c, $(BONUS_FILES)))
BONUS_OBJS	=	$(addprefix $(BOJS_DIR), $(addsuffix .o, $(BONUS_FILES)))
RM			=	rm -rf
RED			:= $(shell tput -Txterm setaf 1)
RESET		:= $(shell tput -Txterm sgr0)

all:
	@mkdir -p $(OBJS_DIR)
	@make $(LIBFT)
	@make $(NAME)
	@echo "$(RED)PIPEX is ready hehe..."

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(GCC) -c $< -o $@

$(NAME): $(OBJS)
	@$(GCC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

bonus:
	@mkdir -p $(BOJS_DIR)
	@make $(LIBFT)
	@make bname
	@echo "$(RED)PIPEX (bonus) is ready hehe..."

$(BOJS_DIR)%.o: $(BONUS_DIR)%.c
	@$(GCC) -c $< -o $@

bname: $(BONUS_OBJS)
	@$(GCC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT_DIR)/$(LIBFT) $(SAN) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS_DIR)

fclean:
	@make clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleted everything hehe..."

cleanb:
	@$(RM) $(BOBJS_DIR)

fcleanb:
	@make clean
	@$(RM) $(NAME)
	@$(RM) $(BOJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleted everything hehe..."

re:
	@make fclean
	@make all

norm:
	@norminette -R CheckForbidenSourceHeader $(SRCS)
	@norminette -R CheckForbidenSourceHeader $(BONUS_SRCS)