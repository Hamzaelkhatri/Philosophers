#  :monocle_face:	 Philosophers
 In this project, you will learn the basics of threading a process and how to work on the same memory space. You will learn how to make threads. You will discover the mutex, semaphore and shared memory.

# What is MultiThreads? 🧵

    Multithreading is a specialized form of multitasking
    and a multitasking is the feature that allows your computer 
    to run two or more programs concurrently.
    
 # What Are Threads? 	
    A thread is a small sequence of programmed instructions.
    Threads refer to the highest level of code your processor can execute.
  
# What The point of mutex ?

    the point of a mutex is to synchronize two threads. 
    When you have two threads attempting to access a single resource, the general pattern is to have the first block of code attempting access to set the mutex         before entering the code. 
    When the second code block attempts access, it sees that the mutex is set and waits until the first block of code is complete (and unsets the mutex),
    then  continues.
 
 # What is semaphores
 
   Semaphore is simply a variable that is non-negative and shared between threads. 
   This variable is used to solve the critical section problem and to achieve process synchronization in the multiprocessing environment. 
   
   # resources
   
   https://computing.llnl.gov/tutorials/parallel_comp/
https://computing.llnl.gov/tutorials/pthreads/
https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/
https://franckh.developpez.com/tutoriels/posix/pthreads/
http://greenteapress.com/thinkos/html/thinkos012.html
http://jean-luc.massat.perso.luminy.univ-amu.fr/ens/docs/thread-sem.html
https://timmurphy.org/2014/04/26/using-fork-in-cc-a-minimum-working-example/
https://stackoverflow.com/questions/876605/multiple-child-process
https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates
https://www.thegeekstuff.com/2012/05/c-mutex-examples/
https://www.youtube.com/watch?v=GXXE42bkqQk&ab_channel=BrianFraser
https://computing.llnl.gov/tutorials/pthreads/
