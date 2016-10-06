#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct thread {
unsigned char* stack_pointer;
void* initial_argument;
void (*initial_function) (void*);
}

long power(int, int);
void fun_with_threads();

void thread_switch(struct thread * old, struct thread * new);// step2
void thread_start(struct thread * old, stuct thread * new);// step2
void thread_wrap(); // step 2

void yield();

static const int STACK_SIZE = 1024 * 1024;
struct thread* current_thread;
struct thread* inactive_thread;
int *p = malloc(sizeof(int));
*p = 5;

int main(){

current_thread -> initial_argument = p;
current_thread -> stack_pointer = malloc(STACK_SIZE) + STACK_SIZE;
current_thread->initial_function(current_thread->initial_argument);

//thread_start(inactive_thread, current_thread);

return 0;
}

long power (int num, int pow)
{
    if (pow)
    {
        return (num * power(num, pow - 1));
    }
    return 1;
}

void fun_with_threads(void* arg){
long n = *(long*) arg;
print("%ld = %ld\n", n, power(n));
}

void thread_wrap(){ //step 2
current_thread->initial_function(current_thread->initial_argument);
yield();
}

void yield(){ //step 3
struct thread * temp = current_thread;
current_thread =  inactive_thread;
inactive_thread = temp;
thread_switch(inactive_thread, current_thread);
}

