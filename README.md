# CHangman
Simply console hangman written in C

words.txt in cmake-build-debug catalog contains all words that can be draw.
If you want to add more words you need to edit line 103
```
int target_line = rand() % 100 + 1;
```

where 100 is current numbers of rows in words.txt.
