#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argv[1] == NULL) {
    printf("rahe error: no action given");
  }

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
    return EXIT_FAILURE;
  }

  size_t comargs_len = 0;
  char *comargs = NULL;

  for (int i = 1; argv[i] != NULL; i++) {
    comargs_len += strlen(argv[i]) + 1; // +1 for the space
  }

  comargs = malloc(comargs_len + 1);
  if (!comargs) {
    fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  comargs[0] = '\0'; // initialize comargs to an empty string

  for (int i = 1; argv[i] != NULL; i++) {
    strcat(comargs, argv[i]);
    if (argv[i + 1] != NULL) {
      strcat(comargs, " ");
    }
  }

  char command[256]; // assuming the command won't exceed 256 characters
  snprintf(command, sizeof(command), "python -u \"./src/main.py\" %s", comargs);
  system(command);

  free(comargs);
  return EXIT_SUCCESS;
}