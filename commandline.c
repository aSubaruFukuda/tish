#include "commandline.h"

static int count_character(char *str);

char *get_command_line(char *prompt, FILE *fp) {
	char *buf;
	if ((buf = malloc(BUFSIZ)) == NULL) {
		fatal("memory allocate fail", 1);
	}

	int buf_length = 0;
	int available_space = 0;
	buf_length = available_space = BUFSIZ;

	printf("%s", prompt);
	int c;
	int pos = 0;
	while ((c = getc(fp)) != EOF) {
		if (available_space < 2) {
			if ((buf = realloc(buf, buf_length + BUFSIZ)) == NULL) {
				fatal("memory allocate fail", 1);
			}
			buf_length += BUFSIZ;
			available_space += BUFSIZ;
		}
		if (c == '\n') {
			break;
		}
		buf[pos++] = c;
		available_space--;
	}
	if (c == EOF && pos == 0) {
		return NULL;
	}
	buf[pos] = '\0';
	return buf;
}

char **get_command_list(char *command_line) {
	if (command_line == NULL) {
		return NULL;
	}
	int numspace = count_character(command_line);
	char **command_list = (char **)calloc(sizeof(char *), numspace + 2);
	if (command_list == NULL) {
		fatal("memory allocate fail", 1);
	}
	char *token;
	int i = 0;
	command_list[i++] = strtok(command_line, " ");
	while (true) {
		token = strtok(NULL, " ");
		command_list[i++] = token;
		if (token == NULL) {
			break;
		}
	}
	return command_list;
}

static int count_character(char *str) {
	int i, counter = 0;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') {
			counter++;
		}
	}
	return counter;
}
