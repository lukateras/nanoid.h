#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <sys/random.h>
#endif
#include "nanoid.h"

#ifndef GETENTROPY_MAX
#define GETENTROPY_MAX 256
#endif

int main(int argc, char *argv[]) {
  char id[GETENTROPY_MAX + 1] = "";
  size_t len = NANOID_LEN;
  errno = 0;

  if (argc > 2)
    errx(EXIT_FAILURE, "Too many arguments: %u; maximum: 1", argc - 1);

  if (argc == 2) {
    len = strtoul(argv[1], NULL, 10);

    if (errno)
      errx(EXIT_FAILURE, "Invalid length: %s", argv[1]);

    if (len > GETENTROPY_MAX)
      errx(EXIT_FAILURE, "Length too large: %zu; maximum: %u", len, GETENTROPY_MAX);
  }

  if (nanoid(id, len))
    err(EXIT_FAILURE, "nanoid");

  if (puts(id) == EOF)
    err(EXIT_FAILURE, NULL);
}
