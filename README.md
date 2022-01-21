# Minitalk

## Objective

The objective of this project is create two executables: client and server.

Server should be executed without arguments and print his pid.

Client should be executed with the server pid as first parameter and a message as second parameter.

Client should convert the message to binary and send to server using only SIGUSR1 and SIGUSR2.

Server should receive all the characters (or a least a part of it) before print the message.

## Bonus

The bonus part consist of the server sending a message to client to confirm that he received and printed all the message and be capable of print unicode characters.

The bonus code is in the bonus branch.

## Code style

This project should respect some code style rules:

A max of five functions per file and a max of 25 lines per function. 

The loops should be implemented using while.

Global variables aren't allowed.
