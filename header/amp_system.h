/************************************************************************
 * Contents: This file contains the thread functions of observer 
 *
 * Author: Dawid Blom
 *
 * Date: 14/04/2022
 *
 * NOTE: All the services in this file is contained in the file 
 * 	 services.h. This file should handle all the necessary
 * 	 functionality for the real-time services when it comes
 * 	 to threading.
 ************************************************************************/

#ifndef _AMP_SYSTEM_H
#define _AMP_SYSTEM_H

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <pthread.h>

#include "services.h"


struct amp_members
{
	int 			policy;

	int 			priority;

	struct sched_param 	thread_priority[SIZE];

	pthread_attr_t 		thread_attr[SIZE];

	pthread_t 		threads[SIZE];
};

struct amp_members amp_member;



bool amp_system_init(int policy, int priority);

bool amp_thread_setup();

bool amp_thread_create();

bool amp_thread_join();

#endif









/**
 * By calling this function, it should
 * initialize the the members inside 
 * the struct amp_members with a policy 
 * and priority.
 *
 * Finally, this function returns false 
 * uppon failure and true uppon success. 
 **/
bool amp_system_init(int policy, int priority)
{
	amp_member.policy	= policy;
	amp_member.priority	= priority;
	for (int i = 0; i < SIZE; i++)
	{
		amp_member.thread_priority[i].sched_priority = priority - i;
	}

	return true;
}











/**
 * By calling this function, it should
 * setup the service threads with all
 * their attributes as well as assign
 * affinity so that each service will
 * run on a specified CPU core.
 *
 * All even number services will run
 * on CPU core 2 and all odd numbered
 * services will run on CPU core 1.
 *
 * Finally, this function returns false
 * uppon failure to setup the threads
 * and true uppon success.
 **/
bool amp_thread_setup()
{
	int rc;
	cpu_set_t cpu;
	for (int i = 0; i < SIZE; i++)
	{
		CPU_ZERO(&cpu);
		if (((i + 1) % 2) == 0)
			CPU_SET(2, &cpu);
		else if (((i + 1) % 5) == 0)
			CPU_SET(3, &cpu);
		else
			CPU_SET(1, &cpu);

		
		rc = pthread_attr_init(&amp_member.thread_attr[i]);
		if (rc != 0)
		{
			perror("Pthread Attribute Init: ");
			return false;
		}

		rc = pthread_attr_setinheritsched(&amp_member.thread_attr[i], PTHREAD_EXPLICIT_SCHED);
		if (rc != 0)
		{
			perror("Pthread Attribute Setinheritsched: ");
			return false;
		}

		rc = pthread_attr_setschedpolicy(&amp_member.thread_attr[i], amp_member.policy);
		if (rc != 0)
		{
			perror("Pthread Attribute Setschedpolicy: ");
			return false;
		}

		rc = pthread_attr_setschedparam(&amp_member.thread_attr[i], &amp_member.thread_priority[i]);
		if (rc != 0)
		{
			perror("Pthread Attribute Setschedparam: ");
			return false;
		}

		rc = pthread_attr_setaffinity_np(&amp_member.thread_attr[i], sizeof(cpu_set_t), &cpu);
		if (rc != 0)
		{
			perror("Pthread Attribute Setaffinity: ");
			return false;
		}
	}

	return true;
}












/**
 * By calling this function, it should
 * create the threads for all the services
 * based on the attributes that was used
 * in the amp_thread_setup function.
 *
 * Finally, this function returns false
 * uppon failure and true uppon success.
 **/
bool amp_thread_create()
{
	int rc = pthread_create(&amp_member.threads[0], &amp_member.thread_attr[0], service1,NULL);
	if (rc != 0)
	{
		perror("Thread Creation For Service 1: ");
		return false;
	}

	rc = pthread_create(&amp_member.threads[1], &amp_member.thread_attr[1], service2, NULL);
	if (rc != 0)
	{
		perror("Thread Creation For Service 2: ");
		return false;
	}

	rc = pthread_create(&amp_member.threads[2], &amp_member.thread_attr[2], service3, NULL);
	if (rc != 0)
	{
		perror("Thread Creation For Service 3: ");
		return false;
	}

	rc = pthread_create(&amp_member.threads[3], &amp_member.thread_attr[3], service4, NULL);
	if (rc != 0)
	{
		perror("Thread Creation For Service 4: ");
		return false;
	}

	rc = pthread_create(&amp_member.threads[4], &amp_member.thread_attr[4], service5, NULL);
	if (rc != 0)
	{
		perror("Thread Creation For Service 5: ");
		return false;
	}

	return true;
}











/**
 * By calling this function, it should
 * join all the threads that were created 
 * for this system.
 *
 * Finally, this function always returns 
 * true, however, it should display whether
 * or not the thread has been joined.
 **/
bool amp_thread_join()
{
	int rc;
	for (int i = 0; i < SIZE; i++)
	{
		rc = pthread_join(amp_member.threads[i], NULL);
		if (rc < 0)
			perror("Thread Join: ");
		else
			perror("Thread Join: ");
	}

	printf("Joined the threads.\n");
	return true;
}
