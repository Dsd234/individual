#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char buff[512];
	char buff2[512];
	
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	serv_adr.sin_port = htons(9020);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 2) < 0)
		printf("Error en el Listen");
	
	
	int i = 0;
	for(;;)
	{
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexi?n\n");
		
		int terminar = 0;
		while (terminar == 0){
		
		ret=read(sock_conn,buff, sizeof(buff));
		printf ("Recibido\n");
		
		buff[ret]='\0';
		
		char *p = strtok(buff,"/");
		int codigo = atoi(p);
		float grados;
		if (codigo!=0){
		p = strtok(NULL,"/");
		grados = atof(p);
		}
		if(codigo == 0)
		{
			terminar = 1;
		}
		else if(codigo == 1)
		{
			float p =(grados*(9*0.2)+32);
			sprintf(buff2,"%f",p);
		
		}
		else if(codigo == 2)
		{
			float p =(grados-32)*5*0.11;
			sprintf(buff2,"%f",p);
			
		}
		
		printf("%f",grados);
		if(codigo !=0){
			write (sock_conn,buff2, strlen(buff2));
		}
		
		}
		
		
		// Se acabo el servicio para este cliente
		//close(sock_conn); 
		
	}
}

