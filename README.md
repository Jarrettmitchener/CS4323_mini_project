# CS4323_mini_project
Operating Systems mini group project
Group c

Jarrett Mitchener
Caleb Newport
Cameron stalcup
Keenan Holsapple

To run the the server file, use
gcc Server.c -o Server
./Server

To run the client file, use
gcc Client.c -o Client
./Client

--------------Other program information------------------------

This program is a basic TCP server client word game that uses fork()
to deal with multiple connections to the server rather than multithreading.
Players can either play in singleplayer or multiplayer.
Singleplayer is against a computer.
seperate scoreboards for multiplayer and singleplayer.
Uses a dictionary text file and input text files to determine if 
a word is correct and uses the scrambled letters in the input files.

The server is the main hub for the other program files besides the client,
as the client does no actual processing for the game or text files, it 
is just designed to recieve input from the server and act accordingly.
The server and client have a variable named "delay" which is used to 
delay the send calls between them, as at least on my computer if there
was no delay then it would often break the program. not sure if this is
a gcc, socket, or cpu problem, possibly cpu since I run an amd 3600X 
and I've had weird issues like this before with code time and streams.
CSX does still have the same issues but seemingly less often, so for
consistency after each send the progam waits for x microseconds, and
x microseconds is set to the "delay" variable.

If you're interested, heres the github we used, note that is a little bare
https://github.com/Jarrettmitchener/CS4323_mini_project

