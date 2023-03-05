#include<stdio.h> 
#include<ctype.h> 
#include<dirent.h> 
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h> 
 
#define size 100 
#define len 1000 
 
int unique_words_count, sum_word_len = 2, sum_avg; 
float read_speed, write_speed, speak_speed, unique_percent; 
 
struct word_freq 
{ 
 char words[size]; 
 int count; 
 struct word_freq *next; 
}start, *p, *q, *temp, *t; 
 
void main() 
{ 
 FILE *fp, *f; 
 char file_name[size], search[size]; 
 int checking_number = 0, choose, i ,j, sentence_len = 0, sentence_avg_len, counter_num = 
0, file_number = 0; 
 printf("\n----------------------------------------------------\n"); 
 printf("FILE ANALYSIS"); 
 printf("\n----------------------------------------------------\n"); 
 a: 
 printf("\nAVAILABLE FILES IN THE OPENED DIRECTORY:\n\n"); 
 DIR *d; 
 struct dirent *dir; 
 d = opendir("."); 
 if (d) 
 { 
 while ((dir = readdir(d)) != NULL) 
 { 
 printf("%d. %s\n",++file_number, dir->d_name); 
 } 
 closedir(d); 
 } 
 printf("\n\nEnter the file name in which you need to perform file analysis:\t"); 
 scanf("%s",file_name); 
 fp = fopen(file_name, "r"); 
 if(fp == NULL) 
 { 
 printf("\nFILE NOT FOUND!!! TRY AGAIN!!!\n"); 
 checking_number++; 
 if (checking_number != 3) goto a; 
 else exit(1); 
 } 
 fclose(fp); 
 while(1) 
 { 
 printf("\nMENU:\n\n"); 
 printf("1. Statistics\n2. Print lines in the files\n3. 10 most frequent occuring words\n4. 10 
least frequent occuring words\n5. Search occurance for a substring
\n6. Miscellaneous\n7. Exit\n\n"); 
 printf("\nEnter your option here: "); 
 scanf("%d", &choose); 
 switch(choose) 
 { 
 case 1: 
 printf("\nSTATS:\n\n"); 
 int count_lines = 0, count_characters = 0, count_vowels = 0, count_consonants = 0;
 int count_numbers = 0, count_symbols = 0, count_upper = 0, count_lower = 0, 
count_words; 
 fp = fopen(file_name, "r"); 
 char ch, chh, word[size], sentence[len]; 
 while((ch = fgetc(fp)) != EOF) 
 { 
 count_characters++; 
 chh = tolower(ch); 
 if(isalpha(ch)) 
 { 
 if((chh == 'a')||(chh == 'e')||(chh == 'i')||(chh == 'o')||(chh == 'u')) 
 count_vowels++; 
 else 
 count_consonants++; 
 if(islower(ch)) 
 count_lower++; 
 if(isupper(ch)) 
 count_upper++; 
 } 
 else if(isdigit(ch)) 
 count_numbers++; 
 else 
 count_symbols++; 
 } 
 fclose(fp); 
 word_speed: 
 count_words = 0; 
 fp = fopen(file_name, "r"); 
 while((fscanf(fp, "%s", word)) != EOF) 
 count_words++; 
 fclose(fp); 
 if(choose == 6)goto word_speed_return; 
 fp = fopen(file_name, "r"); 
 while(fgets(sentence, len, fp) != NULL) 
 count_lines++; 
 fclose(fp); 
 printf("1. LINES: %d\n2. WORDS: %d\n3. CHARACTERS: %d\n4. VOWELS: 
%d\n",count_lines, count_words, count_characters, count_vowels); 
 printf("5. CONSONANTS: %d\n6. NUMBERS: %d\n7. SYMBOLS: %d\n8. UPPER CASE 
LETTERS: %d\n9. LOWER CASE LETTERS: %d\n10. ALPHABETS: %d\n", count_con
sonants, count_numbers, count_symbols, count_upper, count_lower, 
count_vowels+count_consonants); 
 sleep(1); 
 break; 
 
 case 2: 
 printf("\nTHE FIRST 10 lines are:\n\n"); 
 fp = fopen(file_name, "r"); 
 int count = 0, tt = 0, flag; 
 b: 
 flag = -1; 
 while(fgets(sentence, len, fp) != NULL) 
 { 
 count += 1; 
 printf("%d. %s\n",count, sentence); 
 if(count == tt+10) 
 { 
 flag = 1; 
 break; 
 } 
 } 
 if(flag == -1) 
 goto c; 
 printf("\nWant to proceed with remaining lines(y/n): "); 
 char choice; 
 scanf("%c", &choice); 
 scanf("%c", &choice); 
 printf("\n\n"); 
 sleep(2); 
 if(choice == 'y') 
 { 
 t += 10; 
 goto b; 
 } 
 c: 
 printf("\n------------------------------------------------------------------\n"); 
 fclose(fp); 
 break; 
 
 case 3: 
 token: 
 unique: 
 fp = fopen(file_name, "r"); 
 start.next = NULL; 
 p = &(start); 
 sum_word_len = 0; 
 unique_words_count = 0; 
 while(fscanf(fp, "%s", word)!= EOF) 
 { 
 if((isdigit(word[0]))||(isdigit(word[1]))) 
 continue; 
 for(i = 0; i < strlen(word); i++) 
 { 
 word[i] = tolower(word[i]); 
 } 
 if((word[0] == '(')||(word[strlen(word)-1] == ')')) 
 { 
 for(i = 0, j= 0; i < strlen(word); i++) 
 { 
 if((word[i] == '(')) 
 { 
 continue; 
 } 
 else if(word[i] == ')') 
 continue; 
 else if(word[i] == ',') 
 continue; 
 else 
 word[j++] = word[i]; 
 } 
 word[j] = '\0'; 
 } 
 int e = 0; 
 sum_word_len += strlen(word); 
 if(start.next!= NULL) 
 { 
 for(temp=start.next; temp->next != NULL; temp=temp->next) 
 { 
 if(strcmp(temp->words,word) == 0) 
 { 
 temp->count += 1; 
 e = 1; 
 break; 
 } 
 } 
 } 
 if(e==0) 
 { 
 q = (struct word_freq*) malloc (sizeof(struct word_freq)); 
 strcpy(q->words, word); 
 q->count = 1; 
 q->next = p->next; 
 p->next = q; 
 p = q; 
 unique_words_count++; 
 } 
 } 
 if(choose == 6) goto unique_return; 
 if(choose == 4) goto go_out; 
 for(temp = start.next; temp->next != NULL; temp = temp->next) 
 { 
 for(t = start.next; t->next->next != NULL; t = t->next) 
 { 
 if(t->count < (t->next)->count) 
 { 
 int te = t->count; 
 t->count = t->next->count; 
 t->next->count = te; 
 char *temp = (char *)malloc((strlen(t->words) + 1) * sizeof(char)); 
 strcpy(temp, t->words); 
 strcpy(t->words, t->next->words); 
 strcpy(t->next->words, temp); 
 free(temp); 
 } 
 } 
 } 
 int checker = 0; 
 sleep(1); 
 printf("\nThe 10 most frequent occuring words are as follows:\n\n"); 
 for(temp = start.next; temp->next != NULL; temp = temp->next) 
 { 
 checker += 1; 
 if(checker == 11) 
 break; 
 printf("%d. %s (%d times)\n", checker, temp->words, temp->count); 
 } 
 sleep(1); 
 break; 
 
 case 4: 
 goto token; 
 go_out: 
 printf("\nThe 10 least frequent occuring words are as follows:\n\n"); 
 for(temp = start.next; temp->next != NULL; temp = temp->next) 
 { 
 for(t = start.next; t->next->next != NULL; t = t->next) 
 { 
 if(t->count > (t->next)->count) 
 { 
 int te = t->count; 
 t->count = t->next->count; 
 t->next->count = te; 
 char *temp = (char *)malloc((strlen(t->words) + 1) * sizeof(char)); 
 strcpy(temp, t->words); 
 strcpy(t->words, t->next->words); 
 strcpy(t->next->words, temp); 
 free(temp); 
 }
 } 
 } 
 checker = 0; 
 for(temp = start.next; temp->next != NULL; temp = temp->next) 
 { 
 checker += 1; 
 if(checker == 11) 
 break; 
 printf("%d. %s (%d time(s))\n", checker, temp->words, temp->count); 
 } 
 fclose(fp); 
 sleep(1); 
 break; 
 
 case 5: 
 fp = fopen(file_name, "r"); 
 printf("\nEnter the substring which you need to search for in the file:\n"); 
 scanf("%s", &search); 
 int counting = 0; 
 while(fgets(sentence, len, fp) != NULL) 
 { 
 if(strstr(sentence, search) != NULL) 
 { 
 printf("\nOcuurance %d of substring '%s' found in the below line present 
in the file...\n", ++counting, search); 
 puts(sentence); 
 } 
 } 
 sleep(1); 
 printf("The substring '%s' occurs %d times\n", search, counting); 
 fclose(fp); 
 sleep(1); 
 break; 
 
 case 6: 
 goto word_speed; 
 word_speed_return: 
 goto unique; 
 unique_return: 
 read_speed = count_words/265.0; 
 speak_speed = count_words/115.0; 
 write_speed = count_words/31.0; 
 printf("\nWords: %d\n",count_words); 
 printf("\nReading time: %0.2f minutes", read_speed); 
 printf("\nWriting time: %0.2f minutes",write_speed); 
 printf("\nSpeaking time: %0.2f minutes", speak_speed); 
 unique_percent = ((unique_words_count)*100.0)/(count_words); 
 sum_avg = sum_word_len/count_words; 
 fp = fopen(file_name, "r"); 
 printf("\nThe number of unique words is: %d",unique_words_count); 
 printf("\nThe average word length is: %d",sum_avg); 
 printf("\nThe number of unique words used in the file is %0.2f\n",unique_percent); 
 sleep(1); 
 break; 
 case 7: 
 sleep(1); 
 exit(0); 
 break; 
 default: 
 printf("\nINVALID OPTION!! TRY AGAIN\n"); 
 break; 
 } 
 } 
}