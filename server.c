// From the book, pg 947
#include "csapp.h"
#include "signal.h"
//#ifndef CONCURRENT
//#define CONCURRENT
// Harsh Devprakash Gupta
// 650125174
/* $end echoserverimain */
void echo(int connfd) 
{
    size_t n; 
    char buf[MAXLINE]; 
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { //line:netp:echo:eof
	printf("server received %d bytes\n", (int)n);
	Rio_writen(connfd, buf, n);
    }
}
/* $end echo */
void sequential_server(int argc, char **argv){
    char sentence[1000];
    FILE *fptr;
    int index = 0;
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    
    char client_hostname[MAXLINE], client_port[MAXLINE];

    fptr = fopen("log.txt", "w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
    index++;
	clientlen = sizeof(struct sockaddr_storage); 
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, 
                    client_port, MAXLINE, 0);
        //printf("Connected to (%s, %s)\n", client_hostname, client_port);
        fprintf(fptr,"%d %s %s)\n", index,client_hostname, client_port);
	echo(connfd);
	Close(connfd);
    }
    fclose(fptr);
    exit(0);
    


}


int main(int argc, char **argv) 
{
    pid_t pid; //Process id 
    pid = fork();
    if (pid == 0)
        {   
            sequential_server(argc, argv);
            
            
        }
        sleep(1);
    
    /*char sentence[1000];
    FILE *fptr;
    int index = 0;
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;*/  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    
    /*char client_hostname[MAXLINE], client_port[MAXLINE];

    fptr = fopen("log.txt", "w");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
    index++;
	clientlen = sizeof(struct sockaddr_storage); 
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, 
                    client_port, MAXLINE, 0);
        //printf("Connected to (%s, %s)\n", client_hostname, client_port);
        fprintf(fptr,"%d %s %s)\n", index,client_hostname, client_port);
	echo(connfd);
	Close(connfd);
    }
    fclose(fptr);
    exit(0);*/
}
