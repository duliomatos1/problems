#!/usr/bin/env python3
import re
from collections import Counter
if __name__ == '__main__':
    with open("/home/duliomatos/Charles_Dickens_-_A_Tale_of_Two_Cities.txt", "r") as f:
        contents = f.read()
    words = [w for w in re.split('[^a-zA-Z]', contents) if len(w) > 3]
    for word, count in Counter(words).most_common(25):
        print(f"{word}  {count}")
