
#include "sendrec.h"

void die(char *s)
{
    perror(s);
    exit(1);
}
 
void* Sender()
{
    struct sockaddr_in si_me, si_other;
     
    int s, recv_len;
  // 	socklen_t slen = sizeof(si_other);
    char moskus[BUFLEN];
    strcat(moskus, "Hello Moskus");
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    si_other.sin_family = AF_INET;
    inet_pton(AF_INET, SADDRESS, &si_other.sin_addr);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    inet_pton(AF_INET, OURADDRESS, &si_me.sin_addr);
    //si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
   
    while(1)
    {
    	

        if (sendto(s, moskus, BUFLEN, 0, (struct sockaddr*) &si_other, sizeof(si_other)) == -1)
        {
            die("sendto()");
       	
        }
        printf("Sendt packet to %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data from sender: %s\n" , moskus);    
        sleep(2);
    }
 
    close(s);
    return 0;
}


void* Reciever()
{
    struct sockaddr_in si_me, si_other;
     
    int r, recv_len, slen = sizeof(si_other);
   // socklen_t restrict slen = sizeof(si_other);
    char buf[BUFLEN];
    
    //create a UDP socket
    if ((r=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    si_other.sin_family = AF_INET;
    inet_pton(AF_INET, SADDRESS, &si_other.sin_addr);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    inet_pton(AF_INET, OURADDRESS, &si_me.sin_addr);
    //si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(r , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
      
        memset(&buf[0], 0, sizeof(buf)); 
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(r, buf, BUFLEN, 0, &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data received: %s\n" , buf);    
    }
 
    close(r);
    return 0;
}