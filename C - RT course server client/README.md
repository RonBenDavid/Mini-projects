Autor:Ron ben david

An emergency center project based on a client-server includes sending a message in Telegram and to all emergency services according to priority,
That I work on "REAL TIME SYSTEMS" course where I got excellent project and a score of 100.
*Include using Raspberry pi in comments for future development

To compile:

compile server: "gcc server.c -o server -lpthread"
compile client: "gcc client.c -o client -lm"
compile police: "gcc police.c -o police"
compile mada: "gcc ambulance.c -o ambulance"
compile firemen: "gcc firemen.c -o firemen"
compile standby: "gcc standby.c -o standby"

Note:
*telegram use urlencoding function and curl api
need to use terminal command to download curl "sudo apt-get install curl"

TO SEND MESSAGE TO TELEGRAM CHAT EDIT DEFINE IN SERVER.c:

#define TELEGRAM_BOT_TOKEN "ENTER YOUR BOT TOKEN"
#define TELEGRAM_CHAT_ID "ENTER YOUR CHAT ID"

To run:
./server
./client localhost
./police
./mada
./firemen
./standby



API LIST:
*(argc, argv)

*null terminated strings, fot example: strcat(3), strstr(3), strchar(3), strtok(3) etc.

*FILE API (fread, fwrite, fopen etc.)

*read וwrite.

*IPv4.

*IPv6.

*Stream sockets 

*Datagram sockets 

*IP multiplexing - select

*poll 

*fork(2), wait(2)

*Pthereds -lpthread

*SIGNALS

*MATH LIBERY USING LINK -lm.

Extras not listed in the requirements:


*TIME

*GPS

*LED

*TELEGRAM
