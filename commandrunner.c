#include "commandrunner.h"

static int execute_command(char **argv);

int run_command(char *cmdlist[]) {
	if (cmdlist[0] == NULL) {
	} else if (is_control_command(cmdlist[0])) {
		return do_control_command(cmdlist);
	} else if (is_executable_command()) {
		if (is_builtin_command(cmdlist)) {
			return do_builtin_command(cmdlist);
		} else {
			return execute_command(cmdlist);
		}
	}
	return -1;
}

static int execute_command(char **argv) {
	extern char **environ;
	int pid;
	int child_exit_status = -1;

	if (argv[0] == NULL) {
		return 0;
	}
	if ((pid = fork()) == -1) {
		perror("fork");
	} else if (pid == 0) {
		environ = get_local_env_list();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	} else {
		if (wait(&child_exit_status) == -1) {
			perror("wait");
		}
	}
	return child_exit_status;
}

