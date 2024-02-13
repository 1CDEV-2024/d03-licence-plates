#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void incr_numbers(char *buffer) {
  long n = strtol(buffer, NULL, 10);

  n += 1;
  buffer[2] = '0' + n % 10;
  buffer[1] = '0' + n % 100 / 10;
  buffer[0] = '0' + n % 1000 / 100;
}

static char contains_bad_char(char *buffer) {
  return buffer[0] == 'I' || buffer[1] == 'I' || buffer[0] == 'O' ||
         buffer[1] == 'O' || buffer[0] == 'U' || buffer[1] == 'U';
}

static void incr_letters(char *buffer) {
  buffer[1] += 1;
  if (buffer[1] == ('Z' + 1)) {
    buffer[1] = 'A';
    buffer[0] += 1;
  }
  if (contains_bad_char(buffer) || !strncmp(buffer, "SS", 2))
    incr_letters(buffer);
}

static char diff(char *str, char *cmp) {
  return !!strncmp(cmp, str, strlen(cmp));
}

static void set(char *dst, char *src) { memcpy(dst, src, strlen(src)); }

int main(void) {
  char buffer[] = "AA-001-AA";
  char *left = buffer, *middle = buffer + 3, *right = buffer + 7;

  for (set(left, "AA"); diff(left, "ZZ"); incr_letters(left)) {
    if (left[0] == 'W') {
      left[1] = 'Z';
      continue;
    }

    for (set(right, "AA"); diff(right, "ZZ"); incr_letters(right)) {
      for (set(middle, "001"); diff(middle, "000"); incr_numbers(middle))
        printf("%s\n", buffer);
    }
  }
}
