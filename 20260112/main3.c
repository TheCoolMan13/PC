#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char **argv)
{
  if(argc != 3)
  {
    fprintf(stderr, "Usage: %s input_file\n", argv[0]);
    exit(-1);
  }

  FILE *input = NULL;
  FILE *output = NULL;
  if((input = fopen(argv[1], "r")) == NULL)
  {
    perror(argv[1]);
    exit(1);
  }
  if((output = fopen(argv[2], "wb")) == NULL)
  {
    perror(argv[2]);
    exit(1);
  }

  uint16_t nr;
  while(fscanf(input, "%d", &nr) == 1)
  {
    printf("Numarul citit este: %04X\n", nr);
    fwrite(&nr, sizeof(uint16_t), 1, output);
  }




  if(fclose(output) < 0)
  {
    perror("fclose output");
    exit(-1);
  }
  if(fclose(input) < 0)
  {
    perror("fclose input");
    exit(-1);
  }
  return 0;
}
