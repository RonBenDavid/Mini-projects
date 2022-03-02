1. Complete the body of the following function so that it reads a file named, filename, and returns the number of lines in the file.
  int countLines (char * filename)
  {
…
   }

For example, if the input file name is input.txt a possible run will be performed as follows:

    int numLines;
    numLines = countLines ("input.txt");
    printf ("The number of lines is% d", numLines);

2. Complete the body of the following function so that it reads a file named, filename, and counts the number of occurrences for each letter A to Z in the file.
void letterFrequency (char * filename, int counts [])
{
     …
}

Lowercase and uppercase letters in the text should be treated in the same way (so that both 'a' and 'A' will be considered as the letter 'A').
The number of occurrences of each letter should be placed in an array of counts so that an array of counts [0] will contain the number of occurrences of the letter 'A' in the file, ... and counts [25] will contain the number of occurrences of the letter 'Z'.

3. Complete the body of the following function so that it copies a file named, infile, to a new file named outfile while removing the spaces from the input file.
void removeSpaces (char * infile, char * outfile)
{
           …
      }

4. Write a program that creates the initial file and executes the above functions.