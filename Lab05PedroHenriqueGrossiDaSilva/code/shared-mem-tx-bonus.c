// Arquivo shared-mem-tx-bonus.c: cria e usa uma área de memória compartilhada. Apenas escreve. Espera permissão para escrever
// Em Linux, compile usando: gcc -o shared-mem-tx-bonus shared-mem-tx-bonus.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>

int main (int argc, char *argv[])
{
   int fd, value, *ptr;
   int s_fd, s_value, *s_ptr; // usados para o semaforo
   
   // Passos 1 a 3: abre/cria uma area de memoria compartilhada
   fd = shm_open("/sharedmem", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
   if(fd == -1) {
      perror ("shm_open");
      exit (1) ;
   }

   s_fd = shm_open("/sharedmem_s", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
   if(s_fd == -1) {
	   perror("shm_s_open");
	   exit (1);
   }

   // Passos 1 a 3: ajusta o tamanho da area compartilhada
   if (ftruncate(fd, sizeof(value)) == -1) {
      perror ("ftruncate");
      exit (1) ;
   }

   if (ftruncate(s_fd, sizeof(s_value)) == -1) {
	   perror ("ftruncate_s");
	   exit (1);
   }
   
   // Passos 2 a 4: mapeia a area no espaco de enderecamento deste processo
   ptr = mmap(NULL, sizeof(value), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED) {
      perror ("mmap");
      exit (1);
   }

   s_ptr = mmap(NULL, sizeof(s_value), PROT_READ|PROT_WRITE, MAP_SHARED, s_fd, 0);
   if(s_ptr == MAP_FAILED) {
	   perror ("mmap_s");
	   exit (1);
   }
   
   for (;;) {
      // Passo 5: escreve um valor aleatorio na area compartilhada se ja tiver sido lida
      if ((*s_ptr) == 1)
	      sleep(1);
      else {
	      value = random () % 1000 ;
	      (*ptr) = value ;
	      (*s_ptr) = 1;
	      printf ("Wrote value %i\n", value) ;
	      sleep (1);
      }
   }
}
