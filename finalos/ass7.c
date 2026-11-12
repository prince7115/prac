
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;

    char filename[100];
    char buffer[1024];
    int fd, n;

    // Create two pipes
    pipe(pipe1);
    pipe(pipe2);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    // Parent Process
    if (pid > 0)
    {
        close(pipe1[0]); // Close reading end of pipe1
        close(pipe2[1]); // Close writing end of pipe2

        printf("Enter file name: ");
        scanf("%99s", filename);

        // Send filename to child
        write(pipe1[1], filename, strlen(filename) + 1);

        close(pipe1[1]);

        printf("\nContents of file:\n");

        // Read file contents from child
        while ((n = read(pipe2[0], buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, n);
        }

        close(pipe2[0]);

        wait(NULL);
    }

    // Child Process
    else
    {
        close(pipe1[1]); // Close writing end of pipe1
        close(pipe2[0]); // Close reading end of pipe2

        // Read filename from parent
        read(pipe1[0], filename, sizeof(filename));

        close(pipe1[0]);

        // Open the file
        fd = open(filename, O_RDONLY);

        if (fd < 0)
        {
            char msg[] = "Error: Unable to open file.\n";
            write(pipe2[1], msg, strlen(msg));
        }
        else
        {
            // Read file and send contents to parent
            while ((n = read(fd, buffer, sizeof(buffer))) > 0)
            {
                write(pipe2[1], buffer, n);
            }

            close(fd);
        }

        close(pipe2[1]);
        exit(0);
    }

    return 0;
}





























/*
==========================================================
       ASSIGNMENT 7: IPC USING TWO PIPES
==========================================================

AIM:
To implement inter-process communication between a
parent and child process using two pipes.

The parent sends a filename to the child process.
The child opens the file, reads its contents and sends
the contents back to the parent process.

----------------------------------------------------------
1. WHAT IS IPC?
----------------------------------------------------------

IPC stands for Inter-Process Communication.

It is a mechanism that allows two or more processes
to exchange information.

Processes normally have separate memory spaces.
Therefore, IPC mechanisms are used when they need
to communicate.

Examples of IPC:
1. Pipes
2. Message Queues
3. Shared Memory
4. Semaphores
5. Sockets

This program uses pipes for communication.

----------------------------------------------------------
2. WHAT IS A PIPE?
----------------------------------------------------------

A pipe is an IPC mechanism that allows data to flow
from one process to another.

A pipe has two ends:

1. Reading end  - receives data.
2. Writing end  - sends data.

A pipe is generally unidirectional.

This program creates two pipes to enable
communication in both directions.

----------------------------------------------------------
3. HEADER FILES
----------------------------------------------------------

#include <stdio.h>

Provides printf() and scanf().

#include <stdlib.h>

Provides exit().

#include <unistd.h>

Provides pipe(), fork(), read(), write() and close().

#include <sys/types.h>

Provides system data types such as pid_t.

#include <sys/wait.h>

Provides wait() to wait for child process termination.

#include <string.h>

Provides strlen() to calculate string length.

#include <fcntl.h>

Provides file opening flags such as O_RDONLY.

----------------------------------------------------------
4. DECLARING VARIABLES
----------------------------------------------------------

int pipe1[2], pipe2[2];

Two pipes are declared.

pipe1 is used for communication from parent to child.

pipe2 is used for communication from child to parent.

pid_t pid;

Stores the process ID returned by fork().

char filename[100];

Stores the filename entered by the user.

char buffer[1024];

Temporarily stores data read from the file.

int fd, n;

fd stores the file descriptor returned by open().

n stores the number of bytes returned by read().

----------------------------------------------------------
5. CREATING TWO PIPES
----------------------------------------------------------

pipe(pipe1);
pipe(pipe2);

The program creates two pipes.

Each pipe contains two file descriptors:

pipe[0] = Reading end
pipe[1] = Writing end

Communication direction:

PIPE 1:
Parent -> Child

PIPE 2:
Child -> Parent

This allows two-way communication using two
unidirectional pipes.

----------------------------------------------------------
6. CREATING CHILD PROCESS
----------------------------------------------------------

pid = fork();

fork() creates a new child process.

It returns:

Positive value: Executed in parent; value is child PID.
Zero: Executed in child process.
Negative value: Process creation failed.

if(pid < 0)

Checks whether fork() failed.

----------------------------------------------------------
7. PARENT PROCESS
----------------------------------------------------------

if(pid > 0)

This block executes in the parent process.

The parent first closes unused pipe ends:

close(pipe1[0]);

Closes the reading end of pipe1 because the parent
only sends data through this pipe.

close(pipe2[1]);

Closes the writing end of pipe2 because the parent
only receives data through this pipe.

----------------------------------------------------------
8. ACCEPTING FILENAME
----------------------------------------------------------

printf("Enter file name: ");
scanf("%99s", filename);

The parent asks the user to enter a filename.

The filename is stored in the filename array.

The %99s format limits input to 99 characters,
leaving space for the terminating null character.

----------------------------------------------------------
9. SENDING FILENAME TO CHILD
----------------------------------------------------------

write(pipe1[1], filename, strlen(filename) + 1);

The parent sends the filename through pipe1.

strlen(filename) calculates the number of characters.

+1 includes the null character '\0'.

This helps the child receive the complete filename
as a C string.

After sending the filename:

close(pipe1[1]);

The parent closes its writing end of pipe1.

----------------------------------------------------------
10. RECEIVING FILE CONTENTS
----------------------------------------------------------

The parent displays:

Contents of file:

It then executes:

while ((n = read(pipe2[0], buffer, sizeof(buffer))) > 0)

The parent reads data from pipe2.

read() returns the number of bytes received.

The loop continues until read() returns 0,
indicating that the writing end of the pipe has
been closed and all data has been read.

write(STDOUT_FILENO, buffer, n);

Displays the received file contents on the terminal.

STDOUT_FILENO represents standard output,
which is normally the terminal.

After receiving all data:

close(pipe2[0]);

The parent closes the reading end.

wait(NULL);

The parent waits for the child process to terminate.

----------------------------------------------------------
11. CHILD PROCESS
----------------------------------------------------------

else

This block executes in the child process.

The child closes unused pipe ends:

close(pipe1[1]);

The child does not send data through pipe1.

close(pipe2[0]);

The child does not receive data through pipe2.

----------------------------------------------------------
12. RECEIVING FILENAME
----------------------------------------------------------

read(pipe1[0], filename, sizeof(filename));

The child receives the filename sent by the parent.

The filename is stored in its filename array.

The child then closes the reading end of pipe1.

----------------------------------------------------------
13. OPENING FILE
----------------------------------------------------------

fd = open(filename, O_RDONLY);

The child opens the specified file in read-only mode.

O_RDONLY means the file can only be read.

If open() returns a negative value, the file
could not be opened.

----------------------------------------------------------
14. ERROR HANDLING
----------------------------------------------------------

if(fd < 0)

Checks whether opening the file failed.

If the file cannot be opened, the child creates
an error message:

Error: Unable to open file.

The message is sent to the parent using write().

----------------------------------------------------------
15. READING FILE CONTENTS
----------------------------------------------------------

If the file opens successfully, the child reads
its contents using:

while ((n = read(fd, buffer, sizeof(buffer))) > 0)

The file is read in chunks of up to 1024 bytes.

The loop continues until the entire file is read.

----------------------------------------------------------
16. SENDING FILE CONTENTS TO PARENT
----------------------------------------------------------

write(pipe2[1], buffer, n);

The child sends the contents it has read through
pipe2.

The parent receives these contents and displays
them on the terminal.

After reading the complete file:

close(fd);

Closes the opened file.

----------------------------------------------------------
17. CLOSING PIPE AND TERMINATING CHILD
----------------------------------------------------------

close(pipe2[1]);

The child closes the writing end of pipe2.

This is important because the parent detects the
end of input when all writing ends are closed.

exit(0);

Terminates the child process successfully.

----------------------------------------------------------
18. OVERALL WORKING
----------------------------------------------------------

STEP 1:
Two pipes are created.

STEP 2:
fork() creates a child process.

STEP 3:
The parent accepts a filename.

STEP 4:
The parent sends the filename through pipe1.

STEP 5:
The child receives the filename.

STEP 6:
The child opens the file in read-only mode.

STEP 7:
The child reads the file contents.

STEP 8:
The child sends the contents through pipe2.

STEP 9:
The parent receives and displays the contents.

STEP 10:
Both processes close their respective file
descriptors and the parent waits for the child.

----------------------------------------------------------
19. CONCLUSION
----------------------------------------------------------

Thus, inter-process communication was implemented
using two pipes in C.

The parent process sends a filename to the child
process, and the child reads the specified file
and sends its contents back to the parent.

==========================================================
*/
