NAME	=	ush

CFLG	=	-std=c11 $(addprefix -W, all extra error pedantic) -g

SRCD	=	src
INCD	=	inc
OBJD	=	obj

LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a
LMXI:=	$(LMXD)/$(INCD)

INC		=	ush.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC		=	  main.c \
		      mx_tree.c \
		      mx_tokcoma.c \
		      mx_forest.c \
		      mx_index_cmd.c \
		      mx_launch_cmd.c \
		      mx_launch_init.c \
		      mx_launchers.c \
		      mx_check_line.c \
		      mx_exp_param.c \
		      mx_cp_env.c \
		      mx_create_node_env.c \
		      mx_do_util.c \
		      mx_env.c \
		      mx_parse_env.c \
		      mx_ush_env.c \
		      mx_strarr_dup.c \
		      mx_strarr_join.c \
		      mx_exp_tilda.c \
		      mx_exp_join.c \
		      mx_init_shell.c \
		      mx_push_variable.c \
		      mx_ush_cd.c \
		      mx_output_path.c \
		      mx_ush_pwd.c \
		      mx_ush_which.c \
		      mx_substitutions.c \
		      mx_str_from_stdin.c \
		      mx_format_sub_result.c \
		      mx_exp_param2.c \
		      mx_ush_count_flags.c \
		      mx_ush_echo.c \
		      mx_print_error_flags.c \
		      mx_ush_export.c \
		      mx_envp_add.c \
		      mx_print_export.c \
		      mx_ush_unset.c \
		      mx_ush_exit.c \
		      mx_ush_false.c \
		      mx_ush_true.c \
		      mx_ush_return.c \
		      mx_ush_alias.c \
		      mx_modstrsplit.c \
		      mx_ush_flags_pwd.c \
		      mx_ush_flags_echo.c \
		      mx_ush_for_cd.c \
		      mx_ush_color_font.c \
		      mx_ush_color_func.c \
		      mx_ush_color_bg.c \
		      mx_ush_init_color_bg.c \
		      mx_ush_init_color_font.c \
		      mx_ush_signals.c \
		      mx_undo_shielding_v.c \
		      mx_check_err.c \
		      mx_get_bracket.c \
		      mx_bracket1.c \
		      mx_bracket2.c \
		      mx_bracket3.c \
		      mx_bracket4.c \
		      mx_bracket5.c \
		      mx_ecran.c \
		      mx_undo_ecran.c \
		      mx_find_filepath.c \
		      mx_check_builtin.c \
		      mx_check_alias.c \
		      mx_sub_replace.c \

SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: $(LMXD) $(NAME)

$(FILE:a/%=%)

$(NAME): $(LMXA) $(OBJS)
	@clang $(CFLG) $(OBJS) -L$(LMXD) -lmx -o $@
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD) -I$(LMXI)
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

$(LMXD): $(LMXA)

$(LMXA):
	@make -sC $(LMXD)

clean:
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@make -sC $(LMXD) $@
	@rm -rf $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all
