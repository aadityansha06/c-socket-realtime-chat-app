#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>



      char buffer[1025],recv_buffer[1024],send_buffer[1024];
     


      void recive_loop(void* sock){
        SOCKET clientsocket = (SOCKET)sock;
        while (1)
        {
          // recv() reutrn the total number of bytes recived  but doesn't put
          /* null at the end which can led to garbage value

          */
            // -1 for null , because null
      // may or maynmot send by th sender

             int msg_len= recv(clientsocket,recv_buffer,sizeof(recv_buffer)-1,0);
             if(msg_len<0){
              printf("error occcured in reciving");
              break;
             }
              recv_buffer[msg_len]='\0';
              if (strcmp(recv_buffer,"exit")==0)
              {
                 printf("\nHost left..");
                    closesocket(clientsocket);
                  WSACleanup();// unlink window api
                 exit(1);
           
                 break;
              }
                     printf("\n\tHost: %s\n",recv_buffer);
        }
        
      }
      void send_loop(void* sock){
          SOCKET clientsocket = (SOCKET)sock;
         while (1)
        {
          printf("\nSend message ...\t\t");
          fflush(stdin); // Optional: before fgets(), especially after scanf()

          fgets(send_buffer,sizeof(send_buffer),stdin);
   // Remove newline if present
send_buffer[strcspn(send_buffer, "\n")] = '\0';
              send(clientsocket,send_buffer,strlen(send_buffer),0);
              if (strncmp(send_buffer,"exit",4)==0)
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
    SOCKET clientsocket ; // in windows not int type we create socket type sokcet file direcutirey to sotre socket intilalitsation;
    struct sockaddr_in serveraddr ,  clientaddr; // sockaddr is a strucutre in which we can store server address like sin_adress , port , sin interface etc
  char ip[100];

  printf("Enter the ip to connect...\t");
  scanf("%s",ip);
    WSAStartup(MAKEWORD(2,2),&wsd); // makeword to tell which socket verison i.e 2.2 verison and the givng adress of  windows(os) sturct using wsd;
    clientsocket= socket(AF_INET,SOCK_STREAM,0); 


    if (clientsocket == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code : %d", WSAGetLastError());
        WSACleanup();
        return 1;
    }
   



    serveraddr.sin_family = AF_INET; // ipv4;
    serveraddr.sin_port = htons(9090); 
    serveraddr.sin_addr.s_addr = inet_addr(ip); // convert string ip to binary

   if (connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
   {
    printf("Connection failed..");
    
   closesocket(clientsocket);
   WSACleanup();

    return 1;
   }
   
    

 // wait for connection max-3 

   printf("\nConnected successfully.. to server%d\n",serveraddr.sin_addr);

    // accept he client connection and store its ip adress in clientadress so that
    // if server want to say something it would able to

    

     #include <process.h> // Add at top

// both send and recive to run simultenously otherriwse the function will stuck in any one of them
// this called multithreading
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
    Sleep(1000);  // Keep main thread alive ****IMP****** Thnx to calude to tell me
    // Keep main thread alive
}
// At the end of main(), before return 0:
printf("Press any key to exit...\n");
getchar(); // or _getch() if you include <conio.h>

    return 0;
}
