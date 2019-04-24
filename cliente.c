#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "auxiliar.h"//Estrutura de dados auxiliar

//bibliotecas para criação de sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORTA 2000

#define IP "127.0.0.1"

struct sockaddr_in servidor;//Estrutura que conterá a porta e o ip do servidor, definida nas bibliotecas sys/types.h e sys/socket.h

int main(){
    
    char mensagem[] = "OI", recebido[100], nome[100];
    int meu_socket = socket(AF_INET, SOCK_STREAM, 0);//AF_UNIX se o endereco é a localização de arquivo no SO,
    //AF_INET pois o endereco será o ip e a porta, SOCK_STREAM indica que será usado o protocolo TCP.
    //Retorna o id do socket, se sucesso, -1 se erro.
    
    printf("Digite o nome do cliente:");
    
    scanf("%[^\n]s", nome);

    if(meu_socket == -1) falha("Falha ao criar o socket!");
    
    servidor.sin_family = AF_INET;//É o tipo de endereçamento que será a porta e o ip(ipv4).
    servidor.sin_port = htons(PORTA);//Converte a PORTA(2000) para a linguagem de rede.
    servidor.sin_addr.s_addr = inet_addr(IP);//Converte a string "127.0.0.1" para a linguagem de rede.
    
    if(connect(meu_socket, (struct sockaddr*)&servidor, sizeof(servidor)) == -1) falha("Falha ao se conectar com o servidor!");
        //Função utilizada para uma requisição de conecção com o servidor.
        //Nela é passado o id do socket, o ponteiro da estrutura do servidor convertido para (struct sockaddr), e o tamanho em bytes da estrutura
        //O tamanho em bytes é retornado pela função sizeof().
    
    if(send(meu_socket, nome, sizeof(nome), 0) == -1) falha("Falha ao enviar a mensagem!");
    
    if(send(meu_socket, mensagem, sizeof(mensagem), 0) == -1) falha("Falha ao enviar a mensagem!");
        //Função utilizada para enviar uma string, o primeiro argumento é o id do socket, o segundo é a
        //string(vetor), o terceiro é o tamanho em bytes da mensagem(vetor), o ultimo é uma flag(ainda não sei o que é) iniciada normalmente com zero.
    
    if(recv(meu_socket, recebido, sizeof(recebido), 0) == -1) falha("Falha ao receber a mensagem!");
        //Função utilizada para receber uma string, o primeiro argumento é o id do socket, o segundo é a
        //string(vetor) que será recebida, o terceiro é o tamanho em bytes da mensagem(vetor) recebida, o ultimo é uma flag(ainda não sei o que é) 
        //iniciada normalmente com zero.
    
    printf("O servidor %s ", recebido);
    
    esvazia(recebido);
    
    if(recv(meu_socket, recebido, sizeof(recebido), 0) == -1) falha("Falha ao receber a mensagem!");
    
    printf("Enviou a mensagem: %s\n", recebido);
    
    close(meu_socket);//Função utilizada para fechar a conecção com o servidor, nela é passado o id do socket.
    
    return 0;
}
