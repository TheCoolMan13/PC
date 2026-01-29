#include <stdio.h>
#include <stdint.h>


void afisare_pe_biti(uint8_t input)
{
  for(int i = 7 ; i >= 0 ; i--)
    {
      printf("%d" , (input>>i)&1);
    }
  printf("\n");
}

int main()
{

  uint8_t input;
  scanf("%hhu" , &input);
  uint8_t output;
  output = input;
  uint8_t mask;
  for(int i = 0 ; i< 8 ; i++)
    {
      if(i ==  0 || i == 2 || i == 3)
	{
	  //setare
	  mask = 1<<i;
	  output |=mask;
	}
      if(i == 1 || i == 5 || i == 6)
	{
	  //resetare
	  mask = 1<<i;
	  output &= ~mask;
	}
      if(i == 4 || i == 7)
	{
	  //complementare
	  mask = 1<<i;
	  output ^=mask;
	}
    }

  afisare_pe_biti(input);
  afisare_pe_biti(output);
  return 0;
}

