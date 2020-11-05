#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int keycheck(string a);
void encipher(string x, string u);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    string key = argv[1];

    if (keycheck(key) == 1) //if error, end code
    {
        return 1;
    }

    string text = get_string("plaintext:  ");

    encipher(key, text); //have key and text, encipher now
    
    return 0;

}

int keycheck(string a)
{

    if (strlen(a) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else
    {

        for (int i = 0, n = strlen(a); i < n; i++) //looking at key one letter at a time
        {

            for (int c = strlen(a), b = i + 1; b < c; b++) // looking at key one letter at a time starting from second letter
            {
                if (a[i] == a[b])   //start with first letter, check if same as second letter then third etc. (2,3,4,5,6). Repeats after now checking if 2 is saem as 3,4,5,6,etc.
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }

            }

            if (a[i] >= '0' && a[i] <= '9') //checking if letter is a number
            {
                printf("Key must contain alphabetic characters.\n");
                return 1;
            }

            a[i] = toupper(a[i]); //passes checks -> make upper case
        }
    }


    return 0;
}


void encipher(string x, string u)
{
    string difference = x;

    for (int i = 'A'; i <= 'Z'; i++)
    {
        difference[i - 'A'] = difference[i - 'A'] - i;  //making an array of the "differences" ex J-A, Z-B. Looping through each letter of alphabet ***NOTE THAT [i = 'A'] IS JUST DETERMINING LOCATION IN ARRAY
    }

    for (int t = 0; u[t] != '\0'; t++) //loop through each character in text
    {
        if (isalpha(u[t]))  //if alphabetic character
        {
            if (isupper(u[t]))  //if uppercase
            {
                u[t] += difference[u[t] - 'A'];     //A = A + difference[A-A = 0] == A = A + (J-A)
            }

            else
            {
                u[t] += difference[toupper(u[t]) - 'A'];    // need to convert text character to upper case since all characters in "difference" is upper case. Ex. a = a + (J - A) == J - 32 (coverting to lower case)
            }
        }
    }

    printf("ciphertext: %s\n", u);
}


