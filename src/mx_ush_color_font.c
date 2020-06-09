#include "ush.h"

static void regular_colors(t_shell *shell, char* str) {
	int index = mx_check_color(shell->f_color_reg, str);
	if (index >= 0) {
		switch (index) {
			case 0 : shell->font_c = "\033[0;30m"; break ; //black
    		case 1 : shell->font_c = "\033[0;31m"; break ; // red
        	case 2 : shell->font_c = "\033[0;32m"; break ; // green
        	case 3 : shell->font_c = "\033[0;33m"; break ; // yellow
        	case 4 : shell->font_c = "\033[0;34m"; break ; // blue
        	case 5 : shell->font_c = "\033[0;35m"; break ; // purple
   			case 6 : shell->font_c = "\033[0;36m"; break ; //cyan
    		case 7 : shell->font_c = "\033[0;37m"; break ; // white
		}
	}
}

static void bold_colors(t_shell *shell, char* str) {
	int index = mx_check_color(shell->f_color_bold, str);
	if (index >= 0) {
		switch (index) {
			case 0 : shell->font_c = "\033[1;30m"; break ; //black
    		case 1 : shell->font_c = "\033[1;31m"; break ; // red
        	case 2 : shell->font_c = "\033[1;32m"; break ; // green
        	case 3 : shell->font_c = "\033[1;33m"; break ; // yellow
        	case 4 : shell->font_c = "\033[1;34m"; break ; // blue
        	case 5 : shell->font_c = "\033[1;35m"; break ; // purple
   			case 6 : shell->font_c = "\033[1;36m"; break ; //cyan
    		case 7 : shell->font_c = "\033[1;37m"; break ; // white
		}
	}
}

static void underline_colors(t_shell *shell, char* str) {
	int index = mx_check_color(shell->f_color_under, str);
	if (index >= 0) {
		switch (index) {
			case 0 : shell->font_c = "\033[4;30m"; break ; //black
    		case 1 : shell->font_c = "\033[4;31m"; break ; // red
        	case 2 : shell->font_c = "\033[4;32m"; break ; // green
        	case 3 : shell->font_c = "\033[4;33m"; break ; // yellow
        	case 4 : shell->font_c = "\033[4;34m"; break ; // blue
        	case 5 : shell->font_c = "\033[4;35m"; break ; // purple
   			case 6 : shell->font_c = "\033[4;36m"; break ; //cyan
    		case 7 : shell->font_c = "\033[4;37m"; break ; // white
		}
	}
}



static void color_work(char** args, t_shell *shell) {
	regular_colors(shell, args[1]);
	bold_colors(shell, args[1]);
	underline_colors(shell, args[1]);
	printf("%s", shell->font_c);
	shell->status = 0;
}

int mx_ush_color_font(char** args, t_shell *shell) {
	if (args[1]) {
		if (strcmp(args[1], "help") == 0) {
			mx_help_color_f(shell);
			return shell->status;
		}
		else if (mx_error_color_f(shell, args, args[1]) == -1) {
			shell->status = 1;
			return shell->status;
		}
		else {
			color_work(args, shell);
			return shell->status;
		}
	}
	else {
		mx_printerr("please enter color\n");
		shell->status = 1;
		return shell->status;
	}
	return shell->status;
}
