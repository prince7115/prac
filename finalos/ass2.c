
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort function
void bubbleSort(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Display array
void display(int arr[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

// Function to demonstrate Zombie Process
void demonstrateZombie()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("\nZombie Child PID: %d\n", getpid());
        printf("Zombie child is terminating...\n");
        exit(0);
    }
    else if (pid > 0)
    {
        printf("Zombie Parent PID: %d\n", getpid());

        // Delay wait() to demonstrate zombie
        sleep(5);

        printf("Child may be in Zombie state.\n");
        printf("Check using: ps -el | grep ' Z '\n");

        wait(NULL);

        printf("Parent collected child status.\n");
        printf("Zombie process removed.\n");
    }
    else
    {
        perror("Fork failed");
    }
}

// Function to demonstrate Orphan Process
void demonstrateOrphan()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("\nOrphan Child Started\n");
        printf("Child PID: %d\n", getpid());
        printf("Initial Parent PID: %d\n", getppid());

        sleep(5);

        printf("\nAfter Parent Termination:\n");
        printf("Child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());

        printf("Orphan child completed.\n");
        exit(0);
    }
    else if (pid > 0)
    {
        printf("Orphan Parent PID: %d\n", getpid());
        printf("Parent is terminating...\n");

        exit(0);
    }
    else
    {
        perror("Fork failed");
    }
}

int main()
{
    int n, arr[100], i;
    pid_t pid;

    // Accept integers
    printf("Enter number of integers: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);

    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("\n--- CHILD PROCESS ---\n");
        printf("Child PID: %d\n", getpid());

        bubbleSort(arr, n);

        printf("Child sorted array: ");
        display(arr, n);

        exit(0);
    }
    else
    {
        // Parent process
        printf("\n--- PARENT PROCESS ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        bubbleSort(arr, n);

        printf("Parent sorted array: ");
        display(arr, n);

        // Wait for child
        wait(NULL);

        printf("\nParent: Child process completed.\n");

        // Demonstrate Zombie
        printf("\n========== ZOMBIE DEMONSTRATION ==========\n");
        demonstrateZombie();

        // Demonstrate Orphan
        printf("\n========== ORPHAN DEMONSTRATION ==========\n");
        demonstrateOrphan();
    }

    return 0;
}






















/*
================================================================
ASSIGNMENT 2: PROCESS MANAGEMENT USING SYSTEM CALLS IN C
================================================================

AIM:
To write a C program that demonstrates process creation using
fork(), execution of parent and child processes, sorting an
array using Bubble Sort, and the demonstration of Zombie and
Orphan processes in Linux.

----------------------------------------------------------------
1. INTRODUCTION
----------------------------------------------------------------

This program demonstrates the concept of process management
in a Linux operating system using C programming.

A process is a program that is currently being executed.
Every process has its own Process ID (PID), which uniquely
identifies it within the operating system.

The program performs the following operations:

1. Accepts an array of integers from the user.
2. Creates a child process using fork().
3. The child process sorts the array using Bubble Sort.
4. The parent process independently sorts the same array.
5. The parent waits for the child process to complete.
6. Demonstrates a Zombie Process.
7. Demonstrates an Orphan Process.

This program uses Linux system calls to demonstrate how
processes are created, executed, terminated and managed.

----------------------------------------------------------------
2. HEADER FILES USED
----------------------------------------------------------------

#include <stdio.h>

This header file provides standard input/output functions.

Functions used:
- printf(): Displays output on the terminal.
- scanf(): Accepts input from the user.
- perror(): Displays an error message associated with
  the last system error.

#include <stdlib.h>

This header file provides general-purpose utility functions.

Function used:
- exit(): Terminates the calling process.

#include <unistd.h>

This header file provides access to POSIX operating system
system calls.

Functions used:
- fork(): Creates a new child process.
- getpid(): Returns the PID of the calling process.
- getppid(): Returns the PID of the parent process.
- sleep(): Suspends execution for a specified number
  of seconds.

#include <sys/wait.h>

This header file provides functions for process synchronization
and management.

Function used:
- wait(): Makes the parent process wait for a child process
  to terminate and collects its termination status.

----------------------------------------------------------------
3. BUBBLE SORT FUNCTION
----------------------------------------------------------------

void bubbleSort(int arr[], int n)

Bubble Sort is a simple sorting algorithm that arranges
elements in ascending or descending order.

In this program, Bubble Sort arranges the array in ascending
order.

The algorithm repeatedly compares two adjacent elements.

If the first element is greater than the second element,
their positions are exchanged using a temporary variable.

The process continues until the entire array is sorted.

IMPORTANT VARIABLES:

i:
Controls the number of passes through the array.

j:
Controls the comparison of adjacent elements.

temp:
Temporarily stores an element during swapping.

LOGIC:

The outer loop:
for (i = 0; i < n - 1; i++)

It executes n-1 passes because an array of n elements
requires at most n-1 passes to become sorted.

The inner loop:
for (j = 0; j < n - i - 1; j++)

It compares adjacent elements.

The expression n-i-1 reduces the number of comparisons
after every pass because the largest elements are already
placed at their correct positions at the end of the array.

CONDITION:

if (arr[j] > arr[j + 1])

If the current element is greater than the next element,
they are swapped.

SWAPPING:

temp = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = temp;

A temporary variable is used to avoid losing the original
value during swapping.

EXAMPLE:

Input array:
5 2 8 1

Pass 1:
5 and 2 are swapped: 2 5 8 1
8 and 1 are swapped: 2 5 1 8

Pass 2:
5 and 1 are swapped: 2 1 5 8

Pass 3:
2 and 1 are swapped: 1 2 5 8

Sorted array:
1 2 5 8

TIME COMPLEXITY:

Best case: O(n^2) for this implementation.
Average case: O(n^2).
Worst case: O(n^2).

SPACE COMPLEXITY:
O(1), because sorting is performed in the same array
without requiring another array.

IMPORTANT:
This implementation does not use an optimized swapped flag.
Therefore, even an already sorted array requires all
outer-loop passes.

----------------------------------------------------------------
4. DISPLAY FUNCTION
----------------------------------------------------------------

void display(int arr[], int n)

This function displays all the elements of an array.

The for loop iterates from index 0 to n-1.

printf("%d ", arr[i]);

Displays each integer followed by a space.

printf("\n");

Moves the cursor to the next line after displaying the array.

The purpose of this function is to avoid writing the same
array-printing logic multiple times.

----------------------------------------------------------------
5. PROCESS CREATION USING FORK()
----------------------------------------------------------------

pid_t pid = fork();

fork() is a Linux system call used to create a new process.

The process that calls fork() is called the Parent Process.

The newly created process is called the Child Process.

After a successful fork(), both processes continue execution
from the statement immediately following the fork() call.

Both processes receive separate logical address spaces.
The child initially receives a copy of the parent's memory,
including the array and its values.

RETURN VALUES OF FORK():

fork() can return three different values:

1. pid < 0:
   Process creation failed.
   A negative value indicates an error.

2. pid == 0:
   The currently executing process is the Child Process.

3. pid > 0:
   The currently executing process is the Parent Process.
   The returned value is the PID of the newly created child.

IMPORTANT:
The return value of fork() is different in the parent and
child processes.

----------------------------------------------------------------
6. PROCESS IDENTIFICATION FUNCTIONS
----------------------------------------------------------------

getpid():

Returns the Process ID (PID) of the currently executing
process.

Example:
getpid()

getppid():

Returns the Parent Process ID (PPID) of the currently
executing process.

Example:
getppid()

PID:
A unique process identifier assigned by the operating system.

PPID:
The process identifier of the parent of the current process.

These functions help identify and distinguish parent and
child processes.

----------------------------------------------------------------
7. MAIN FUNCTION AND INPUT ACCEPTANCE
----------------------------------------------------------------

int main()

The execution of the C program begins from main().

Variables:

int n:
Stores the number of integers entered by the user.

int arr[100]:
An integer array that can store a maximum of 100 elements.

int i:
Used as a loop counter.

pid_t pid:
Stores the return value of fork().

INPUT:

printf("Enter number of integers: ");
scanf("%d", &n);

The program asks the user to enter the number of integers.

VALIDATION:

if (n <= 0 || n > 100)

This condition checks whether the entered array size is valid.

|| is the logical OR operator.

If n is less than or equal to zero OR greater than 100,
the input is rejected.

return 1 terminates the program and indicates an error.

After validation, a for loop accepts n integer values
and stores them in the array.

IMPORTANT:
The array is filled BEFORE fork() is called.

Therefore, both parent and child processes receive a copy
of the same input array when fork() executes.

----------------------------------------------------------------
8. PARENT AND CHILD PROCESS EXECUTION
----------------------------------------------------------------

pid = fork();

This statement creates a child process.

After successful execution, both parent and child processes
execute the statements following fork().

The program uses an if-else structure to distinguish them.

A) CHILD PROCESS (pid == 0)
--------------------------------

if (pid == 0)

This condition is true only in the child process.

The child performs the following operations:

1. Displays the child process information.
2. Uses getpid() to display its PID.
3. Calls bubbleSort(arr, n).
4. Sorts its own copy of the array.
5. Displays the sorted array.
6. Calls exit(0) to terminate.

IMPORTANT CONCEPT:

The child process receives a separate logical memory space.
Therefore, when the child sorts its array, the parent's
array is not modified.

Both processes can independently modify their copies
of the array.

B) PARENT PROCESS (pid > 0)
--------------------------------

If the return value of fork() is positive, execution
continues in the parent process.

The parent performs the following operations:

1. Displays the parent process information.
2. Uses getpid() to display its own PID.
3. Displays the child's PID returned by fork().
4. Calls bubbleSort(arr, n).
5. Displays its independently sorted array.
6. Calls wait(NULL) to wait for the child to terminate.

IMPORTANT:

The parent and child both execute the same Bubble Sort
function, but they work on separate copies of the array.

This demonstrates independent execution of processes.

----------------------------------------------------------------
9. WAIT() SYSTEM CALL
----------------------------------------------------------------

wait(NULL);

The wait() system call makes the parent process wait until
one of its child processes terminates.

It also collects the child's termination status.

NULL means that the program does not need to store the
child's exit status.

PURPOSE:

1. Synchronizes the parent and child processes.
2. Prevents the parent from proceeding before the child
   has terminated.
3. Collects the child's termination status.
4. Prevents a terminated child from remaining as a zombie
   after its status has been collected.

IMPORTANT:
wait(NULL) does not terminate the child.
It waits for the child to terminate.

In this program, the parent waits after displaying its
sorted array.

----------------------------------------------------------------
10. ZOMBIE PROCESS DEMONSTRATION
----------------------------------------------------------------

A Zombie Process is a process that has completed execution
but whose termination status has not yet been collected
by its parent process.

When a child process terminates, the operating system
retains a small amount of information about it, including
its PID and exit status.

This information is retained until the parent calls wait()
or another appropriate wait function.

A terminated child in this state is called a Zombie Process.

FUNCTION:

void demonstrateZombie()

The function demonstrates the creation of a zombie process.

STEP 1: CREATE A CHILD PROCESS

pid_t pid = fork();

A new child process is created.

STEP 2: CHILD PROCESS

if (pid == 0)

The child displays its PID using getpid().

It then executes:

exit(0);

The child terminates successfully.

STEP 3: PARENT PROCESS

else if (pid > 0)

The parent displays its own PID.

STEP 4: DELAY USING SLEEP()

sleep(5);

The parent pauses execution for five seconds.

During this time, the child has already terminated,
but the parent has not yet collected its exit status.

Therefore, the child can remain in the Zombie state.

STEP 5: CHECK ZOMBIE STATUS

The program displays the following command:

ps -el | grep ' Z '

This Linux command can be executed in another terminal
to check for processes in the zombie state.

ps:
Displays information about running and terminated processes.

-el:
Displays a detailed process listing.

|:
The pipe operator sends the output of the ps command
to the grep command.

grep ' Z ':
Searches for process entries containing the Z state.

Z:
Represents a Zombie process.

STEP 6: COLLECT CHILD STATUS

wait(NULL);

The parent calls wait() to collect the child's termination
status.

After the status is collected, the zombie entry is removed.

IMPORTANT:
A zombie is not actively executing. It has already terminated.
Only a small process-table entry remains until its status
is collected.

----------------------------------------------------------------
11. ORPHAN PROCESS DEMONSTRATION
----------------------------------------------------------------

An Orphan Process is a process whose parent process has
terminated while the child process is still executing.

When a parent terminates before its child, the operating
system adopts the orphaned child through the init process
or another designated system process.

On many modern Linux systems, this is systemd (PID 1),
although another subreaper process may adopt it.

FUNCTION:

void demonstrateOrphan()

This function demonstrates how a child process becomes
an orphan when its parent terminates first.

STEP 1: CREATE A CHILD PROCESS

pid_t pid = fork();

The fork() system call creates a new child process.

STEP 2: CHILD PROCESS

if (pid == 0)

The child displays:

- Its own PID using getpid().
- Its initial parent's PID using getppid().

STEP 3: CHILD SLEEPS

sleep(5);

The child process pauses for five seconds.

This delay allows the parent process to terminate first.

STEP 4: PARENT PROCESS TERMINATES

else if (pid > 0)

The parent displays its own PID and a termination message.

It then executes:

exit(0);

This terminates the parent process without waiting for
the child.

STEP 5: CHILD BECOMES ORPHAN

The child is still sleeping when its parent terminates.

Therefore, it becomes an orphan process.

After waking up, the child displays:

- Its own PID again.
- Its new parent PID using getppid().

The new PPID generally identifies the process that adopted
the orphan.

STEP 6: CHILD TERMINATES

The child displays a completion message and executes:

exit(0);

This terminates the child process.

IMPORTANT DIFFERENCE:

Zombie Process:
The child has terminated, but its parent has not collected
its exit status.

Orphan Process:
The parent has terminated, but the child is still executing.

----------------------------------------------------------------
12. ERROR HANDLING
----------------------------------------------------------------

if (pid < 0)

This condition checks whether fork() failed.

If process creation fails, the program executes:

perror("Fork failed");

perror() displays the specified error message along with
a description of the system error.

The program then returns 1 or follows the appropriate
error-handling path.

----------------------------------------------------------------
13. IMPORTANT SYSTEM CALLS USED
----------------------------------------------------------------

1. fork()
   Creates a new child process.

2. getpid()
   Returns the PID of the current process.

3. getppid()
   Returns the PPID of the current process.

4. wait()
   Waits for a child process to terminate and collects
   its termination status.

5. sleep()
   Suspends the execution of a process for a specified
   number of seconds.

6. exit()
   Terminates the calling process.

----------------------------------------------------------------
14. DIFFERENCE BETWEEN PARENT AND CHILD PROCESS
----------------------------------------------------------------

Parent Process:
- It is the process that calls fork().
- fork() returns the child's PID to the parent.
- It has its own PID.
- It can create and manage child processes.
- In this program, it sorts the array and waits for the child.

Child Process:
- It is created using fork().
- fork() returns 0 in the child.
- It has its own PID.
- It initially receives a copy of the parent's memory.
- In this program, it independently sorts the array.

----------------------------------------------------------------
15. DIFFERENCE BETWEEN ZOMBIE AND ORPHAN PROCESS
----------------------------------------------------------------

Zombie Process:
- The child process has already terminated.
- Its parent is still alive in the normal demonstration.
- The parent has not collected its termination status.
- A process-table entry remains until it is collected.

Orphan Process:
- The parent process has terminated.
- The child process is still executing.
- The child is adopted by another process.
- The child continues its execution normally.

----------------------------------------------------------------
16. OVERALL EXECUTION FLOW
----------------------------------------------------------------

1. Program execution starts from main().

2. The user enters the number of integers.

3. The program validates the array size.

4. The user enters the array elements.

5. fork() creates a child process.

6. The child sorts and displays its copy of the array.

7. The parent independently sorts and displays its copy.

8. The parent calls wait(NULL) to collect the child status.

9. The program calls demonstrateZombie().

10. A child terminates, and the parent delays calling wait().

11. The child temporarily enters the Zombie state.

12. The parent calls wait(NULL) and collects the child status.

13. The program calls demonstrateOrphan().

14. A new child is created.

15. The parent terminates using exit(0).

16. The child continues executing and becomes an orphan.

17. The child displays its new PPID and terminates.

18. The program completes execution.

----------------------------------------------------------------
17. ADVANTAGES
----------------------------------------------------------------

1. Demonstrates process creation and management.
2. Explains the relationship between parent and child processes.
3. Demonstrates independent execution using fork().
4. Helps understand process synchronization using wait().
5. Demonstrates Zombie and Orphan processes.
6. Uses Bubble Sort to demonstrate computation in
   independently executing processes.
7. Introduces important Linux system calls.

----------------------------------------------------------------
18. LIMITATIONS
----------------------------------------------------------------

1. Bubble Sort is inefficient for large datasets.
2. The program supports a maximum of 100 integers.
3. Both processes independently perform the same sorting
   operation, so there is no reduction in sorting work.
4. No shared memory or inter-process communication is used.
5. The program does not check the return value of every
   input operation.
6. The five-second sleep provides an observation window,
   but does not guarantee exact scheduling or output timing.
7. Zombie visibility through ps depends on checking during
   the short period before wait() executes.

================================================================
END OF ASSIGNMENT EXPLANATION
================================================================
*/
