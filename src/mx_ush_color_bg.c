#include "ush.h"

static void regular_colors(t_shell *shell, char* str) {
	int index = mx_check_color(shell->bg_color_reg, str);
	if (index >= 0) {
		switch (index) {
			case 0 : shell->bg_c = "\033[40m"; break ; //black
    		case 1 : shell->bg_c = "\033[41m"; break ; // red
        	case 2 : shell->bg_c = "\033[42m"; break ; // green
        	case 3 : shell->bg_c = "\033[43m"; break ; // yellow
        	case 4 : shell->bg_c = "\033[44m"; break ; // blue
        	case 5 : shell->bg_c = "\033[45m"; break ; // purple
   			case 6 : shell->bg_c = "\033[46m"; break ; //cyan
    		case 7 : shell->bg_c = "\033[47m"; break ; // white
		}
	}
}

static void reg_high_colors(t_shell *shell, char* str) {
	int index = mx_check_color(shell->bg_color_high, str);
	if (index >= 0) {
		switch (index) {
			case 0 : shell->bg_c = "\033[0;90m"; break ; //black
    		case 1 : shell->bg_c = "\033[0;91m"; break ; // red
        	case 2 : shell->bg_c = "\033[0;92m"; break ; // green
        	case 3 : shell->bg_c = "\033[0;93m"; break ; // yellow
        	case 4 : shell->bg_c = "\033[0;94m"; break ; // blue
        	case 5 : shell->bg_c = "\033[0;95m"; break ; // purple
   			case 6 : shell->bg_c = "\033[0;96m"; break ; //cyan
    		case 7 : shell->bg_c = "\033[0;97m"; break ; // white
		}
	}
}

static void bold_colors(t_shell *shell, char* str) {
	int index = mx_check_color(shell->bg_color_bold, str);
	if (index >= 0) {
		switch (index) {
			case 0 : shell->bg_c = "\033[1;90m"; break ; //black
    		case 1 : shell->bg_c = "\033[1;91m"; break ; // red
        	case 2 : shell->bg_c = "\033[1;92m"; break ; // green
        	case 3 : shell->bg_c = "\033[1;93m"; break ; // yellow
        	case 4 : shell->bg_c = "\033[1;94m"; break ; // blue
        	case 5 : shell->bg_c = "\033[1;95m"; break ; // purple
   			case 6 : shell->bg_c = "\033[1;96m"; break ; //cyan
    		case 7 : shell->bg_c = "\033[1;97m"; break ; // white
		}
	}
}

static void high_intensive_colors(t_shell *shell, char* str) {
	int index = mx_check_color(shell->bg_color_inten, str);
	if (index >= 0) {
		switch (index) {
			case 0 : shell->bg_c = "\033[0;100m"; break ; //black
    		case 1 : shell->bg_c = "\033[0;101m"; break ; // red
        	case 2 : shell->bg_c = "\033[0;102m"; break ; // green
        	case 3 : shell->bg_c = "\033[0;103m"; break ; // yellow
        	case 4 : shell->bg_c = "\033[0;104m"; break ; // blue
        	case 5 : shell->bg_c = "\033[0;105m"; break ; // purple
   			case 6 : shell->bg_c = "\033[0;106m"; break ; //cyan
    		case 7 : shell->bg_c = "\033[0;107m"; break ; // white
		}
	}
}

static void color_work(char** args, t_shell *shell) {
	regular_colors(shell, args[1]);
	reg_high_colors(shell, args[1]);
	bold_colors(shell, args[1]);
	high_intensive_colors(shell, args[1]);
	printf("%s", shell->bg_c);
	shell->status = 0;
}


int mx_ush_color_bg(char** args, t_shell *shell) {
	if (args[1]) {
		if (strcmp(args[1], "help") == 0) {
			mx_help_color_bg(shell);
			return shell->status;
		}
		else if (mx_error_color_bg(shell, args, args[1]) == -1) {
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
