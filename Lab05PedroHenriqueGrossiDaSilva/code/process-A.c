// Arquivo process-A.c: gera um numero aleatorio. Envia mensagens(numero gerado + PID) para uma fila de mensagens Posix.
// Em Linux, compile usando: gcc -o process-A process-A.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <unistd.h>

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

#define QUEUE "/my_queue"

int main (int argc, char *argv[])
{
   mqd_t  queue;         // descritor da fila
   struct mq_attr attr;  // atributos da fila
   int    msg;           // mensagem a enviar
   int	  num;		 // numero gerado
   int	  counter;	 // conta o numero de mensens enviadas

   // define os atributos da fila  
   attr.mq_maxmsg  = 10;           // capacidade para 10 mensagens
   attr.mq_msgsize = sizeof(msg);  //tamanho de cada mensagem
   attr.mq_flags   = 0;

   umask (0);			   // mascara de perissoes (umask)

   // abre ou cria a fila com permissoes 0666
   if ((queue = mq_open (QUEUE, O_RDWR|O_CREAT, 0666, &attr)) < 0) {
	   perror ("mq_open");
	   exit (1);
   }

   for (;;)
   {
      num = random() % 100 ;  // valor entre 0 e 99

      // envia o numero como mensagem
      counter = 0;
      do {
	      if (counter == 0)
		      msg = num;
	      else
		      msg = getpid();
	      counter++;

	      if (mq_send (queue, (void*) &msg, sizeof(msg), 0) < 0)
	      {
		      perror ("mq_send");
		      exit (1);
	      }
	      printf ("Sent message with value %d\n", msg);
      } while (counter != 2);
      sleep (1) ;
   }
}
