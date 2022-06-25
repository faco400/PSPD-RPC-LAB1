#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <math.h> //para elevar ao quadrado e tirar raiz
#include <time.h>

#define MAXVET 12500
#define TOTALVET 500000
#define IP "127.0.0.1"
#define PORT 8080

float v[TOTALVET];
float *p;

/* funcoes auxiliares */
float f_aleat(int ); // Gera um valor aleatorio entre 0 e X
void init_vet ( ); // inicializa o vetor

int main(int argc, char* argv[]) {
	int sock;
	struct sockaddr_in server;
	float server_reply[2];

	srand(time(0));

	// Inicializar vetor
	init_vet();

	// Criar socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	// Configuração do Socket
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

	// Conectar ao servidor remoto
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");

	// enviando 40 pacotes de 50000 bytes
	int n_package = TOTALVET/MAXVET;
	printf("%d\n", n_package);
	float partial_min, partial_max;
	for(int i = 0; i < n_package; i++){
		p = &v[i*MAXVET];
		// Enviando vetor para o servidor
		if (send(sock, p, MAXVET * sizeof(float), 0) < 0) {
			puts("Send failed");
			return 1;
		}

		// Recebendo resposta do servidor
		if (recv(sock, &server_reply, 2 * sizeof(float), 0) < 0) {
			puts("recv failed");
			return 0;
		}
		if(i==0){
			partial_min = server_reply[0];
			partial_max = server_reply[1];
		}else{
			if(server_reply[0] < partial_min)
				partial_min = server_reply[0];
			if(server_reply[1] > partial_max)
				partial_max = server_reply[1];
		}
	}

	//Escrevendo resposta do servidor
	puts("Server reply :\n");
	printf("Menor: %0.2f\n", partial_min);
	printf("Maior: %0.2f\n", partial_max);

	// fechar o socket
	close(sock);
	return 0;
}

// Gera um valor aleatorio entre 0 e X
float f_aleat(int X) {
	return rand() % X;
}

// inicializa o vetor
void init_vet () {
 	for (int i = 0; i < TOTALVET; i++) {
		v[i] = pow((i+1) - (f_aleat(TOTALVET)/2), 2); 
	}
	for (int i = 0; i < TOTALVET; i++) { 
		v[i] = sqrt(v[i]);
	}
}