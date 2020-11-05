#include <stdio.h>
#include <cs50.h>

void hash(int y);
void space(int x);

int main(void)
{
    //get number from person
    int n;
do
{
n = get_int("How many rows would you like? Please enter a number b/w 1 & 8\n");
}
// make sure in range of 1-8
while(n<1 || n>8);

int w =1;
//output each row and then loop to create new rows
for(int a=n; a>0; a--)
{
    
    space(a-1);
    hash(w);
    space(2);
    hash(w);
    printf("\n");
    w++;
}
  
 
}

//output x many of hashses
void hash(int y)
{
    for(int h=y; h>0; h--)
    {
    printf("#");
    }
}

//output x many of spaces
void space(int x)
{
    for(int i=x; i>0; i--)
    {
   printf(" ");
    }
}
