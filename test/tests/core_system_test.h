/*************************************************************************
 * Contents: All the TESTS for the whole core system.
 *
 * Author: Dawid Blom
 *
 * Date: 12/04/2022
 *
 * NOTE: All Tests done here for the core system.
 *************************************************************************/

#ifndef _CORE_SYSTEM_H
#define _CORE_SYSTEM_H

#include <sched.h>
#include <unistd.h>
#include <time.h>



struct core_members
{
	int 			policy;

	struct sched_param 	priority;

	pid_t 			pid;
};

struct core_members core_member;

bool system_init(int policy, int priority, pid_t pid);

bool system_setup();

double system_real_time();

#endif





/**
 * Test core_system_init function.
 **/
bool system_init(int policy, int priority, pid_t pid)
{
	{
		core_member.policy 				= policy;
		core_member.priority.sched_priority		= priority;
		core_member.pid				= pid;

		return true;
	}
	
	return false;
}












/**
 * Test for the system setup function.
 **/
bool system_setup()
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
 * Test for the system real time function. 
 **/
double system_real_time()
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC_RAW, &time);

	return (((double)(time.tv_sec) + (double)(time.tv_nsec)) / 1000000000.0);
}
