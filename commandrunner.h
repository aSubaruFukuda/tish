#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "varlib.h"
#include "util.h"

extern int  run_command(char *cmdlist[]);
extern int  builtin_command(char **args, int *resultp);
extern bool is_control_command(char *s);
extern int  do_control_command(char **args);
extern bool is_executable_command(void);
extern bool is_builtin_command(char **cmdlist);
extern int  do_builtin_command(char **cmdlist);

