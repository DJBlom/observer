/*************************************************************************
 * Contents: This file contains both the interface and the implementation
 *
 * Author: Dawid Blom
 *
 * Date: 12/04/2022
 *
 * NOTE: This is the core system, which will setup the Linux kernel
 * 	 to run according to FIFO so that we can use RMA in order to
 * 	 properly determine the outcome.
 *************************************************************************/






#ifndef _CORE_SYSTEM_H
#define _CORE_SYSTEM_H

#include <sched.h>

#include <unistd.h>

#include <time.h>



struct system_members
{
	int 			policy;

	struct sched_param 	priority;

	pid_t 			pid;
};

struct system_members member;

bool system_init(int policy, int priority, pid_t pid);

bool system_setup();

double system_real_time();

#endif





/**
 * By calling this function, it should
 * initialize the core system and enable
 * it to set itself up in order for the
 * system to run correctly.
 *
 * It should assign the policy the system
 * will run at, the priority the system
 * should run at, and the main processes
 * process identification.
 **/
bool system_init(int policy, int priority, pid_t pid)
{
	{
		member.policy 				= policy;
		member.priority.sched_priority		= priority;
		member.pid				= pid;

		return true;
	}
	
	return false;
}












/**
 * By calling this function, it should
 * it should setup the Linux Kernel's 
 * scheduler policy to whatever the 
 * policy was used to initialize the 
 * system with.
 *
 * It will set the scheduler with a 
 * specified policy, and it will
 * print out the current policy of the
 * system.
 *
 * Returns true if everything went well,
 * or return false when we failed to set 
 * the Linux Kernel scheduler.
 **/
bool system_setup()
{
	int rc = sched_setscheduler(member.pid, member.policy, &member.priority);
	if (rc != 0)
	{
		perror("Usage: sudo ./[name of executable binary]");
		return false;
	}

	
	int policy = sched_getscheduler(member.pid);
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
 * By calling this function, it should
 * compute the systems clock in order 
 * to profile and track the time of the
 * system. Converting nano-seconds to
 * seconds.
 **/
double system_real_time()
{
	struct timespec time;
	int rc = clock_gettime(CLOCK_MONOTONIC_RAW, &time);
	if (rc != 0)
	{
		perror("Failed to get system_time: ");
		exit(1);
	}

	return (((double)(time.tv_sec) + (double)(time.tv_nsec)) / 1000000000.0);
}
