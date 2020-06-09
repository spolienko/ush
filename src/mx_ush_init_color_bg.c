#include "ush.h"

static char** init_bg_color_reg() {
	char** bg_color_reg = malloc(9 * sizeof(char *));
	bg_color_reg[0] = "black";
	bg_color_reg[1] = "red";
	bg_color_reg[2] = "green";
	bg_color_reg[3] = "yellow";
	bg_color_reg[4] = "blue";
	bg_color_reg[5] = "purple";
	bg_color_reg[6] = "cyan";
	bg_color_reg[7] = "white";
	bg_color_reg[8] = NULL;
	return bg_color_reg;
}

static char** init_bg_color_reg_high() {
	char** bg_color_high = malloc(9 * sizeof(char *));
	bg_color_high[0] = "high_black";
	bg_color_high[1] = "high_red";
	bg_color_high[2] = "high_green";
	bg_color_high[3] = "high_yellow";
	bg_color_high[4] = "high_blue";
	bg_color_high[5] = "high_purple";
	bg_color_high[6] = "high_cyan";
	bg_color_high[7] = "high_white";
	bg_color_high[8] = NULL;
	return bg_color_high;
}

static char** init_bg_color_bold() {
	char** bg_color_bold = malloc(9 * sizeof(char *));
	bg_color_bold[0] = "bold_black";
	bg_color_bold[1] = "bold_red";
	bg_color_bold[2] = "bold_green";
	bg_color_bold[3] = "bold_yellow";
	bg_color_bold[4] = "bold_blue";
	bg_color_bold[5] = "bold_purple";
	bg_color_bold[6] = "bold_cyan";
	bg_color_bold[7] = "bold_white";
	bg_color_bold[8] = NULL;
	return bg_color_bold;
}

static char** init_bg_color_high_inten() {
	char** bg_color_inten = malloc(9 * sizeof(char *));
	bg_color_inten[0] = "intensive_black";
	bg_color_inten[1] = "intensive_red";
	bg_color_inten[2] = "intensive_green";
	bg_color_inten[3] = "intensive_yellow";
	bg_color_inten[4] = "intensive_blue";
	bg_color_inten[5] = "intensive_purple";
	bg_color_inten[6] = "intensive_cyan";
	bg_color_inten[7] = "intensive_white";
	bg_color_inten[8] = NULL;
	return bg_color_inten;
}


void mx_init_color_bg(t_shell *shell) {
	shell->bg_color_reg = init_bg_color_reg();
	shell->bg_color_high = init_bg_color_reg_high();
    shell->bg_color_bold = init_bg_color_bold();
    shell->bg_color_inten = init_bg_color_high_inten();
}
