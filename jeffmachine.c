#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./jeffmachine yourFile.txt\n");
        return 1;
    }

    //open our input file...
    FILE *input = fopen(argv[1], "r");

        if (input == NULL)
        {
            printf("Could not open file... \n");
            return 1;
        }

//our design is very human, we let the user know the program is doing it's job...
printf("Jeff machine successfully opened %s \n", argv[1]);

//we create a filename for our output format...
char *fileName = malloc(sizeof(argv[1]) + (sizeof(char) * 5));
sprintf(fileName, "jeff_%s", argv[1]);

//and we tell the user that too, so they don't get anxious. 
printf("Creating file %s \n", fileName);

//since we're not a liar, we do, infact, create that file... 
FILE *output = fopen(fileName, "w");

//create our buffer array...
char buffer[sizeof(char) * 2];


//now we read the file in chunks of 2 (arbitrarily) and print those chunks to our output file...
while (fread(buffer, sizeof(char), 2, input) == 2)
{
    fwrite(buffer, sizeof(char), 2, output);
}

//now that our output file matches the input file, it's time for our prgoram to go to work... 

fprintf(output, " Jeff\n");

//let the user know that the program has successfully run!
printf("Congratulations! Your input file has been Jeff-i-fied! Woah! Check out the results in %s\n", fileName);

//and clean up our mess... 
free(fileName);
fclose(output); 
fclose(input);
return 0;
}