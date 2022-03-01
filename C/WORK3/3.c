/*
Assigned by:
Name:Ron ben david.
ID:#307906263.
Group number:60001,Dr.Mark Korenblit.
*/
# include <stdio.h>
# include <string.h>
char FindFirstVowel(char*);
void main()
{
	char sentence[200];
	char vowel;
	printf("Please enter a sentence\n");
	gets(sentence);
	vowel = FindFirstVowel(sentence);
	if (vowel == '\0')//If the function was not find any vowel letters
	{
		printf("There was no vowel in your sentence\n");
	}
	else //If the function found vowel letters
	{
		printf("The first vowel in the sentence is %c\n", vowel);
	}
}
char FindFirstVowel(char *Letter)
{
	int i = 0;
	while (Letter[i] != '\0')//Run all the letters in the sentence
	{
		if (Letter[i] == 'a' || Letter[i] == 'e' || Letter[i] == 'i' || Letter[i] == 'o' || Letter[i] == 'u' || Letter[i] == 'A' || Letter[i] == 'E' || Letter[i] == 'I' || Letter[i] == 'O' || Letter[i] == 'U')
			return Letter[i];
		i++;
	}
	return '\0';//When not found nothing
}