#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXVARS 200

extern void initialize_variable_table(void);
extern int  load_environment(char *env[]);
extern char **get_local_env_list(void);
extern void show_variable_table(void);
extern int  set_var(char *name, char *val);
extern int  export_var(char *name);
