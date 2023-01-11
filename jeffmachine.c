#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int jeffScan (FILE *input);
char * findFileType (char * fileName);

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: To add a jeff to a text file, use: ./jeffmachine yourFile.txt\n Or to run a jeff scan, use: ./jeffmachine yourFile.txt s\n");
        printf("The Jeff Machine can now accept 'jpg' files as well!  Usage: ./jeffmachine yourFile.jpg");
        return 1;
    }
    
    typedef uint8_t BYTE;
    
    //figure out the file type of our input file, so we know what to do with it.    
    char * fileType = findFileType(argv[1]);

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


//we create a filename for our output format...
char *fileName = malloc(sizeof(argv[1]) + (sizeof(char) * 5));
sprintf(fileName, "jeff_%s", argv[1]);

printf("Creating file %s \n", fileName);
FILE *output = fopen(fileName, "w");


//if our file is a text file...
if (strcmp(fileType, "txt") == 0)
{
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
}

if (strcmp(fileType, "jpg") == 0)
{
   //open our jeff pic... 
   FILE *jeffPic = fopen("./jeff.jpg", "r");
   if (jeffPic == NULL)
   {
        printf("Something has gone wrong... Jeff image not found... Please contact support \n");
        return 2;
   }

   //buffer for our read/write below...
   BYTE buffer[512];

   //copy jeff pic to outputfil 
   while(fread(buffer, sizeof(BYTE), 512, jeffPic) == 512)
   {
    fwrite(buffer, sizeof(BYTE), 512, output);
   }

    printf("Success!  Your image has been Jeff-i-fied! Open up %s to see your new image... \n", fileName);
    fclose(jeffPic);
}

//and clean up our mess... 
free(fileType);
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

char * findFileType(char* fileName)
{
    //find the length of the input string, subtract 1, and assign it to int 'last char'
    int lastchar = strlen(fileName) - 1;

    //allocate memory for our 3 digit filetype string...
    char* fileType = malloc(sizeof(char) * 4); 

    //add the last three digits of the input string to our 
    sprintf(fileType, "%c%c%c", fileName[lastchar - 2], fileName[lastchar - 1], fileName[lastchar]);

    //assign a NUL to denote the end of our string.. 
    fileType[3] = '\0'; 

    return fileType;
}