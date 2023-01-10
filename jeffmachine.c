#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int jeffScan (FILE *input);

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: To add a jeff to your file, use: ./jeffmachine yourFile.txt\n Or to run a jeff scan, use: ./jeffmachine yourFile.txt s\n");
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


//check if the user has provided additonal commandline arguments...
if (argc > 2){

    //if our user has included the "s" argument, we will run a jeff scan and printf the results to the user... 
    if (strcmp(argv[2], "s") == 0)
    {
        //let the user know the scan is taking place... (and scan) 
        printf("Your commandline arguments indidcate you wish to perform a Jeff Scan... Scanning...\n");
        int jeffCount = jeffScan(input); 
        printf("Scanning...\n");

        //print the results to the user...
        printf("Scan complete!  Your input file contains %i instances of 'Jeff'\n", jeffCount);
        fclose(input);
        return 0;
    }
}

printf("did not activate the s argument conditional...\n");
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


int jeffScan(FILE *input)
{


    //our buffer "letter" where we can store fread value of the while that looks at each char... 
    char *j = malloc(sizeof(char));

    //our buffer array to write to (room to store jeff + nul char)
    char *buffer = malloc(sizeof(char) * 5);

    //our count variable, where we will store the number of "jeff"'s we find... 
    int count = 0; 


// we're looking for j's... 
while(fread(j, sizeof(char), 1, input) == 1)
    {
      //we create this 'letter' char to dump the value stored at pointer j into (and we convert that to uppercase if lowercase)...
      //this step is technically unnecessary but i think it makes the code read just a little better.
      char letter = toupper(*j); 

      //if we find a "j", we're going to see what the next 3 characters are and add them to our array...
      if (letter == 'J')
      {
        //fill our array starting at the second letter... 
        fread(buffer + 1, sizeof(char), 4, input); 


        //...since we hit the if condintional for our j, we know the first letter is j
        //but to avoid using a "magic letter", we'll assign the value of the letter variable from above...
        buffer[0] = letter;
            
        //set our text to all upper case...
        for (int i = 0; i < 4; i++)
        {
            buffer[i] = toupper(buffer[i]);
        }
        
        //we also manually set a nul character here to mark the end of the string, so our conditional later doesn't get confused...
        buffer[4] = '\0';            
                  
        //if our buffer values (case insensitive) spell out "JEFF, we add one to the counter... 
        if (strcmp(buffer, "JEFF") == 0)
            {
            count++;
            }
    }
    }

    free(buffer);
    return count;
}