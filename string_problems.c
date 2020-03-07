#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int _strlen(char *str)
{
    int len;
    for (len = 0; str[len] != 0; len++);
    return len;
}

void reverse_string(char *str)
{
    int len = _strlen(str);
    for (int i=0; i < len / 2; i++) {
        char c = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = c;
    }
}

int is_palindrome(char * str)
{
    int len = _strlen(str);
    for (int i=0; i < len / 2; i++) {
        if (str[i] != str[len - 1 -i])
            return 0;
    }
    return 1;
}

void test_reverse_string()
{
    char *str = malloc(5 * sizeof(char));
    strcpy(str, "12345");
    reverse_string(str);
    printf("Reversed 12345: %s\n", str);
}

void test_palindrome()
{
    char *test_strs[] = {"hello", "abba", "1357531"};
    for (int i = 0; i < 3; i++) {
        printf("Is %s palindrome: %s\n",
               test_strs[i],
               is_palindrome(test_strs[i]) ? "true" : "false");
    }
}


char* find_longest_substring(char *s1, char *s2)
{
    int len1 = _strlen(s1);
    int len2 = _strlen(s2);
    int longest_start = 0;
    int longest_length = 0;

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            int count = 0;
            while (i + count < len1 && j + count < len2) {
                if (s1[i + count] == s2[j + count])
                    count++;
                else
                    break;
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

struct lcs_count
{
  int count;
  int start;
};

struct lcs_count recur_longest_substring(
    struct lcs_count count,
    char *left_str,
    char *right_str,
    int i,
    int j)
{
    if (i < 0 || j < 0)
        return count;
    if (left_str[i] == right_str[j]) {
        count.count++;
        count.start = i;
        count = recur_longest_substring(count, left_str, right_str, i - 1, j - 1);
    }
    struct lcs_count zero_count = { .count = 0, .start = 0};
    struct lcs_count count_left =
        recur_longest_substring(zero_count, left_str,  right_str, i - 1, j);
    struct lcs_count count_right =
        recur_longest_substring(zero_count, left_str,  right_str, i, j - 1);
    struct lcs_count new_count = (count_left.count > count_right.count)
                                     ? count_left
                                     : count_right;
    count = (new_count.count > count.count) ? new_count : count;
    return count;
}

char* find_longest_substring_dp_rec(char *s1, char *s2)
{
  /* A bad implementation, since it doesn't memoize previous calculations */
    int len1 = _strlen(s1);
    int len2 = _strlen(s2);
    struct lcs_count c = { .count = 0, .start = 0};
    struct lcs_count count = recur_longest_substring(c, s1, s2, len1 - 1, len2 - 1);
    if (count.count == 0)
        return NULL;
    char *longest_substring = malloc((count.count + 1) * sizeof(char));
    memcpy(longest_substring, s1 + count.start, count.count);
    longest_substring[count.count] = '\0';
    return longest_substring;
}

char* find_longest_substring_dp(char *left_str, char *right_str)
{
    int len1 = _strlen(left_str);
    int len2 = _strlen(right_str);
    struct lcs_count* counts = malloc((len1 + 1) * (len2 + 1) * sizeof(struct lcs_count));
    const struct lcs_count zero_count = { .count = 0, .start = 0};
    struct lcs_count max_count = zero_count;
    for (int i=0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            struct lcs_count *new_count = counts + i * len1 + j;
            if (i == 0 || j == 0) {
                *new_count = zero_count;
            } else if (left_str[i - 1] == right_str[j - 1]) {
                struct lcs_count *prev_count = counts + (i - 1) * len1 + j - 1;
                *new_count = *prev_count;
                new_count->count++;
                if (prev_count->count == 0)
                    new_count->start = i - 1;
                if (new_count->count > max_count.count)
                    max_count = *new_count;
          } else {
            *new_count = zero_count;
          }
        }
    }
    free(counts);
    char *longest_substring = malloc((max_count.count + 1) * sizeof(char));
    memcpy(longest_substring, left_str + max_count.start, max_count.count);
    longest_substring[max_count.count] = '\0';
    return longest_substring;
}

void test_longest_substring()
{
    printf("Finding longest substring...\n");
    char* longest = find_longest_substring_dp("geekforgeeks", "squadgeeksteam");
    printf("Done!\n");
    printf("%s\n", longest);
}

int str_to_int(char *str)
{
    int len = _strlen(str);
    int result = 0;
    int signal = 1;
    int dec = 1;
    int start = 0;
    if (len == 0)
        return 0;
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

void test_string_to_int()
{
    printf("%d\n", str_to_int("12345"));
    printf("%d\n", str_to_int("-12345"));
}

char* int_to_str(int value)
{
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
    } while (remainder > 0);
    result[pos] = '\0';
    return result;
}

void test_int_to_str()
{
  printf("%s\n", int_to_str(123456));
  printf("%s\n", int_to_str(-123456));
}

int is_anagram(char *s1, char *s2)
{
    int len1 = _strlen(s1);
    int len2 = _strlen(s2);
    if (len1 != len2)
         return 0;
    char* used = malloc(len1 * sizeof(char));
    memset(used, 0, len1);
    for (int i=0; i < len1; i++) {
        int found = 0;
        for (int j=0; j < len1; j++) {
            if (used[j])
                continue;
            if (s1[i] == s1[j]) {
                found = 1;
            used[j] = 1;
        }
    }
    if (!found)
        return 0;
  }
  return 1;
}

void test_is_anagram()
{
    char* strs[][2] = {
        {"abcde", "cbdae"},
        {"hello", "good"},
        {"abcde", "abcd"},
        {"abc", "abcd"}};
    for (int i=0; i < 4; i++) {
        printf("Is \"%s\" an anagram of \"%s\"? %d\n",
               strs[i][0],
               strs[i][1],
               is_anagram(strs[i][0], strs[i][1]));
    }
}

int unique_chars(char *str)
{
    char used[256];
    memset(&used, 0, 256);
    int len = _strlen(str);
    for (int i=0; i < len; i++) {
        if (used[str[i]])
            return 0;
        used[str[i]] = 1;
    }
    return 1;
}

void test_unique_chars()
{
    char *strs[] = {"hello", "opium", "bola", "coisa", "cigano", "troco"};
    for (int i=0; i < 6; i++) {
        printf("Are \"%s\" chars unique? %d\n", strs[i], unique_chars(strs[i]));
    }
}

int is_rotation(char *s1, char *s2)
{
    int len1 = _strlen(s1);
    int len2 = _strlen(s2);
    if (len1 != len2)
        return 0;
    for (int offset=0; offset < len1; offset++) {
        int is_rotation = 1;
        for (int pos=0; pos < len1; pos++) {
            if (s1[pos] != s2[(pos + offset) % len1]) {
              is_rotation =0;
              break;
            }
        }
        if (is_rotation)
            return 1;
    }
    return 0;
}

void test_is_rotation()
{
    char* strs[][2] = {
        {"abcde", "eabcd"},
        {"hello", "good"},
        {"abcde", "abcde"},
        {"abc", "abcd"}};
    for (int i=0; i < 4; i++) {
        printf("Is \"%s\" a rotation of \"%s\"? %d\n",
               strs[i][0],
               strs[i][1],
               is_rotation(strs[i][0], strs[i][1]));
    }
}

int main(int argc, char **arv)
{
    test_longest_substring();
}
