//Autor:Ron ben david

//#include "pico/stdlib.h"
//#include "pico/binary_info.h"
//const uint LED_PIN = 25;
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 512	//Max length of buffer
#define PORT 9040	//The port on which to listen for incoming data

void die(char *s)
{
	perror(s);
	exit(1);
}

int main(void)
{
	/*

    bi_decl(bi_program_description("First Blink"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
	*/
	struct sockaddr_in si_me, si_other;
	
	int s, i, slen = sizeof(si_other) , recv_len;
	char buf[BUFLEN];
	int cnt=0;
	//create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	
	// zero out the structure
	memset((char *) &si_me, 0, sizeof(si_me));
	
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
	}
	
	//keep listening for data
	while(1)
	{
		printf("\n\n-----Waiting for New emergency call-----\n\n");
		fflush(stdout);
		
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
		{
			die("recvfrom()");
		}
		
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("%s\n" , buf);
		/* BLINKING LED
		while (cnt!=1000) {
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
		cnt+=1;
		}
		*/

    }
	close(s);
	return 0;
}
