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
	double start_system_time = system_real_time();

	openlog("OBSERVER STATUS", LOG_ODELAY, LOG_USER);
	syslog(LOG_CRIT, "Start Time %6.2fsec", start_system_time);

	int priority = sched_get_priority_max(POLICY);
	pid_t main_pid = getpid();
	if (!system_init(POLICY, priority, main_pid))
	{
		perror("Failed to initialize system: ");
		exit(1);
	}


	if (!system_setup())
	{
		perror("Failed to set scheduler: ");
		exit(1);
	}

	printf("SYSTEM FINISHED: %6.2f\n", start_system_time);
	syslog(LOG_CRIT, "Finished Time %6.2fsec", start_system_time);
	closelog();

	return 0;
}
