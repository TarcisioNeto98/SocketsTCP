#include <stdio.h>
#include <stdlib.h>
#include "auxiliar.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTA 2000

#define TAM 100

struct sockaddr_in cliente, servidor;//Estrutura que conterá o ID e a porta do servidor.

int main(){//As funções bind(), listen() e accept() só são usadas no Servidor.
    
    int meu_socket = socket(AF_INET, SOCK_STREAM, 0);//A função socket cria um socket e retorna seu id
    
    if(meu_socket == -1){
        printf("Falha ao criar o socket!\n");
        exit(0);
    }
    
    char mensagem[] = "Oi, tudo bem?", recebido[TAM], nome[TAM];
    
    printf("Digite o nome do servidor: ");
    scanf("%[^\n]s", nome);
    
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PORTA);
    
    if(bind(meu_socket, (struct sockaddr*)&servidor, sizeof(servidor)) == -1){//Função utilizada para atribuir um 
        //endereco ip ao socket, só é utilizado no servidor
        //nela é passada o id do socket, o endereco da estrutura convertido para 'struct sockaddr' e o tamanho da estrutura.
        printf("Falha ao associar o id do socket ao servidor!\n");
        exit(0);
    }
    
    printf("Esperando conecção do cliente!\n");
    
    if(listen(meu_socket, 1) == -1){//Função utilizada para criar uma lista de espera, os clientes esperam nessa lista, enquanto um cliente não solicita uma
        //conecção o programa dormi, nela é passada o id do socket e o número maximo de clientes que podem ficar na fila(No caso, coloquei somente um, mas é opcional).
        printf("Falha ao criar uma lista de espera!\n");
        exit(0);
    }
    
    socklen_t tam_cliente = sizeof(cliente);//Ignore essa linha.
    
    int id_cliente = accept(meu_socket, NULL, NULL);//Função utilizada para aceitar a conecção do cliente, nela é passado o id do socket do servidor
    //estou em dúvida sobre o que ela retorna e os outros dois parametros.
    
    //int id_cliente = accept(meu_socket, (struct sockaddr*)&cliente, &tam_cliente); //Também funciona.

    if(id_cliente == -1){
        printf("Falha ao aceitar a conecção do cliente!\n");
        exit(0);
    }
    
    if(recv(id_cliente, recebido, sizeof(recebido), 0) == -1){
        printf("Falha ao receber a mensagem!\n");
        exit(0);
    }
    
    printf("O cliente %s ", recebido);
    
    esvazia(recebido);
    
    if(recv(id_cliente, recebido, sizeof(recebido), 0) == -1){
        printf("Falha ao receber a mensagem!\n");
        exit(0);
    }
    
    printf("Enviou a mensagem: %s\n", recebido);
    
    if(send(id_cliente, nome, sizeof(nome), 0) == -1){
        printf("Falha ao enviar a mensagem!\n");
        exit(0);
    }
    
    if(send(id_cliente, mensagem, sizeof(mensagem), 0) == -1){
        printf("Falha ao enviar a mensagem!\n");
        exit(0);
    }
    
    close(meu_socket);
    close(id_cliente);
    
    return 0;
}
