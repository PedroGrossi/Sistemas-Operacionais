// Arquivo shared-mem-rx.c: cria e usa uma �rea de mem�ria compartilhada. Apenas le.
// Em Linux, compile usando: gcc -o shared-mem-rx shared-mem-rx.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>

int main (int argc, char *argv[])
{
   int fd, value, *ptr;
   
   // Passos 1 a 3: abre/cria uma area de memoria compartilhada
   fd = shm_open("/sharedmem", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
   if(fd == -1) {
      perror ("shm_open");
      exit (1) ;
   }

   // Passos 1 a 3: ajusta o tamanho da area compartilhada
   if (ftruncate(fd, sizeof(value)) == -1) {
      perror ("ftruncate");
      exit (1) ;
   }
   
   // Passos 2 a 4: mapeia a area no espaco de enderecamento deste processo
   ptr = mmap(NULL, sizeof(value), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED) {
      perror ("mmap");
      exit (1);
   }
   
   for (;;) {      
      // Passo 5: le e imprime o conteudo da area compartilhada
      value = (*ptr) ;
      printf("Read value %i\n", value);
      sleep (1) ;
   }
}
