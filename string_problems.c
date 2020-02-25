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


char* find_longest_substring(char *s1, char *s2) {
  int len1 = _strlen(s1);
  int len2 = _strlen(s2);
  int longest_start = 0;
  int longest_length = 0;

  for (int i = 0; i < len1; i++) {
    for (int j = 0; j < len2; j++) {
      int count = 0;
      while (i + count < len1 && j + count < len2) {
        if (s1[i + count] == s2[j + count]) {
          count++;
        } else {
          break;
        }
      }
      if (count > longest_length) {
        longest_length = count;
        longest_start = i;
      }
    }
  }
  char *substring = malloc((longest_length + 1) * sizeof(char));
  memcpy(substring, s1 + longest_start, longest_length);
  return substring;
}

void test_longest_substring() {
  char* longest = find_longest_substring("geekforgeeks", "squadgeeksteam");
  printf("%s\n", longest);
}

int str_to_int(char *str) {
  int len = _strlen(str);
  int result = 0;
  int signal = 1;
  int dec = 1;
  int start = 0;
  if (len == 0) return 0;
  if (str[0] == '-') {
    signal = -1;
    start = 1;
  }
  for (int i = len - 1; i >= start; i--) {
    result += (str[i] - '0') * dec;
    dec *= 10;
  }
  return result * signal;
}

void test_string_to_int() {
  printf("%d\n", str_to_int("12345"));
  printf("%d\n", str_to_int("-12345"));
}

char* int_to_str(int value) {
  char *result = malloc(16 * sizeof(char));
  int pos = 0;
  if (value < 0) {
    result[pos++] = '-';
    value *= -1;
  }
  int remainder = value;
  do {
    int digit = remainder % 10;
    result[pos++] = '0' + digit;
    remainder /= 10;
  } while(remainder > 0);
  result[pos] = '\0';
  return result;
}

void test_int_to_str() {
  printf("%s\n", int_to_str(123456));
  printf("%s\n", int_to_str(-123456));
}

int main(int argc, char **arv) {
  test_int_to_str();
}
