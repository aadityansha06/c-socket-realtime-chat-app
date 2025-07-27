#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#include<process.h>




      char recv_buffer[1024],send_buffer[1024];
     


      void recive_loop(void* sock){
        SOCKET clientsocket = (SOCKET)sock;
        while (1)
        {
          // recv() reutrn the total number of bytes recived  but doesn't put
          /* null at the end which can led to garbage value

          */
             int msg_len= recv(clientsocket,recv_buffer,sizeof(recv_buffer)-1,0);
             if(msg_len<0){
              printf("\n\t\t error occcured in reciving");
              break;
             }
              recv_buffer[msg_len]='\0';
              if (strcmp(recv_buffer,"exit")==0)
              {
                 printf("\nClient left..");
                    closesocket(clientsocket);
                  WSACleanup();// unlink window api
                                  exit(1);
                 break;
              }
              printf("\n\tClient: %s\nSend message ...",recv_buffer);
              
        }
        
      }
      void send_loop(void* sock){
          SOCKET clientsocket = (SOCKET)sock;
         while (1)
        {
          printf("\nSend message ...\t\t");
          fflush(stdin); // Optional: before fgets(), especially after scanf()

          fgets(send_buffer,sizeof(send_buffer),stdin);
          send_buffer[strcspn(send_buffer, "\n")] = '\0';
              send(clientsocket,send_buffer,strlen(send_buffer),0);
              if (strcmp(send_buffer,"exit")==0)
              {
                 printf("\nYou left..");
                   closesocket(clientsocket);
                  WSACleanup();
                                   exit(1);// unlink window api
                  int a;
                  scanf("%d",&a);
                 
                 break;
              }
              
        }
      }





int main(int argc, char const *argv[])
{
    WSADATA wsd; // WSADATA is a strucutre , use to initllize socket api for windows
    SOCKET sockfd,clientsocket ; // in windows not int type we create socket type sokcet file direcutirey to sotre socket intilalitsation;
    struct sockaddr_in serveraddr ,  clientaddr; // sockaddr is a strucutre in which we can store server address like sin_adress , port , sin interface etc

    WSAStartup(MAKEWORD(2,2),&wsd); // makeword to tell which socket verison i.e 2.2 verison and the givng adress of  windows(os) sturct using wsd;
    sockfd= socket(AF_INET,SOCK_STREAM,0); /*
    
    AF_INEt defines the family of  ip i.e ip adress v4 or v6 ; 
    2nd is type of sokcet whtehter its stream or datagram
    3rd is in stram there are many type fo socket specific which or whchh protocl 
    or security will be sed from stream so for TCP its 0
    */

// bind()
    // Assigning address to the ednpoint or say socket we have jsut created it not assigned its
    /*
    adress where client can make request using same type of socket or endpoint i.e ipv4
    stram and in stram tcp
    */  

    serveraddr.sin_family = AF_INET; // ipv4;
    serveraddr.sin_port = htons(9090); // at the server ip address the specifc room will be or 
    // common gorund to send request to  sever will be 9090 think of it as a room in hosetl
    // where hostel is ip of this and port is the speficif room in which client has to go
    serveraddr.sin_addr.s_addr = INADDR_ANY; // ALLOW ANYONE TO CONNET WITH THIS SERVER

   bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

   listen(sockfd,3); // wait for connection max-3 

   printf("waiting for connection.. at port 9090");

    // accept he client connection and store its ip adress in clientadress so that
    // if server want to say something it would able to
        int clientsize = sizeof(clientaddr);
 /*New socket to communicate with client*/  
  clientsocket= accept(sockfd,(struct sockaddr*)&clientaddr,&clientsize);

    if (clientsocket == INVALID_SOCKET)
    {
        printf("Conencting client failed");
    }else{
        printf("\nconnected successfully.. from IP %s\n",inet_ntoa(clientaddr.sin_addr));
    }
    char buffer[1024] = "Hello CLient you are now connected";
    send(clientsocket,buffer,sizeof(buffer),0);

_beginthread((void(*)(void*))recive_loop, 0, (void*)clientsocket);
/*
 in multi threaindg pointer of the paramneter is passed i.e address 
 and in the function we create a pointer varibale to store the address or pointer
 then convert it back to the parameter
 "BHAI pls itna effort mara hu ek feedback de dena  kar dena "

 e.g 
  void recive_loop(void* sock){  // sack is a pointer having address of that clientaddress
        SOCKET clientsocket = (SOCKET)sock;
*/
_beginthread((void(*)(void*))send_loop, 0, (void*)clientsocket);
   while(1) {
    Sleep(1000); // Keep main thread alive ****IMP****** Thnx to calude to tell me
}
// At the end of main(), before return 0:
printf("Press any key to exit...\n");
getchar(); // or _getch() if you include <conio.h>
    return 0;
}
