#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <math.h> //para elevar ao quadrado e tirar raiz
#include <time.h>

#define MAXVET 50
#define IP "127.0.0.1"
#define PORT 8080

float v[MAXVET]; 

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

	// imprime pizza
	for (int i = 0; i < MAXVET; i++) {
		printf("%0.2f\n", v[i]);
	}

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

	// Enviando vetor para o servidor
	if (send(sock, &v, MAXVET * sizeof(float), 0) < 0) {
		puts("Send failed");
		return 1;
	}

	// Recebendo resposta do servidor
	if (recv(sock, &server_reply, 2 * sizeof(float), 0) < 0) {
		puts("recv failed");
		return 0;
	}

	//Escrevendo resposta do servidor
	puts("Server reply :\n");
	for (int i = 0; i < 2; i++) {
		printf("%0.2f\n", server_reply[i]);
	}

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
  for (int i = 0; i < MAXVET; i++) {
		v[i] = pow((i+1) - (f_aleat(MAXVET)/2), 2); 
  }
	for (int i = 0; i < MAXVET; i++) { 
		v[i] = sqrt(v[i]);
  }
}