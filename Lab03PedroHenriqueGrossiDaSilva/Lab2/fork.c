/*
Criação de processos em UNIX

Compilar com gcc -Wall fork.c -o fork

Carlos Maziero, DINF/UFPR 2020
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int retval; //variavel para guardar o retorno do fork

	printf("Ola, sou o processo %5d\n", getpid()); // numero do processo em execução
	retval = fork(); // inicia um processo
	printf("[retval: %5d] sou %5d, filho de %5d\n", retval, getpid(), getppid());

	if (retval < 0)  //erro no fork()
	{
		perror("Erro");
		exit(1);
	}
	else
		if(retval > 0)  //sou o processo pai
			wait(0); // espero a conclusão do processo filho
		else		// sou o processo filho
			sleep(5); // aguardo 5 segundos e me encerro automaticamente

	printf("Tchau de %5d!\n", getpid()); // o fiilho se encera antes do pai por isso é "printado" antes
	exit(0); // fim do processo
}
