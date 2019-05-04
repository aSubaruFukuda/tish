#include "varlib.h"

struct var {
	char *str;
	bool is_global;
};

static struct var table[MAXVARS];
static struct var *get_var(char *name, int new_flg);
static char *generate_variable_string(char *name, char *val);

void initialize_variable_table(void) {
	int i = 0;
	while (i < MAXVARS) {
		table[i].str = NULL;
		table[i++].is_global = false;
	}
}

int load_environment(char *env[]) {
	char *env_str;
	int i;
	for (i = 0; env[i] != NULL; i++) {
		if (i == MAXVARS) {
			fprintf(stderr, "Exceed the table size this program have! You must adjust MAXVARS.");
			return -1;
		}
		env_str = malloc(1 + strlen(env[i]));
		if (env_str == NULL ) {
			fprintf(stderr, "memory allocate error.");
			return -1;
		}
		strcpy(env_str, env[i]);
		table[i].str = env_str;
		table[i].is_global = true;
	}
	return 0;
}

char **get_local_env_list(void) {
	int i,j, n = 0;
	for (i = 0; i < MAXVARS && table[i].str != NULL; i++) {
		if (table[i].is_global) {
			n++;
		}
	}
	char **envlist = (char **)malloc((n+1) * sizeof(char *));
	if (envlist == NULL) {
		return NULL;
	}
	for (i = 0,j = 0; i < MAXVARS && table[i].str != NULL; i++) {
		if (table[i].is_global) {
			envlist[j++] = table[i].str;
		}
	}
	envlist[j] = NULL;
	return envlist;
}

void show_variable_table(void) {
	int i;
	for (i = 0; i < MAXVARS && table[i].str != NULL; i++) {
		if(table[i].is_global) {
			printf(" * %s\n", table[i].str);
		} else {
			printf("   %s\n", table[i].str);
		}
	}
}

int set_var(char *name, char *val) {
	struct var *itemp;
	char *s;

	if ((itemp=get_var(name, 1)) != NULL && (s = generate_variable_string(name, val)) != NULL) {
		if (itemp->str){
			free(itemp->str);
		}
		itemp->str = s;
		return 0;
	}
	return -1;
}

int export_var(char *name) {
	struct var *itemp;
	if ((itemp = get_var(name, 0)) != NULL) {
		itemp->is_global = true;
		return 0;
	} else if (set_var(name, "") != -1) {
		return export_var(name);
	}
	return -1;
}

static struct var *get_var(char *name, int new_flg) {
	int i, len = strlen(name);
	for (i = 0; i < MAXVARS && table[i].str != NULL; i++) {
		if (!strncmp(table[i].str, name, len) && table[i].str[len] == '=') {
			return &table[i];
		}
	}
	if (new_flg && i < MAXVARS) {
		return &table[i];
	}
	return NULL;
}

static char *generate_variable_string(char *name, char *val) {
	char *val_str = malloc(strlen(name) + strlen(val) + 2);
	if (val_str != NULL) {
		sprintf(val_str, "%s=%s", name, val);
	}
	return val_str;
}

