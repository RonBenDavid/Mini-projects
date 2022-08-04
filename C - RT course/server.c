//Autor:Ron ben david

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <signal.h>
#include <poll.h>
#include<time.h>
#include <pthread.h>

#define PORT "9034"  // the port users will be connecting to
#define PORT_POLICE "9040"	//The port on which to send data to police
#define PORT_AMBULANCE "9050"	//The port on which to send data to AMBULANCE
#define PORT_FIREMEN "9060"	//The port on which to send data to firemen
#define PORT_Stand_By_EME "9070"	//The port on which to send data to Stand_By_EME
#define BACKLOG 10   // how many pending connections queue will hold

#define MAXDATASIZE 500 // max number of bytes we can get at once

#define BUFLEN 512	//Max length of buffer

#define TIMEOUT 15000 //1500 milisec==15 sec

#define PATH "case_No"

#define SERVER "127.0.0.1"

#define TELEGRAM_BOT_TOKEN "ENTER YOUR BOT TOKEN"
#define TELEGRAM_CHAT_ID "ENTER YOUR CHAT ID"
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

const char arguments[2][10000];

void case_No(int new_fd, char* GPS);
void sigchld_handler(int s);
void* get_in_addr(struct sockaddr* sa);

void die(char *s)
{
	perror(s);
	exit(1);
}

void *EME_call_func()
{
	struct sockaddr_in si_other;
	int s, i, slen=sizeof(si_other);
	char buf[BUFLEN];
	int ret=1;
	int port_num;
	port_num=atoi(arguments[1]);
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(port_num);
	
	if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	while(1)
	{
		//send the message
		if (sendto(s, arguments[0], strlen(arguments[0]) , 0 , (struct sockaddr *) &si_other, slen)==-1)
		{
			die("sendto()");
		}
		
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
		{
			die("recvfrom()");
		}
		
		puts(buf);
	}
	close(s);
}
void *urlencode()
{
    // allocate memory for the worst possible case (all characters need to be encoded)
    char* originalText;
    char *encodedText = (char *)malloc(sizeof(char)*strlen(arguments[0])*3+1);
    char final[1000]={0};   
    const char *hex = "0123456789abcdef";
    
    int pos = 0;
    for (int i = 0; i < strlen(arguments[0]); i++) {
        if (('a' <= arguments[0][i] && arguments[0][i] <= 'z')
            || ('A' <= arguments[0][i] && arguments[0][i] <= 'Z')
            || ('0' <= arguments[0][i] && arguments[0][i] <= '9')) {
                encodedText[pos++] = arguments[0][i];
            } else {
                encodedText[pos++] = '%';
                encodedText[pos++] = hex[arguments[0][i] >> 4];
                encodedText[pos++] = hex[arguments[0][i] & 15];
            }
    }
    encodedText[pos] = '\0';
    sprintf(final,"curl --silent --output /dev/null -X GET \"https://api.telegram.org/bot%s/sendMessage?chat_id=-%s&text=%s\"",TELEGRAM_BOT_TOKEN,TELEGRAM_CHAT_ID,encodedText);
system(final);
}

int main(void)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, * servinfo, * p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    char id[15];
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;//AF_UNSPEC use IPV4 OR IPV6
    hints.ai_socktype = SOCK_STREAM;//STREAM CLIENT
    hints.ai_flags = AI_PASSIVE; // use my local IP

    //GET INFO
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));//gai_strerror - nction translates these error codes to a human readable string
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
            sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure
    //CHECK BIND
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }
    //LISTEN
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // kill all zombies processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    //SIGANLS
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    // main accept() loop
    while (1) {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr*)&their_addr),
            s, sizeof s);
        printf("\nserver: got connection from %s\n", s);




        //fork
        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listene
            if (send(new_fd, "911 what's is your Emergency\n", 30, 0) == -1)
                perror("send");
            send(new_fd, "911 what's is your Emergency\n", 30, 0);
            int numbytes;
            char buf[MAXDATASIZE];

            //read massage with GPS
            numbytes = read(new_fd, buf, MAXDATASIZE - 1);
            buf[numbytes] = '\0';
            printf("%s\n", buf);

            //conv the GPS and do case
            char GPS_str[30];
            strcpy(GPS_str, buf);
            strcpy(buf, "Please stay calm, you will recieve a few questions\nPlease enter your ID:");
            write(new_fd, buf, strlen(buf));
            case_No(new_fd, GPS_str);
            printf("The socket closed!\n");
            close(new_fd);
            exit(0);
        }//end fork
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}




void case_No(int new_fd, char* GPS)
{
    char buf[MAXDATASIZE];
    char data[MAXDATASIZE];
    char prob_type[2];
    char get_hurt_str[2];
    char num_of_hurt_str[3];
    int  num_of_hurt = 0;
    char client_address[50]={0};
    struct pollfd fds[1];
    fds[0].fd = new_fd;
    fds[0].events = 0;
    fds[0].events |= POLLIN;
    time_t t;   // not a primitive datatype
    time(&t);
    fd_set readfds;
    struct timeval timeout_select;
    int rc_POLICE, rc_AMBULANCE, rc_FIREMEN, rc_STANDBY, rc_TELEGRAM;
    pthread_t thread_POLICE, thread_AMBULANCE ,thread_FIREMEN ,thread_STANDBY, thread_TELEGRAM;
    char timeout_massage[60] = "You have waited for too long, please try again! timeout";

    if (!poll(fds, 1, TIMEOUT)) {
        printf("timeout\n");
        send(new_fd, timeout_massage, strlen(timeout_massage), 0);
        close(new_fd);
        exit(0);
    }
    else {
        printf("waiting for client's ID\n");

        //read ID
        int numbytes = read(new_fd, buf, MAXDATASIZE - 1);
        buf[numbytes] = '\0';
        data[numbytes] = '\0';
        char client_ID[10];
        strcpy(client_ID, buf);
        printf("Client ID: %s\n", buf);
        printf("Questions were sent to the client, waiting for an answer\n");


        strcpy(buf, "What is the problem?\n1.Car accident\n2.Fire\n3.Break-in\n4.Medical emergency");
        write(new_fd, buf, strlen(buf));

        FD_ZERO(&readfds);
        FD_SET(new_fd, &readfds);
        timeout_select.tv_sec = TIMEOUT / 1000;
        timeout_select.tv_usec = 0;

        int sret = select(8, &readfds, NULL, NULL, &timeout_select);// ID return
        if (sret == 0)
        {
            printf("Client ID: %s - timeout\n", client_ID);
            send(new_fd, timeout_massage, strlen(timeout_massage), 0);
            close(new_fd);
            exit(0);
        }
        else
        {
            numbytes = read(new_fd, prob_type, 2);
            prob_type[numbytes - 1] = '\0';
            printf("\nProblem Number: %s\n", prob_type);


            strcpy(buf, "Someone Get hurt?\nif yes, How many Pepole?\else press 0");
            write(new_fd, buf, strlen(buf));
            numbytes = read(new_fd, num_of_hurt_str, sizeof(num_of_hurt_str));
            num_of_hurt = atoi(num_of_hurt_str);
            printf("Pepole that Get hurt: %s\n", num_of_hurt_str);
            // create text file
            FILE* fp;
            int i = 0;
            remove(PATH);
            strcat(client_address, PATH);
            strcat(client_address, client_ID);
            strcat(client_address, ".txt");
            fp = fopen(client_address, "wt");
            switch(prob_type[0])
	    {
		case '1':
			    if(num_of_hurt!=0){
					    sprintf(data, "New emergency call!!!\nTime: %s\nclient ID: %-12s \nGPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Car accident", num_of_hurt_str);
					    fprintf(fp, "Time: %s\nclient ID: %-12s \nMy GPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Car accident", num_of_hurt_str);
					    fclose(fp);
					    strcpy((char*)arguments[0], data);
					    printf("%s",arguments[0]);
		    			    strcpy((char*)arguments[1], "9040");
					   if( (rc_POLICE=pthread_create( &thread_POLICE, NULL, &EME_call_func, NULL)) ){
					      printf("Thread creation failed: %d\n", rc_POLICE);
					    }//POLICE
		  			    sleep(0.1);
					    strcpy((char*)arguments[1], "9050");
					   if( (rc_AMBULANCE=pthread_create( &thread_AMBULANCE, NULL, &EME_call_func, NULL)) ){
					      printf("Thread creation failed: %d\n", rc_AMBULANCE);
					    }//AMBULANCE
		  			    sleep(0.1);
					    strcpy((char*)arguments[1], "9070");
					   if( (rc_STANDBY=pthread_create( &thread_STANDBY, NULL, &EME_call_func, NULL)) ){
					      printf("Thread creation failed: %d\n", rc_STANDBY);
					    }//STANDBY
		  			    sleep(0.1);
					   if( (rc_TELEGRAM=pthread_create( &thread_TELEGRAM, NULL, &urlencode, NULL)) ){
					      printf("Thread creation failed: %d\n", rc_TELEGRAM);
					      }//TELEGRAM
		      			    sleep(0.1);
					    pthread_join( thread_POLICE, NULL);
					    pthread_join( thread_AMBULANCE, NULL);
					    pthread_join( thread_STANDBY, NULL);
					    pthread_join( thread_TELEGRAM, NULL);
			    }
			    else{
					    sprintf(data, "New emergency call!!!\nTime: %s\nclient ID: %-12s \nGPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : NO \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "car accident", num_of_hurt_str);
					    fprintf(fp, "Time: %s\nclient ID: %-12s \nMy GPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : NO \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "car accident", num_of_hurt_str);
					    fclose(fp);
					    strcpy((char*)arguments[0], data);
					    strcpy((char*)arguments[1], "9040");
					   if( (rc_POLICE=pthread_create( &thread_POLICE, NULL, &EME_call_func, NULL)) ){
					      printf("Thread creation failed: %d\n", rc_POLICE);
					    }//POLICE
		      			    sleep(0.1);
					    strcpy((char*)arguments[1], "9070");
					   if( (rc_STANDBY=pthread_create( &thread_STANDBY, NULL, &EME_call_func, NULL)) ){
					      printf("Thread creation failed: %d\n", rc_STANDBY);
					    }//STANDBY
		      			    sleep(0.1);
		    		           if( (rc_TELEGRAM=pthread_create( &thread_TELEGRAM, NULL, &urlencode, NULL)) ){
					      printf("Thread creation failed: %d\n", rc_TELEGRAM);
					      }//TELEGRAM
		    			    sleep(0.1);
					    pthread_join( thread_POLICE, NULL);
					    pthread_join( thread_STANDBY, NULL);
		    			    pthread_join( thread_TELEGRAM, NULL);
			    }
		    break;

		case '2':
			    if(num_of_hurt!=0){
			    sprintf(data, "New emergency call!!!\nTime: %s\nclient ID: %-12s \nGPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Fire", num_of_hurt_str);
			    fprintf(fp, "Time: %s\nclient ID: %-12s \nMy GPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Fire", num_of_hurt_str);
			    fclose(fp);
			    strcpy((char*)arguments[0], data);
			    strcpy((char*)arguments[1], "9040");
		           if( (rc_POLICE=pthread_create( &thread_POLICE, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_POLICE);
			    }//POLICE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9050");
		           if( (rc_AMBULANCE=pthread_create( &thread_AMBULANCE, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_AMBULANCE);
			    }//AMBULANCE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9070");
		           if( (rc_STANDBY=pthread_create( &thread_STANDBY, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_STANDBY);
			    }//STANDBY
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9060");
		           if( (rc_FIREMEN=pthread_create( &thread_FIREMEN, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_FIREMEN);
			    }//FIREMEN
		           if( (rc_TELEGRAM=pthread_create( &thread_TELEGRAM, NULL, &urlencode, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_TELEGRAM);
			      }//TELEGRAM
    			    sleep(0.1);
			    pthread_join( thread_POLICE, NULL);
			    pthread_join( thread_AMBULANCE, NULL);
			    pthread_join( thread_STANDBY, NULL);
			    pthread_join( thread_FIREMEN, NULL);
    			    pthread_join( thread_TELEGRAM, NULL);
			    }
			    else{
			    sprintf(data, "New emergency call!!!\nTime: %s\nclient ID: %-12s \nGPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : NO \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Fire", num_of_hurt_str);
			    fprintf(fp, "Time: %s\nclient ID: %-12s \nMy GPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : NO \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Fire", num_of_hurt_str);
			    fclose(fp);
			    strcpy((char*)arguments[0], data);
			    strcpy((char*)arguments[1], "9040");
		           if( (rc_POLICE=pthread_create( &thread_POLICE, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_POLICE);
			    }//POLICE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9050");
		           if( (rc_AMBULANCE=pthread_create( &thread_AMBULANCE, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_AMBULANCE);
			    }//AMBULANCE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9070");
		           if( (rc_STANDBY=pthread_create( &thread_STANDBY, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_STANDBY);
			    }//STANDBY
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9060");
		           if( (rc_FIREMEN=pthread_create( &thread_FIREMEN, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_FIREMEN);
			    }//FIREMEN
      			    sleep(0.1);
    		           if( (rc_TELEGRAM=pthread_create( &thread_TELEGRAM, NULL, &urlencode, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_TELEGRAM);
			      }//TELEGRAM
			    sleep(0.1);
			    pthread_join( thread_POLICE, NULL);
			    pthread_join( thread_AMBULANCE, NULL);
			    pthread_join( thread_STANDBY, NULL);
			    pthread_join( thread_FIREMEN, NULL);
    			    pthread_join( thread_TELEGRAM, NULL);
			    }
		    break;

		case '3':
			    if(num_of_hurt!=0){
			    sprintf(data, "New emergency call!!!\nTime: %s\nclient ID: %-12s \nGPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Break-in", num_of_hurt_str);
			    fprintf(fp, "Time: %s\nclient ID: %-12s \nMy GPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Break-in", num_of_hurt_str);
			    fclose(fp);
			    strcpy((char*)arguments[0], data);
			    strcpy((char*)arguments[1], "9040");
		           if( (rc_POLICE=pthread_create( &thread_POLICE, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_POLICE);
			    }//POLICE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9050");
		           if( (rc_AMBULANCE=pthread_create( &thread_AMBULANCE, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_AMBULANCE);
			    }//AMBULANCE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9070");
		           if( (rc_STANDBY=pthread_create( &thread_STANDBY, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_STANDBY);
			    }//STANDBY
      			    sleep(0.1);
    		           if( (rc_TELEGRAM=pthread_create( &thread_TELEGRAM, NULL, &urlencode, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_TELEGRAM);
			      }//TELEGRAM
    			    sleep(0.1);
			    pthread_join( thread_POLICE, NULL);
			    pthread_join( thread_AMBULANCE, NULL);
			    pthread_join( thread_STANDBY, NULL);
    			    pthread_join( thread_TELEGRAM, NULL);
			    }
			    else{
			    sprintf(data, "New emergency call!!!\nTime: %s\nclient ID: %-12s \nGPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : NO \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Break-in", num_of_hurt_str);
			    fprintf(fp, "Time: %s\nclient ID: %-12s \nMy GPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : NO \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Break-in", num_of_hurt_str);
			    fclose(fp);
			    strcpy((char*)arguments[0], data);
			    strcpy((char*)arguments[1], "9040");
		           if( (rc_POLICE=pthread_create( &thread_POLICE, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_POLICE);
			    }//POLICE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9070");
		           if( (rc_STANDBY=pthread_create( &thread_STANDBY, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_STANDBY);
			    }//STANDBY
      			    sleep(0.1);
    		           if( (rc_TELEGRAM=pthread_create( &thread_TELEGRAM, NULL, &urlencode, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_TELEGRAM);
			      }//TELEGRAM
    			    sleep(0.1);
			    pthread_join( thread_POLICE, NULL);
			    pthread_join( thread_STANDBY, NULL);
    			    pthread_join( thread_TELEGRAM, NULL);
			    }
		    break;

		case '4':
			    sprintf(data, "New emergency call!!!\nTime: %s\nclient ID: %-12s \nGPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Medical emergency", num_of_hurt_str);
			    fprintf(fp, "Time: %s\nclient ID: %-12s \nMy GPS coordinates is : %-30s \nProblem : %-2s \nSomeone Get hurt : YES \nHow many get hurt : %s",ctime(&t), client_ID, GPS, "Medical emergency", num_of_hurt_str);
			    fclose(fp);
			    strcpy((char*)arguments[0], data);
			    strcpy((char*)arguments[1], "9050");
		           if( (rc_AMBULANCE=pthread_create( &thread_AMBULANCE, NULL, &EME_call_func,NULL)) ){
			      printf("Thread creation failed: %d\n", rc_AMBULANCE);
			    }//AMBULANCE
      			    sleep(0.1);
			    strcpy((char*)arguments[1], "9070");
		           if( (rc_STANDBY=pthread_create( &thread_STANDBY, NULL, &EME_call_func, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_STANDBY);
			    }//STANDBY
      			    sleep(0.1);
    		           if( (rc_TELEGRAM=pthread_create( &thread_TELEGRAM, NULL, &urlencode, NULL)) ){
			      printf("Thread creation failed: %d\n", rc_TELEGRAM);
			      }//TELEGRAM
    			    sleep(0.1);
			    pthread_join( thread_AMBULANCE, NULL);
			    pthread_join( thread_STANDBY, NULL);
    			    pthread_join( thread_TELEGRAM, NULL);
		    break;

		// operator doesn't match any case constant +, -, *, /
		default:
		    printf("Error! operator is not correct");
	    }
        }
    }

}

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void* get_in_addr(struct sockaddr* sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
