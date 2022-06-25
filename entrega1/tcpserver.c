#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXVET 12500

#define PORT 8080

/* funcoes auxiliares */
float max(float *); // pega maximo valor do vetor
float min(float *); // pega minimo valor do vetor

int main(int argc, char* argv[]) {
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;
	float message[MAXVET], i=0;
	float res[2];

	// Cria o socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	// Configura a estrutura do socket
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	// Faz o bind do socket
	if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {

		// print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	// Escuta o socket por até 3 conexoes
	listen(socket_desc, 3);

	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	// Aceita conexao com o cliente
	client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c);

	// Verifica se aceitou conexao com cliente
	if (client_sock < 0) {
		perror("accept failed");
		return 1;
	}

	puts("Connection accepted");

	// Recebe mensagem do cliente
	int n_package = 40;
	while(n_package > 0){
		if ((read_size = recv(client_sock, &message, MAXVET * sizeof(float), 0)) > 0) {
			
			res[0] = min(message); // descobbre min
			res[1] = max(message); // descobre max

			// enviando vetor resposta para o cliente
			write(client_sock, &res, 2 * sizeof(float));
		}

		// se cliente não mandou nada desconecta ou se houver erro avisa
		if (read_size == 0) {
			puts("Client disconnected");
		}
		else if (read_size == -1) {
			perror("recv failed");
		}
		n_package--;
	}

	return 0;
}

// pega maximo valor do vetor
float max (float *v) {
	int i;
	float n;
	n = v[0];
	for(i = 1; i < MAXVET; i++) {
		if(v[i] > n)
			n = v[i];
	}

	return n;
}

// pega minimo valor do vetor
float min (float *v) {
	int i;
	float n;
	n = v[0];
	for(i = 1; i < MAXVET; i++) {
		if(v[i] < n)
			n = v[i];
	}

	return n;
}
