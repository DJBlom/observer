/*****************************************************************************
 * Contents: This file contains the main function of observer
 *
 * Author: Dawid Blom
 *
 * Date: 13/04/2022
 *
 * NOTE: Observer is hard real-time embedded system that runs 
 * 	 on a FIFO scheduling mechanism.
 *****************************************************************************/







#define _GNU_SOURCE
#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <syslog.h>

#include "../header/core_system.h"

#include "../header/amp_system.h"

#include "../header/scheduler.h"




/**
 * Policy used to run the system
 * in a FIFO manner in order to
 * achieve pridictable results.
 **/
#define POLICY SCHED_FIFO







/**
 * By calling this function, it should
 * start the whole system and begin 
 * running it's real time services in
 * a FIFO order.
 *
 * Additionally, keeping time and profiling
 * with syslog.
 **/
int main(int argc, char **argv)
{
	double start_system_time = core_system_real_time();

	openlog("OBSERVER", LOG_ODELAY, LOG_USER);
	syslog(LOG_CRIT, "start time %6.2fsec", start_system_time);

	int priority = sched_get_priority_max(POLICY);
	pid_t main_pid = getpid();
	if (!core_system_init(POLICY, priority, start_system_time, main_pid))
	{
		perror("core system initialization");
		exit(1);
	}


	if (!amp_system_init(POLICY, priority))
	{
		perror("amp system initilization");
		exit(1);
	}


	if (!core_system_setup())
	{
		perror("set scheduler");
		exit(1);
	}


	if (!amp_thread_setup())
	{
		perror("amp thread setup");
		exit(1);
	}


	if (!amp_thread_create())
	{
		perror("amp thread creation");
		exit(1);
	}

	
	if (!scheduler_init(101, 0, 10000000))
	{
		perror("scheduler initialization");
		exit(1);
	}


	if (!amp_thread_join())
	{
		perror("amp thread joining");
		exit(1);
	}

	core_system_cleanup();


	printf("system finished in: %6.2fsec\n", start_system_time);
	syslog(LOG_CRIT, "finish time: %6.2fsec", start_system_time);
	closelog();

	return 0;
}
