#include <stdio.h>
#include <stdint.h>
// Ex 14

int task_a(uint16_t input)
{
  uint16_t output=0;
  for(int nibble = 3 ; nibble >= 0 ; nibble--)
    {
      for(int indice = nibble * 4 + 4 ; indice > (nibble * 4) ; indice--)
	{
	  printf("%d" , (output>>indice)&1);
	}
    }
  return output;
}

int task_b()
{
  
  return 0;
}


int main()
{
  uint16_t input;
  uint16_t output;
  scanf("%hhu" , &input);
  output = task_a(input);

  return 0;
}
