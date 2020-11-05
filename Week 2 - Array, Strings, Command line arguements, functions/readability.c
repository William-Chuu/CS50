#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

void coleman_liau(string a);

int main(void)
{
    string s = get_string("Text: ");

    coleman_liau(s);
}

void coleman_liau(string a)
{
    int L_counter = 0;
    int W_counter = 1;
    int S_counter = 0;

    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if ((a[i] >= 'a' || a[i] >= 'A') && (a[i] <= 'z' || a[i] <= 'Z'))
        {
            L_counter++;
        }

        else if (a[i] == ' ')
        {
            W_counter++;
        }

        else if (a[i] == '.' || a[i] == '!' || a[i] == '?')
        {
            S_counter++;
        }
    }

    float L = ((float) L_counter / (float) W_counter) * 100;
    float S = ((float) S_counter / (float) W_counter) * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }

    //test for word, sentences, and letter counters
    //printf("%i letter(s)\n%i word(s)\n%i sentence(s)\n", L_counter, W_counter, S_counter);

}



