/* Copyright (C) 2006 PRAV - Pesquisa em Redes de Alta Velocidade
 *                    NTVD - N�cleo de TV Digital
 * http://www.ufrgs.br/ntvd
 *
 *  O objetivo deste programa � apresentar a base da estrutura de programa��o com sockets
 *  atrav�s de UDP
 *
 * Cli.c: Esqueleto de cliente UDP. 
 * Argumentos: -h <IP destino> -p <porta>
 *
 * Desenvolvido para sistemas UNIX Like (Linux, FreeBSD, NetBSD...) e Windows
 *		Maiko de Andrade
 *		Valter Roesler
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <winsock2.h>
	
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>	
	#define SOCKET	int
	#define Sleep sleep
#endif

int main(int argc, char **argv){
	 struct sockaddr_in peer;
	 SOCKET s;
	 int porta, peerlen, rc, i,taxa, npacotes;
	 char ip[16], buffer[1250];
	 
#ifdef _WIN32
	 WSADATA wsaData;
  
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		printf("Erro no startup do socket\n");
		exit(1);
	}
#endif

	 if(argc < 6) {
		  printf("Utilizar:\n");
		  printf("trans -h <numero_ip> -p <porta> -r <taxa_kbits>\n");
		  exit(1);
	 }

	 // Pega parametros
	 for(i=1; i<argc; i++) {
		  if(argv[i][0]=='-') {
				switch(argv[i][1]) {
					 case 'h': // Numero IP
						  i++;
						  strcpy(ip, argv[i]);
						  break;

					 
					 case 'p': // porta
						  i++;
						  porta = atoi(argv[i]);
						  if(porta < 1024) {
								printf("Valor da porta invalido\n");
								exit(1);
						  }
						  break;
						  
					case 'r': // taxa kbits
						  i++;
						  taxa = atoi(argv[i]);
						  
						  if(taxa < 1) {
								printf("Taxa precisa ser >= 1");
								exit(1);
						  }
						  npacotes = taxa / 10; //numero de pacotes(de 1250 bytes) a serem transmitidos em 1s
						 break; 
					 default:
						  printf("Parametro invalido %d: %s\n",i,argv[i]);
						  exit(1);
				}		  	 
		  } else {
			  printf("Parametro %d: %s invalido\n",i, argv[i]); 
				exit(1);
		  }
	 }
	 
	
	 
// Cria o socket na familia AF_INET (Internet) e do tipo UDP (SOCK_DGRAM)
	 if((s = socket(AF_INET, SOCK_DGRAM,0)) < 0) {
		  printf("Falha na criacao do socket\n");
		  exit(1);
 	 }
	 
// Cria a estrutura com quem vai conversar 
	 peer.sin_family = AF_INET;
	 peer.sin_port = htons(porta);
	 peer.sin_addr.s_addr = inet_addr(ip); 
	 peerlen = sizeof(peer);
	
// Envia pacotes Hello e aguarda resposta
	while(1)
	{
		strcpy(buffer,"Hello");
		//printf("Npacotes: %d, Tempo de pacote(ms) %d.\n",npacotes,tempo_pacote/1000);
		//getchar();
		for(i=0;i<npacotes;i++){
			sendto(s, buffer, sizeof(buffer), 0, (struct sockaddr *)&peer, peerlen);
			printf("Enviado Hello\n");

		}
			sleep(1);
//#ifdef _WIN32
		//rc = recvfrom(s,buffer,sizeof(buffer),0,(struct sockaddr *)&peer, &peerlen); 
//#else
		//rc = recvfrom(s,buffer,sizeof(buffer),0,(struct sockaddr *) &peer,(socklen_t *) &peerlen); 
//#endif
		
		//printf("Recebido %s\n\n",buffer);
		
	}
}
