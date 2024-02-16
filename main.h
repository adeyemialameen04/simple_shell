#ifndef _MAIN_H_
#define _MAIN_H_

void tokenize_command(char *cmd, int *argc, char ***argv);
int exec_command(char **argv);
void free_argv(int argc, char ***argv);

#endif /* #ifndef _MAIN_H_ */
