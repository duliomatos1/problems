#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int _strlen(char *str) {
  int len;
  for (len = 0; str[len] != 0; len++);
  return len;
}

void reverse_string(char *str) {
  int len = _strlen(str);
  for (int i=0; i < len / 2; i++) {
    char c = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = c;
  }
}

int is_palindrome(char* str) {
  int len = _strlen(str);
  for (int i=0; i < len / 2; i++) {
    if (str[i] != str[len - 1 -i]) return 0;
  }
  return 1;
}

void test_reverse_string() {
  char *str = malloc(5 * sizeof(char));
  strcpy(str, "12345");

  reverse_string(str);
  printf("Reversed 12345: %s\n", str);
}

void test_palindrome() {
  char *test_strs[] = {"hello", "abba", "1357531"};
  for (int i = 0; i < 3; i++) {
    printf(
      "Is %s palindrome: %s\n",
      test_strs[i],
      is_palindrome(test_strs[i]) ? "true" : "false"
    );
  }
}

void find_longest_substring(char *s1

void test_longest_substring(char* s1, char* s2) {
  char* longest = find_longest_substring("geekforgeeks", "squadgeekteam");
  printf("%s\n", longest);
}

int main(int argc, char **arv) {
}
