/*************************************************************************
 * Contents: All the TESTS for the whole core core_system.
 *
 * Author: Dawid Blom
 *
 * Date: 12/04/2022
 *
 * NOTE: All Tests done here for the core core_system.
 *************************************************************************/

#ifndef _CORE_SYSTEM_H
#define _CORE_SYSTEM_H

#include <sched.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>


#define SIZE 5


struct core_members
{
	int 			policy;

	double			start_time;

	struct sched_param 	priority;

	pid_t 			pid;

	sem_t			sem_s[SIZE];
};
struct core_members core_member;


bool core_system_init(int policy, int priority, double start_time, pid_t pid);

bool core_system_setup();

double core_system_real_time();

#endif





/**
 * Test core_system_init function.
 **/
bool core_system_init(int policy, int priority, double start_time, pid_t pid)
{
	core_member.policy 			= policy;
	core_member.start_time			= start_time;
	core_member.priority.sched_priority	= priority;
	core_member.pid				= pid;

	for (int i = 0; i < SIZE; i++)
	{
		if (sem_init(&core_member.sem_s[i], 0, 0) != 0)
		{
			perror("service 1 semaphore initialization");
			return false;
		}
	}


	return true;
}












/**
 * Test for the core_system setup function.
 **/
bool core_system_setup()
{
	int rc = sched_setscheduler(core_member.pid, core_member.policy, &core_member.priority);
	if (rc != 0)
	{
		perror("Usage: sudo ./[name of executable binary]");
		return false;
	}

	
	int policy = sched_getscheduler(core_member.pid);
	switch (policy)
	{
		case SCHED_FIFO:
			printf("Kernel Scheduler Set To: SCHED_FIFO\n");
			break;
		case SCHED_OTHER:
			printf("Kernel Scheduler Set To: SCHED_OTHER\n");
			break;
		case SCHED_RR:
			printf("Kernel Scheduler Set To: SCHED_RR\n");
			break;
		default: 
			printf("Kernel Scheduler Set To: UNKNOWN.\n");
	}

	return true;
}












/**
 * Test for the core_system real time function. 
 **/
double core_system_real_time()
{
	struct timespec time;
	int rc = clock_gettime(CLOCK_MONOTONIC_RAW, &time);
	if (rc != 0)
	{
		perror("failed to get system_time");
		exit(1);
	}

	return (((double)(time.tv_sec) + (double)(time.tv_nsec)) / 1000000000.0);
}
