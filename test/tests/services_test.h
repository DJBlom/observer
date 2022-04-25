/***********************************************************************
 * Contents: This file contains all tests for the services file
 *
 * Author: Dawid Blom
 *
 * Date: 14/04/2022
 *
 * NOTE: All the tests for the services tests
 *
 ***********************************************************************/

#ifndef _SERVICES_H
#define _SERVICES_H

#include <syslog.h>

#include "core_system_test.h"

struct services_members
{
	bool abort[SIZE];
};
struct services_members services_member;


bool services_init();

void *service1(void *arg);

void *service2(void *arg);

void *service3(void *arg);

void *service4(void *arg);

void *service5(void *arg);


#endif







bool services_init()
{
	for (int i = 0; i < SIZE; i++)
		services_member.abort[i] = false;

	return true;
}




void *service1(void *arg)
{
	long long thread_count = 0;
	double current_time = 0.0;

	while (!services_member.abort[0])
	{
		sem_wait(&core_member.sem_s[0]);
		if (services_member.abort[0])
			break;
		thread_count++;

		// Desired function goes here.
		
		current_time = core_system_real_time();
		syslog(LOG_CRIT, "service 1 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}

	pthread_exit(NULL);
}



void *service2(void *arg)
{
	long long thread_count = 0;
	double current_time = 0.0;

	while (!services_member.abort[2])
	{
		sem_wait(&core_member.sem_s[1]);
		if (services_member.abort[1])
			break;
		thread_count++;

		// Desired function goes here.
		
		current_time = core_system_real_time();
		syslog(LOG_CRIT, "service 2 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}

	pthread_exit(NULL);
}

void *service3(void *arg)
{
	long long thread_count = 0;
	double current_time = 0.0;

	while (!services_member.abort[2])
	{
		sem_wait(&core_member.sem_s[2]);
		if (services_member.abort[2])
			break;
		thread_count++;

		// Desired function goes here.
		
		current_time = core_system_real_time();
		syslog(LOG_CRIT, "service 2 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}

	pthread_exit(NULL);
}

void *service4(void *arg)
{
	long long thread_count = 0;
	double current_time = 0.0;

	while (!services_member.abort[3])
	{
		sem_wait(&core_member.sem_s[3]);
		if (services_member.abort[3])
			break;
		thread_count++;

		// Desired function goes here.
		
		current_time = core_system_real_time();
		syslog(LOG_CRIT, "service 2 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}

	pthread_exit(NULL);
}

void *service5(void *arg)
{
	long long thread_count = 0;
	double current_time = 0.0;

	while (!services_member.abort[4])
	{
		sem_wait(&core_member.sem_s[4]);
		if (services_member.abort[4])
			break;
		thread_count++;

		// Desired function goes here.
		
		current_time = core_system_real_time();
		syslog(LOG_CRIT, "service 2 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}

	pthread_exit(NULL);
}



