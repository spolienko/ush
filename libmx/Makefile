NAME	=	libmx.a

CFLG	=	-std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= 	clang

SRCD	=	src
INCD	=	inc
OBJD	=	obj

INC		=	libmx.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC	= 	    mx_printchar.c mx_strlen.c mx_printstr.c mx_printerr.c \
		    mx_print_strarr.c  mx_printint.c mx_pow.c mx_hex_to_nbr.c \
		    mx_itoa.c mx_atoi.c mx_foreach.c mx_binary_search.c \
		    mx_strcmp.c mx_bubble_sort.c mx_swap_char.c \
		    mx_str_reverse.c mx_strdel.c mx_del_strarr.c \
		    mx_get_char_index.c mx_strdup.c mx_strndup.c \
		    mx_strcpy.c mx_strncpy.c mx_strcmp.c mx_strncmp.c mx_strcat.c \
		    mx_strstr.c mx_get_substr_index.c mx_count_substr.c \
		    mx_count_words.c mx_strnew.c mx_isspace.c \
		    mx_strtrim.c mx_strsplit.c mx_strjoin.c mx_file_to_str.c \
		    mx_memset.c mx_memcpy.c mx_memccpy.c mx_memcmp.c mx_memchr.c \
		    mx_memrchr.c mx_memmem.c mx_memmove.c mx_isalpha.c mx_isdigit.c \
		    mx_islower.c mx_isupper.c mx_create_node.c mx_push_front.c \
		    mx_push_back.c mx_pop_front.c mx_pop_back.c mx_list_size.c \
			mx_sort_list.c mx_nbr_to_hex.c 

SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install clean
	
install: $(NAME)

$(NAME): $(OBJS)
	@libtool $^ -o libmx.a

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(COMP) $(CFLG) -c $< -o $@ -I$(INCD)

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJD)

uninstall: clean
	@rm -rf $(NAME)

reinstall: uninstall install

start: 
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic main.c libmx.a && ./a.out
