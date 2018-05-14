/* HEADER : Operating System Hw3
 * AUTHOR : Muhammed YILMAZ
 * DATE   : 08.05.2018
 * E-MAIL : yilmazmu15@itu.edu.tr
 */

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEMKEY_LOCK 1
#define SEMKEY_FILLWATER 2
#define SHMKEY_WATERLEVEL 3
#define SEMKEY_TURN 4
#define SEMKEY_EMPTYWATER 5

void mysigset(int num);
void mysignal(int signum);
void sem_wait(int semid, int val);
void sem_signal(int semid, int val);
int read_file(int *localMaxWater, int orderList[]);	
int order_number();

char *fileName;

int main(int argc, char *argv[])
{
	mysigset(12);

	/*********** READ FILE AND LEARN NECESSARY INFORMATION - START ***********/
	fileName = argv[1];

	int localMaxWater = 0, *orderList, orderNumber = 0;
	orderNumber = order_number();
	orderList = (int*) malloc(sizeof(int) * (orderNumber + 1));
	if(!read_file(&localMaxWater, orderList))
		return -1;
	/*********** READ FILE AND LEARN NECESSARY INFORMATION - FINISH **********/

	/*********************** CREATE SEMAPHORES - START ***********************/
	// Theese are semaphore ids and share memory area id
	int lockSemId, fillWaterSemId, turnSemId, emptyWaterId;
	int waterLevelShmId;
	// These shared variable
	int *globalWaterLevel;

	// creating a semaphore for mutual exlusion between employee processes
	lockSemId = semget(SEMKEY_LOCK, 1, 0700|IPC_CREAT);
	semctl(lockSemId, 0, SETVAL, 1);		// value = 1

	// creating a semaphore for mutual exlusion between 
	fillWaterSemId = semget(SEMKEY_FILLWATER, 1, 0700|IPC_CREAT);
	semctl(fillWaterSemId, 0, SETVAL, 0);	// value = 0

	// creating a semaphore for mutual exlusion between 
	turnSemId = semget(SEMKEY_TURN, 1, 0700|IPC_CREAT);
	semctl(turnSemId, 0, SETVAL, 0);	// value = 0

	// creating a semaphore for mutual exlusion between 
	emptyWaterId = semget(SEMKEY_EMPTYWATER, 1, 0700|IPC_CREAT);
	semctl(emptyWaterId, 0, SETVAL, 0);	// value = 0

	// creating a shared memory area with the size of an int
	waterLevelShmId = shmget(SHMKEY_WATERLEVEL, sizeof(int), 0700|IPC_CREAT);
	/*********************** CREATE SEMAPHORES - FINISH **********************/

	/************************* CREATE PROCESS - START ************************/
	// Theese are necessary for creating processes 
	int i, myOrder, myCoffeType;
	int f;
	int *localChildren = (int*) malloc (sizeof(int) * orderNumber + 2);

	// Child processes are created.
	for(i = 0; i < orderNumber + 1; ++i){
		
		// Process created.
		f = fork();

		// Fork error
		if(f == -1){
			printf("Fork error...\n");
			exit(1);
		}

		// Child process
		if(f == 0)
			break;

		// Process id
		localChildren[i] = f;
	}
	/************************ CREATE PROCESS - FINISH ************************/

	/************************* PARENT PROCESS - START ************************/
	// Parent process is running
	if(f != 0){

		// attaching the shared memory segment identified by waterLevelShmId
			// to the address space of the calling process (parent)
		globalWaterLevel = (int *) shmat(waterLevelShmId, NULL, 0);
		// the water level is initially at the maximum water level
		*globalWaterLevel = localMaxWater;
		// detacting the shared memory segment from the adress space of calling
			// process (parent)

		printf("SIMULATION BEGINS\n");

		sleep(2);
		kill(localChildren[0],12);
		for (int i = 1; i < orderNumber + 1; ++i){
			kill(localChildren[i],12);
			sem_wait(turnSemId,1);
			sleep(1);
		}

		// Final control before closing coffee machine
		if(*globalWaterLevel <= 1){
			printf("Current water level %d cups\n", *globalWaterLevel);
			shmdt(globalWaterLevel);
			sem_signal(emptyWaterId, 1);
			sem_wait(fillWaterSemId, 1);
		}
		else
			shmdt(globalWaterLevel);

		// kill fill water process 
		kill(localChildren[0], 9);

		printf("SIMULATION ENDS\n");

		// removing the created semaphores and shared memory
		semctl(lockSemId, 0, IPC_RMID);
		semctl(fillWaterSemId, 0, IPC_RMID);
		shmctl(waterLevelShmId, 0, IPC_RMID);
		semctl(turnSemId, 0, IPC_RMID);
		semctl(emptyWaterId, 0, IPC_RMID);

		free(orderList);
		free(localChildren);
	}
	/************************ PARENT PROCESS - FINISH ************************/

	/*********************** FILL WATER PROCESS - START **********************/
	else if(f == 0 && i == 0){
		pause();
		while(1){
			sem_wait(emptyWaterId, 1);
		printf("Employee %d wakes up and fills the coffee machine\n",getpid());

			globalWaterLevel = (int *) shmat(waterLevelShmId, NULL, 0);
			*globalWaterLevel = localMaxWater;

			shmdt(globalWaterLevel);

			sem_signal(fillWaterSemId, 1);
		}
	}
	/********************** FILL WATER PROCESS - FINISH **********************/

	/************************ EMPLOYEE PROCESS - START ***********************/
	else{
		myOrder = i;
		myCoffeType = orderList[myOrder - 1];
		pause();

		sem_wait(lockSemId, 1);

		// attaching the shared memory segment identified by waterLevelShmId
			// to the address space of the calling process (child)
		globalWaterLevel = (int *) shmat(waterLevelShmId, NULL, 0);

		printf("Current water level %d cups\n", *globalWaterLevel);
		printf("Employee %d wants coffee Type %d\n", getpid(), myCoffeType);

		// current water level control
		if(*globalWaterLevel - myCoffeType < 1){
			shmdt(globalWaterLevel);

			printf("Employee %d WAITS\n", getpid());
			sem_signal(emptyWaterId, 1);
			sem_wait(fillWaterSemId, 1);

			globalWaterLevel = (int *) shmat(waterLevelShmId, NULL, 0);
			printf("Current water level %d cups\n", *globalWaterLevel);
		}

		printf("Employee %d SERVED\n", getpid());
		*globalWaterLevel -= myCoffeType;

		sem_signal(lockSemId, 1);
		sem_signal(turnSemId, 1);

		shmdt(globalWaterLevel);

		exit(0);
	}
	/*********************** EMPLOYEE PROCESS - FINISH ***********************/

	return 0;
}

// This function calculate number of coffee order
int order_number()
{
	FILE *dgRead = fopen(fileName,"r");
	if(!dgRead)
		return -1;
	int temp, i;
	fscanf(dgRead, "%d", &temp);
	for (i = 0; !feof(dgRead); ++i)	
	{
		fscanf(dgRead, "%d ", &temp);
	}
	fclose(dgRead);
	return i;
}

//This function read data and write data to variable
int read_file(int *localMaxWater, int orderList[])
{
	FILE *dgRead = fopen(fileName,"r");
	if(!dgRead)
		return 0;

	fscanf(dgRead, "%d", localMaxWater);
	for(int i = 0; !feof(dgRead); ++i)
	{
		fscanf(dgRead, "%d", &orderList[i]);
	}
	fclose(dgRead);
	return 1;
}

void mysigset(int num)
{
	struct sigaction mysigaction;
	mysigaction.sa_handler = (void*) mysignal;
	// using the signal-catching function identified by sa_handler
	mysigaction.sa_flags = 0;
	// sigaction() system call is used to change the action taken by a process 
		//on receipt of a specific signal (specified with num)
	sigaction(num, &mysigaction, NULL);
}

// signal_handling function
void mysignal(int signum)
{
	//printf("Received signal with num=%d\n",signum );
}

// semaphore increment operation
void sem_signal(int semid, int val)
{
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = val;
	semaphore.sem_flg = 1;	// relavive: add sem_op to value
	semop(semid, &semaphore, 1);
}

// semaphore decrement operation
void sem_wait(int semid, int val)
{
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = (-1*val);
	semaphore.sem_flg = 1;	// relavive: add sem_op to value
	semop(semid, &semaphore, 1);
}