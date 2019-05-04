#include <ctype.h>
#include "commandrunner.h"

static int assign(char *str);
static bool is_valid_name(char *name);

bool is_builtin_command(char **cmdlist) {
	return
	strcmp(cmdlist[0], "set") == 0  ||
	strchr(cmdlist[0], '=') != NULL ||
	strcmp(cmdlist[0], "export") == 0;
}

int do_builtin_command(char **cmdlist) {

	if (strcmp(cmdlist[0], "set") == 0) {
		show_variable_table();
	} else if (strcmp(cmdlist[0], "export") == 0 && strchr(cmdlist[1], '=') != NULL) {
		char *cp = strchr(cmdlist[1], '=');
		*cp = '\0';
		if (cmdlist[1] != NULL && is_valid_name(cmdlist[1])) {
			if (!export_var(cmdlist[1])) {
				*cp = '=';
				return assign(cmdlist[1]);
			}
		}
	} else if (strcmp(cmdlist[0], "export") == 0) {
		if (cmdlist[1] != NULL && is_valid_name(cmdlist[1])) {
			return export_var(cmdlist[1]);
		}
	} else if (strchr(cmdlist[0], '=') != NULL) {
		return assign(cmdlist[0]);
	}
	return -1;
}

static int assign(char *str) {
	char *cp;
	cp = strchr(str, '=');
	*cp = '\0';
	if (!is_valid_name(str)) {
		return -1;
	}
	return set_var(str, cp+1);
}

static bool is_valid_name(char *name) {
	if (isdigit(name[0])) {
			return false;
	}
	int i;
	for (i = 0; i < strlen(name); i++) {
		if (!(name[i] == '_' || isalnum(name[i]))) {
			return false;
		}
	}
	return true;
}
