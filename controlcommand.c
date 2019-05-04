#include "commandrunner.h"

enum states {NEUTRAL, WANT_THEN, THEN_BLOCK, ELSE_BLOCK};
enum result {SUCCESS, FAIL};

static enum states if_state;
static enum result if_result;
static void syntax_error(char *);

bool is_control_command(char *s) {
	return
		strcmp(s, "if")   == 0 ||
		strcmp(s, "then") == 0 ||
		strcmp(s, "elif") == 0 ||
		strcmp(s, "else") == 0 ||
		strcmp(s, "fi")   == 0;
}

int do_control_command(char **cmdlist) {
	char *cmd = cmdlist[0];

	if (strcmp(cmd, "if") == 0) {
		if (if_state == NEUTRAL) {
			if_result = run_command(cmdlist + 1) == 0 ? SUCCESS : FAIL;
			if_state = WANT_THEN;
		} else {
			syntax_error("if unexpected");
			return -1;
		}
	} else if (strcmp(cmd, "elif") == 0) {
		if (if_state == THEN_BLOCK) {
			if (if_result != SUCCESS) {
				if_result = run_command(cmdlist + 1) == 0 ? SUCCESS : FAIL;
				if_state = WANT_THEN;
			}
		} else {
			syntax_error("elif unexpected");
			return -1;
		}
	} else if (strcmp(cmd, "else") == 0) {
		if (if_state == THEN_BLOCK) {
			if (if_result != SUCCESS) {
				if_result = SUCCESS;
				if_state = ELSE_BLOCK;
			}
		} else {
			syntax_error("else unexpected");
			return -1;
		}
	} else if (strcmp(cmd, "then") == 0) {
		if (if_state == WANT_THEN) {
			if_state = THEN_BLOCK;
		} else {
			syntax_error("then unexpected");
			return -1;
		}
	} else if (strcmp(cmd, "fi") == 0) {
		if (if_state == THEN_BLOCK || if_state == ELSE_BLOCK) {
			if_state = NEUTRAL;
		} else {
			syntax_error("fi unexpected");
			return -1;
		}
	} else {
		fatal(cmd, 2);
	}
	return 0;
}

bool is_executable_command() {
	if (if_state == WANT_THEN) {
		syntax_error("then expected");
		return false;
	} else if  (if_state == THEN_BLOCK && if_result == FAIL) {
		return false;
	} else {
		return true;
	}
}

static void syntax_error(char *msg) {
	if_state = NEUTRAL;
	fprintf(stderr, "syntax error: %s\n", msg);
}
