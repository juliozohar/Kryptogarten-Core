/*
  Program: letter_count.c 
  Author: Julio Cesar Torres
  Date : April 14th 2016 

  Letter counting program. Use it to count the occurrence of individual letters in cryptograms, 
  to calculate the relative  frequency of each letter in a cipher. 

  No numbers , punctuation or symbols are counted. 

  No accents are taken in charge. If you have accentuated text, normalize it to a standard English 
  text before running the program. 

   example{
      text: "QWTPDRW AX FLR JWPI BWNWRTAUWR, ZPNLWA QWNLWHWV BFPBJFPB FW RPJ PEADSV RPBDES JWEW SAB ELSZR QDB PUUWSVPZWR NLIW BWPUAB FPSVNWR"
      text.length : 107 chars
   }

*/

#include <stdio.h>
#include <string.h>

#define SYMBOL_COUNT 26   
#define TEXT_MAX_SIZE    2048

int main()
{
   char string[TEXT_MAX_SIZE];
   int c = 0, char_count = 0, count[SYMBOL_COUNT] = {0};
 
   printf("Enter a string\n");
   gets(string);
 
   while (string[c] != '\0')
   {
      /** Considering characters from '[A-Za-z]' only. 
          Ignoring others */
 
      if (string[c] >= 'a' && string[c] <= 'z') {
         count[string[c]-'a']++;
         ++char_count;
      }
 
      if (string[c] >= 'A' && string[c] <= 'Z') {
         count[string[c]-'A']++;
         ++char_count; 
      }

      c++;
   }
 
   for (c = 0; c < SYMBOL_COUNT; c++)
   {
      /** Printing only those characters 
          whose count is at least 1 */
 
      if (count[c] != 0)
         printf("%c occurs %d times in the entered string. Frequency: %d \n",c+'a',count[c], (count[c]/char_count));

   }
   printf("Total char count: %d \n", char_count);
 
   return 0;
}