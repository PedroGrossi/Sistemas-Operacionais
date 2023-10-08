// Arquivo process-B.c: recebe mensagens de uma fila de mensagens Posix.
// Em Linux, compile usando: gcc -o process-B process-B.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

#define QUEUE "/my_queue"

int main (int argc, char *argv[])
{
   mqd_t  queue;                   // descritor da fila de mensagens
   int   msg ;                     // mensagens contendo um inteiro
   int   counter = 0; 		   // numero de mensagens
 
   // abre a fila, se existir
   if ((queue = mq_open (QUEUE, O_RDWR)) < 0)
   {
      perror ("mq_open");
      exit (1);
   }

   // recebe cada mensagem e imprime seu conteudo
   for (;;)
   {
	   if ((mq_receive (queue, (void*) &msg, sizeof(msg), 0)) < 0) {	   
		   perror("mq_receive:") ;
		   exit (1) ;
	   }


	   if (counter == 0) {
		   printf ("Received msg value %d\n", msg);
		   counter++;
	   }
	   else {
		   printf ("From process number %5d\n", msg);
		   counter = 0;
	   };
   }
}
