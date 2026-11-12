
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

// Counting semaphores
sem_t empty, full;

// Mutex for mutual exclusion
pthread_mutex_t mutex;

// Producer function
void* producer(void* arg)
{
    int item;

    for (int i = 1; i <= 10; i++)
    {
        item = i;

        sem_wait(&empty);  // Wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = item;

        printf("Producer produced: %d\n", item);

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);   // Increase full slots

        sleep(1);
    }

    return NULL;
}

// Consumer function
void* consumer(void* arg)
{
    int item;

    for (int i = 1; i <= 10; i++)
    {
        sem_wait(&full);   // Wait for available item
        pthread_mutex_lock(&mutex);

        item = buffer[out];

        printf("Consumer consumed: %d\n", item);

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  // Increase empty slots

        sleep(2);
    }

    return NULL;
}

int main()
{
    pthread_t p, c;

    // Initialize semaphores
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    // Wait for both threads
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    // Destroy synchronization variables
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
















/*
================================================================
ASSIGNMENT 3: PRODUCER-CONSUMER PROBLEM USING THREADS,
              SEMAPHORES AND MUTEX LOCKS
================================================================

AIM:
To implement the Producer-Consumer problem using POSIX threads,
counting semaphores and mutex locks in C.

The program demonstrates synchronization between two threads
sharing a common bounded buffer.

----------------------------------------------------------------
1. INTRODUCTION
----------------------------------------------------------------

The Producer-Consumer problem is a classical synchronization
problem in Operating Systems.

It involves two types of processes or threads:

1. Producer:
   Generates data items and places them into a shared buffer.

2. Consumer:
   Removes data items from the shared buffer and processes them.

Both producer and consumer access the same shared buffer.

This creates synchronization problems because both threads
may attempt to access or modify the buffer simultaneously.

The program uses:
- POSIX Threads (Pthreads)
- Counting Semaphores
- Mutex Locks
- Circular Buffer

The buffer has a maximum capacity of 5 elements.

The producer generates 10 items, from 1 to 10.
The consumer consumes all 10 items.

----------------------------------------------------------------
2. HEADER FILES USED
----------------------------------------------------------------

#include <stdio.h>

Provides standard input/output functions.

Function used:
- printf(): Displays messages on the terminal.

#include <pthread.h>

Provides functions for creating and managing threads.

Functions used:
- pthread_create(): Creates a new thread.
- pthread_join(): Waits for a thread to complete.
- pthread_mutex_init(): Initializes a mutex.
- pthread_mutex_lock(): Locks a mutex.
- pthread_mutex_unlock(): Unlocks a mutex.
- pthread_mutex_destroy(): Destroys a mutex.

#include <semaphore.h>

Provides semaphore-related functions.

Functions used:
- sem_t: Semaphore data type.
- sem_init(): Initializes a semaphore.
- sem_wait(): Decreases a semaphore value or waits.
- sem_post(): Increases a semaphore value.
- sem_destroy(): Destroys a semaphore.

#include <unistd.h>

Provides access to POSIX operating system functions.

Function used:
- sleep(): Suspends execution for a specified number
  of seconds.

----------------------------------------------------------------
3. BUFFER SIZE AND SHARED VARIABLES
----------------------------------------------------------------

#define SIZE 5

A preprocessor macro defines the buffer capacity as 5.

This means the buffer can hold a maximum of five items
at any given time.

int buffer[SIZE];

This declares an integer array that acts as the shared buffer.

Both producer and consumer threads access this array.

int in = 0, out = 0;

These variables maintain the positions at which items are
inserted and removed.

in:
Indicates the next position where the producer will insert
an item.

out:
Indicates the next position from which the consumer will
remove an item.

Initially, both are set to zero because the buffer is empty.

IMPORTANT:
The buffer, in and out are global variables.
Therefore, they are accessible to both threads.

----------------------------------------------------------------
4. SEMAPHORES
----------------------------------------------------------------

sem_t empty, full;

These are counting semaphores used to control access to
available and occupied buffer positions.

A semaphore is a synchronization mechanism that maintains
an integer value and allows threads to coordinate their
execution.

The program uses two counting semaphores:

A) EMPTY SEMAPHORE
------------------

sem_t empty;

It represents the number of empty slots available in the
buffer.

Initially:

sem_init(&empty, 0, SIZE);

Since SIZE = 5, the initial value of empty is 5.

This means all five positions are initially empty.

Whenever the producer inserts an item, the empty semaphore
is decreased.

Whenever the consumer removes an item, the empty semaphore
is increased.

B) FULL SEMAPHORE
-----------------

sem_t full;

It represents the number of occupied slots in the buffer.

Initially:

sem_init(&full, 0, 0);

Its initial value is zero because the buffer contains
no items at the beginning.

Whenever the producer inserts an item, full is increased.

Whenever the consumer removes an item, full is decreased.

IMPORTANT SEMAPHORE OPERATIONS:

sem_wait():
Decreases the semaphore value by one if it is positive.
If the value is zero, the calling thread blocks until
the semaphore becomes available.

sem_post():
Increases the semaphore value by one and may wake up
a waiting thread.

----------------------------------------------------------------
5. MUTEX LOCK
----------------------------------------------------------------

pthread_mutex_t mutex;

A mutex stands for Mutual Exclusion.

It is a synchronization mechanism that ensures only one
thread at a time can execute a critical section protected
by that mutex.

The producer and consumer both access the shared buffer
and its index variables.

Without proper synchronization, simultaneous access could
cause race conditions.

The mutex prevents both threads from modifying the shared
buffer at the same time.

IMPORTANT OPERATIONS:

pthread_mutex_init(&mutex, NULL);

Initializes the mutex with default attributes.

pthread_mutex_lock(&mutex);

Locks the mutex.

If another thread already holds the mutex, the calling
thread waits until it becomes available.

pthread_mutex_unlock(&mutex);

Unlocks the mutex so another thread can acquire it.

pthread_mutex_destroy(&mutex);

Destroys the mutex after it is no longer required.

----------------------------------------------------------------
6. PRODUCER FUNCTION
----------------------------------------------------------------

void* producer(void* arg)

This is the function executed by the producer thread.

The return type is void* because POSIX thread functions
are designed to return a pointer.

The argument type is also void* so that the function can
receive a pointer to any data type.

In this program, no argument is passed, so arg is unused.

int item;

A local variable used to store the item produced by
the producer thread.

LOOP:

for (int i = 1; i <= 10; i++)

The producer generates ten items, starting from 1 and
ending at 10.

item = i;

Assigns the current loop value to the item variable.

STEP 1: WAIT FOR AN EMPTY SLOT

sem_wait(&empty);

The producer checks whether an empty buffer position
is available.

If empty is zero, the producer blocks until the consumer
removes an item and increases the empty semaphore.

This prevents BUFFER OVERFLOW.

STEP 2: ACQUIRE MUTEX

pthread_mutex_lock(&mutex);

The producer acquires the mutex before accessing the
shared buffer.

This ensures that the consumer cannot simultaneously
modify the shared buffer.

STEP 3: INSERT ITEM

buffer[in] = item;

The produced item is inserted into the buffer at the
position indicated by in.

STEP 4: DISPLAY PRODUCED ITEM

printf("Producer produced: %d\n", item);

Displays the item produced by the producer thread.

STEP 5: UPDATE BUFFER INDEX

in = (in + 1) % SIZE;

Updates the insertion position.

The modulo operator (%) makes the buffer circular.

For SIZE = 5, the index moves as follows:

0 -> 1 -> 2 -> 3 -> 4 -> 0

When the index reaches the last position, it returns
to the first position.

This allows the program to reuse buffer positions.

STEP 6: RELEASE MUTEX

pthread_mutex_unlock(&mutex);

Releases the mutex so that another thread can access
the shared buffer.

STEP 7: SIGNAL AVAILABLE ITEM

sem_post(&full);

Increases the full semaphore because one more item
has been inserted into the buffer.

This can wake up the consumer if it is waiting.

STEP 8: DELAY

sleep(1);

The producer pauses for one second before producing
the next item.

This delay makes the interaction between the producer
and consumer easier to observe.

STEP 9: RETURN

return NULL;

Indicates that the producer thread has completed its work.

----------------------------------------------------------------
7. CONSUMER FUNCTION
----------------------------------------------------------------

void* consumer(void* arg)

This function is executed by the consumer thread.

It removes items from the shared buffer.

int item;

A local variable used to temporarily store the consumed item.

LOOP:

for (int i = 1; i <= 10; i++)

The consumer consumes ten items.

STEP 1: WAIT FOR AN AVAILABLE ITEM

sem_wait(&full);

The consumer checks whether the buffer contains an item.

If full is zero, the consumer blocks until the producer
inserts an item and increases the full semaphore.

This prevents BUFFER UNDERFLOW.

STEP 2: ACQUIRE MUTEX

pthread_mutex_lock(&mutex);

The consumer locks the mutex before accessing the shared
buffer.

This prevents simultaneous modification of shared data.

STEP 3: REMOVE ITEM

item = buffer[out];

The item at the position indicated by out is copied
into the local variable item.

STEP 4: DISPLAY CONSUMED ITEM

printf("Consumer consumed: %d\n", item);

Displays the item removed from the buffer.

STEP 5: UPDATE BUFFER INDEX

out = (out + 1) % SIZE;

Moves the consumer index to the next buffer position.

The modulo operator ensures that the index returns to
zero after reaching the last position.

STEP 6: RELEASE MUTEX

pthread_mutex_unlock(&mutex);

Unlocks the mutex and allows the producer to access
the shared buffer.

STEP 7: SIGNAL EMPTY SLOT

sem_post(&empty);

Increases the empty semaphore because one buffer position
has become available.

This can wake up a producer that is waiting for space.

STEP 8: DELAY

sleep(2);

The consumer pauses for two seconds before consuming
the next item.

The consumer is intentionally slower than the producer.

This helps demonstrate how synchronization controls
the buffer when the producer generates items faster
than the consumer consumes them.

STEP 9: RETURN

return NULL;

Indicates that the consumer thread has completed its work.

----------------------------------------------------------------
8. CIRCULAR BUFFER
----------------------------------------------------------------

A circular buffer is a fixed-size buffer in which the
last position connects back to the first position.

It uses two indexes:

in:
Used by the producer to insert items.

out:
Used by the consumer to remove items.

The following expression is used:

index = (index + 1) % SIZE;

For SIZE = 5:

If index = 0, next index = 1.
If index = 1, next index = 2.
If index = 2, next index = 3.
If index = 3, next index = 4.
If index = 4, next index = 0.

The modulo operator prevents the index from going
outside the array boundaries.

ADVANTAGES:

1. Reuses available buffer positions.
2. Does not require shifting array elements.
3. Provides efficient insertion and deletion.
4. Uses a fixed amount of memory.

----------------------------------------------------------------
9. MAIN FUNCTION
----------------------------------------------------------------

int main()

Program execution begins from main().

pthread_t p, c;

Declares two thread identifiers.

p:
Stores the identifier of the producer thread.

c:
Stores the identifier of the consumer thread.

----------------------------------------------------------------
10. INITIALIZATION OF SEMAPHORES
----------------------------------------------------------------

sem_init(&empty, 0, SIZE);

Initializes the empty semaphore with a value of 5.

Parameters:

1. &empty:
   Address of the semaphore being initialized.

2. 0:
   Indicates that the semaphore is shared between threads
   of the same process rather than between processes.

3. SIZE:
   Initial semaphore value, which is 5.

sem_init(&full, 0, 0);

Initializes the full semaphore with a value of zero.

The buffer is initially empty, so there are no full slots.

----------------------------------------------------------------
11. INITIALIZATION OF MUTEX
----------------------------------------------------------------

pthread_mutex_init(&mutex, NULL);

Initializes the mutex using default attributes.

The mutex is used to protect the shared buffer and
the insertion and removal indexes.

----------------------------------------------------------------
12. THREAD CREATION
----------------------------------------------------------------

pthread_create(&p, NULL, producer, NULL);

Creates the producer thread.

Parameters:

1. &p:
   Stores the ID of the newly created thread.

2. NULL:
   Uses default thread attributes.

3. producer:
   Specifies the function that the thread will execute.

4. NULL:
   No argument is passed to the producer function.

pthread_create(&c, NULL, consumer, NULL);

Creates the consumer thread in the same manner.

Both threads execute concurrently within the same process.

Unlike fork(), pthread_create() creates a new thread
rather than a separate process.

Threads share the process's global memory and resources,
which allows them to communicate through the shared buffer.

----------------------------------------------------------------
13. THREAD SYNCHRONIZATION USING PTHREAD_JOIN
----------------------------------------------------------------

pthread_join(p, NULL);

Makes the main thread wait until the producer thread
has completed execution.

pthread_join(c, NULL);

Makes the main thread wait until the consumer thread
has completed execution.

NULL indicates that the return value of the thread
is not required.

PURPOSE:

1. Prevents the main function from finishing too early.
2. Ensures that both threads complete their work.
3. Allows synchronization between the main thread
   and the worker threads.

----------------------------------------------------------------
14. DESTROYING SYNCHRONIZATION VARIABLES
----------------------------------------------------------------

After both threads have completed, synchronization
objects are destroyed.

sem_destroy(&empty);

Destroys the empty semaphore.

sem_destroy(&full);

Destroys the full semaphore.

pthread_mutex_destroy(&mutex);

Destroys the mutex.

Destroying synchronization variables releases the
resources associated with them.

They should only be destroyed after they are no longer
being used by any thread.

----------------------------------------------------------------
15. WHY BOTH SEMAPHORES AND MUTEX ARE REQUIRED
----------------------------------------------------------------

Semaphores and mutex locks perform different jobs.

SEMAPHORES:

The empty and full semaphores control the number of
available and occupied buffer positions.

They prevent:

- Buffer overflow.
- Buffer underflow.

MUTEX:

The mutex protects the critical section.

It prevents the producer and consumer from accessing
and modifying shared buffer data simultaneously.

Therefore:

Semaphores control WHEN a thread can proceed based on
buffer availability.

Mutex controls WHO can access the critical section
at a particular time.

Both are necessary for correct synchronization.

----------------------------------------------------------------
16. IMPORTANT OPERATING SYSTEM CONCEPTS
----------------------------------------------------------------

THREAD:

A thread is the smallest unit of CPU execution within
a process.

MULTITHREADING:

The execution of multiple threads within the same process.

CONCURRENCY:

Multiple tasks make progress during overlapping periods.

RACE CONDITION:

A situation in which the result depends on the timing
or order of execution of multiple threads accessing
shared data.

CRITICAL SECTION:

A part of the program where shared resources are accessed
or modified.

MUTUAL EXCLUSION:

Ensures that only one thread at a time enters a protected
critical section.

BUFFER OVERFLOW:

Occurs when the producer attempts to insert an item
into a full buffer.

BUFFER UNDERFLOW:

Occurs when the consumer attempts to remove an item
from an empty buffer.

DEADLOCK:

A situation in which two or more threads wait indefinitely
for resources held by each other.

----------------------------------------------------------------
17. EXPECTED EXECUTION
----------------------------------------------------------------

Initial conditions:

Buffer capacity = 5
Empty slots = 5
Full slots = 0

Producer:
Produces items 1 to 10.
Waits for an empty slot before inserting.

Consumer:
Consumes items 1 to 10.
Waits for an available item before removing.

The producer sleeps for 1 second after producing an item.

The consumer sleeps for 2 seconds after consuming an item.

Because the producer is faster, it may fill the buffer
and then block until the consumer creates an empty slot.

The consumer may also block whenever the buffer is empty.

The semaphores and mutex coordinate both threads to ensure
that all ten items are produced and consumed correctly.

IMPORTANT:
The exact interleaving of producer and consumer output
is not guaranteed because the operating system scheduler
controls thread execution.

----------------------------------------------------------------
18. ADVANTAGES
----------------------------------------------------------------

1. Demonstrates multithreading in C.
2. Explains synchronization between concurrent threads.
3. Prevents buffer overflow and underflow.
4. Uses mutex locks to prevent race conditions.
5. Uses semaphores to coordinate producer and consumer.
6. Implements an efficient circular buffer.
7. Demonstrates practical operating system concepts.

----------------------------------------------------------------
19. LIMITATIONS
----------------------------------------------------------------

1. The buffer size is fixed at five elements.
2. The producer always generates exactly ten items.
3. The consumer always consumes exactly ten items.
4. No user input is accepted for the produced items.
5. Thread creation and synchronization return values
   are not checked in this implementation.
6. sleep() introduces artificial delays.
7. The program uses a single producer and a single consumer.

================================================================
END OF ASSIGNMENT EXPLANATION
================================================================
*/
