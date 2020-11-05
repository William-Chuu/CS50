#include <stdio.h>
#include <cs50.h>

void validcard(long x);

int main(void)
{ 
    long n;
    do
    {
        n = get_long("Please enter your credit card # : ");
    }
    while (n < 1);

    validcard(n); 
}

void validcard(long x)
{
    
    //finding first digits
    long a = x / 10000000000000;
    long b = x / 100000000000000;
    long c = x / 1000000000000;
    long d = x / 1000000000000000;

    //for the loops
    long q = 0;
    long z = 0;
    long e = 1;
    long r = 1;

    if (a == 34 || a == 37)
    {

        for (int i = 1; i < 9; i++)
        {
            //gets non-multipled digit
            long k = (x % (10 * e)) / r;
            e = e * 100;
            r = r * 100;
            //sum non-multiplied
            q = (k + q);
        }

        e = 1;
        r = 10;

        for (int i = 1; i < 8; i++)
        {
            //gets multiplied digit PLUS multiplies by 2
            long s = ((x % (100 * e)) / r) * 2;
            e = e * 100;
            r = r * 100;
            //sum multiplied

            if (s >= 10)
            {
                
                long w = (s % 10) + (s / 10);
                z = w + z;
            }
            else
            {
                z = (s + z);
            }
        }

        if ((q + z) % 10 == 0)
        {
            printf("AMEX\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    
    } 
    
    else if (b == 51 || b == 52 || b == 53 || b == 54 || b == 55)
    {
        for (int i = 1; i < 9; i++)
        {
            //gets non-multipled digit
            long k = (x % (10 * e)) / r;
            e = e * 100;
            r = r * 100;
            //sum non-multiplied
            q = (k + q);
        }

        e = 1;
        r = 10;

        for (int i = 1; i < 9; i++)
        {
            //gets multiplied digit PLUS multiplies by 2
            long s = ((x % (100 * e)) / r) * 2;
            e = e * 100;
            r = r * 100;
            //sum multiplied

            if (s >= 10)
            {  
                long w = (s % 10) + (s / 10);
                z = w + z;
            }

            else
            {
                z = (s + z);
            }
        }

        if ((q + z) % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else 
        {
            printf("INVALID\n");
        }  

    } 
    
    else if (c == 4 || d == 4)
    {
        if (d == 4)
        {

            for (int i = 1; i < 9; i++)
            {
                //gets non-multipled digit
                long k = (x % (10 * e)) / r;
                e = e * 100;
                r = r * 100;
                //sum non-multiplied
                q = (k + q);
            }

            e = 1;
            r = 10;

            for (int i = 1; i < 9 ; i++)
            {
                //gets multiplied digit PLUS multiplies by 2
                long s = ((x % (100 * e)) / r) * 2;
                e = e * 100;
                r = r * 100;
                //sum multiplied

                if (s >= 10)
                {
                
                    long w = (s % 10) + (s / 10);
                    z = w + z;
                }

                else
                {
                    z = (s + z);
                }

            }

            if ((q + z) % 10 == 0)  
            {
                printf("VISA\n");
            }

            else
            {
                printf("INVALID\n");
            }  

        }

        else if (c == 4)
        {
            for (int i = 1; i < 8; i++)
            {
                //gets non-multipled digit
                long k = (x % (10 * e)) / r;
                e = e * 100;
                r = r * 100;
                //sum non-multiplied
                q = (k + q);
            }

            e = 1;
            r = 10;

            for (int i = 1; i < 7; i++)
            {
                //gets multiplied digit PLUS multiplies by 2
                long s = ((x % (100 * e)) / r) * 2;
                e = e * 100;
                r = r * 100;
                //sum multiplied

                if (s >= 10)
                {
                
                    long w = (s % 10) + (s / 10);
                    z = w + z;
                }
            
                else
                {
                    z = (s + z);
                }
            }

            if ((q + z) % 10 == 0)
            {
                printf("VISA\n");
            }

            else
            {
                printf("INVALID\n");
            }  

        }

        else 
        {
            printf("INVALID\n");
        }

    } 
    
    else
    {
        printf("INVALID\n");
    }
}

