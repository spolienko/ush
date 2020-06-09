#include "ush.h"

static char** init_font_color_reg() {
	char** f_color_reg = malloc(9 * sizeof(char *));
	f_color_reg[0] = "black";
	f_color_reg[1] = "red";
	f_color_reg[2] = "green";
	f_color_reg[3] = "yellow";
	f_color_reg[4] = "blue";
	f_color_reg[5] = "purple";
	f_color_reg[6] = "cyan";
	f_color_reg[7] = "white";
	f_color_reg[8] = NULL;
	return f_color_reg;
}

static char** init_font_color_bold() {
	char** f_color_bold = malloc(9 * sizeof(char *));
	f_color_bold[0] = "bold_black";
	f_color_bold[1] = "bold_red";
	f_color_bold[2] = "bold_green";
	f_color_bold[3] = "bold_yellow";
	f_color_bold[4] = "bold_blue";
	f_color_bold[5] = "bold_purple";
	f_color_bold[6] = "bold_cyan";
	f_color_bold[7] = "bold_white";
	f_color_bold[8] = NULL;
	return f_color_bold;
}

static char** init_font_color_underline() {
	char** f_color_under = malloc(9 * sizeof(char *));
	f_color_under[0] = "underline_black";
	f_color_under[1] = "underline_red";
	f_color_under[2] = "underline_green";
	f_color_under[3] = "underline_yellow";
	f_color_under[4] = "underline_blue";
	f_color_under[5] = "underline_purple";
	f_color_under[6] = "underline_cyan";
	f_color_under[7] = "underline_white";
	f_color_under[8] = NULL;
	return f_color_under;
}

void mx_init_color_font(t_shell *shell) {
	shell->f_color_reg = init_font_color_reg();
    shell->f_color_bold = init_font_color_bold();
    shell->f_color_under = init_font_color_underline();
}


