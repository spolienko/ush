int mx_strlen(const char *s) {
	int length = 0;
	int i = 0;

	while(s[i++]) {
		length++;
	}
	return length;
}
