#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "varlib.h"
#include "commandline.h"
#include "commandrunner.h"

#define PROMPT "> "

static void setup();

int main() {
	setup();

	char *cmdline, **cmdlist;
	while ((cmdline = get_command_line(PROMPT, stdin)) != NULL) {
		if ((cmdlist = get_command_list(cmdline)) != NULL) {
			run_command(cmdlist);
			free(cmdlist);
		}
		free(cmdline);
	}
	return 0;
}

static void setup() {
	initialize_variable_table();
	extern char **environ;
	load_environment(environ);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

