#include "ush.h"

 int mx_error_color_f(t_shell *shell, char** args, char* str) {
	int f_reg = mx_check_color(shell->f_color_reg, str);
	int f_bold = mx_check_color(shell->f_color_bold, str);
	int f_underline = mx_check_color(shell->f_color_under, str);

	if (f_reg == -1 && f_bold == -1 && f_underline == -1) {
		mx_printerr(args[1]);
		mx_printerr(" color not found\n");
		mx_printerr("please enter -color help- for color info\n");
		shell->status = 1;
		return shell->status;
	}
	if (args[2]) {
		shell->status = 1;
		mx_printerr("color: too many arguments\n");
		return shell->status;
	}
	return shell->status;
}

int mx_check_color(char** array, char* str) {
	int index = 0;
	int find = -1;

	for (; array[index] != NULL; index++) {
		if (strcmp(array[index], str) == 0) {
			find = 1;
			return index;
		}
	}
	return find;
}

void mx_help_color_f(t_shell *shell) {
	printf("Regular colors : ");
	for (int i = 0; shell->f_color_reg[i] != NULL; i++) {
		printf("%s, ", shell->f_color_reg[i]);	
	}
	printf("\n");
	printf("Bold colors : ");
	for (int i = 0; shell->f_color_bold[i] != NULL; i++) {
		printf("%s, ", shell->f_color_bold[i]);	
	}
	printf("\n");
	printf("Underline colors : ");
	for (int i = 0; shell->f_color_under[i] != NULL; i++) {
		printf("%s, ", shell->f_color_under[i]);	
	}
	printf("\n");
}

int mx_error_color_bg(t_shell *shell, char** args, char* str) {
	int bg_reg = mx_check_color(shell->bg_color_reg, str);
	int bg_bold = mx_check_color(shell->bg_color_bold, str);
	int bg_high = mx_check_color(shell->bg_color_high, str);
	int bg_inten = mx_check_color(shell->bg_color_inten, str);

	if (bg_reg == -1 && bg_bold == -1 && bg_high == -1 && bg_inten == -1) {
		mx_printerr(args[1]);
		mx_printerr(" color not found\n");
		mx_printerr("please enter -color help- for color info\n");
		shell->status = 1;
		return shell->status;
	}
	if (args[2]) {
		shell->status = 1;
		mx_printerr("color: too many arguments\n");
		return shell->status;
	}
	return shell->status;
}

void mx_help_color_bg(t_shell *shell) {
	printf("Regular colors : ");
	for (int i = 0; shell->bg_color_reg[i] != NULL; i++) {
		printf("%s, ", shell->bg_color_reg[i]);
	}
	printf("\n");
	printf("Regular intensive colors : ");
	for (int i = 0; shell->bg_color_high[i] != NULL; i++) {
		printf("%s, ", shell->bg_color_reg[i]);	
	}
	printf("\n");
	printf("Bold colors : ");
	for (int i = 0; shell->bg_color_bold[i] != NULL; i++) {
		printf("%s, ", shell->bg_color_reg[i]);	
	}
	printf("\n");
	printf("Underline colors : ");
	for (int i = 0; shell->bg_color_inten[i] != NULL; i++) {
		printf("%s, ", shell->bg_color_reg[i]);	
	}
	printf("\n");
}
