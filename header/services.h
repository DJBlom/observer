/***********************************************************************
 * Contents: This file contains all real time services of observer 
 *
 * Author: Dawid Blom
 *
 * Date: 15/04/2022
 *
 * NOTE: These are all the service currently being used by observer.
 * 	 However, this can change in the event of new features being
 * 	 added. Furthermore, as it stand now, I have not yet decided
 * 	 which services will perform which action. Therefore, I only
 * 	 implemented a template and will implement all the required
 * 	 actions that will be performed by these services as soon as
 * 	 I decided which one goes where. 
 *
 ***********************************************************************/

#ifndef _SERVICES_H
#define _SERVICES_H

#include <semaphore.h>

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






/**
 * By calling this function, it should 
 * initialize the real-time services 
 * abort variables to false. Thereby, 
 * allowing proper functionality of 
 * the services.
 */
bool services_init()
{
	for (int i = 0; i < SIZE; i++)
		services_member.abort[i] = false;

	return true;
}










/**
 * By calling this function, it should 
 * execute the real-time service 1, which 
 * will access a critical section store 
 * real-time video frames in the shared 
 * data structure.
 *
 * NOTE: This service runs until aborted
 * 	 by the scheduler.
 */
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










/**
 * By calling this function, it should 
 * execute the real-time service number 
 * 2, which is responsible for computing
 * the difference between the real-time 
 * video frames captured by service 1.
 *
 * NOTE: This service runs until aborted
 * 	 by the scheduler.
 */
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










/**
 * By calling this function, it should 
 * execute the real-time service number 
 * 3, which is responsible for sharpening
 * the the real-time video frames that had
 * their differences computed by service 2.
 *
 * NOTE: This service runs until aborted
 * 	 by the scheduler.
 */
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
		syslog(LOG_CRIT, "service 3 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}

	pthread_exit(NULL);
}










/**
 * By calling this function, it should 
 * execute real-time service number 4, 
 * which will write the video frames 
 * sharpened by real-time service 3 
 * to a file for transferring. 
 *
 * NOTE: This service runs until aborted
 * 	 by the scheduler.
 */
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
		syslog(LOG_CRIT, "service 4 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}
	
	pthread_exit(NULL);
}










/**
 * By calling this function, it should 
 * execute the real-time service number 
 * 5, which is responsible for transferring 
 * the video files over an embedded TCP/IP 
 * network. Thereby, accessing the folder 
 * where real-time service 4, has stored 
 * the final video frames.
 */
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
		syslog(LOG_CRIT, "service 5 [service function name goes here] @ [Hz goes here] on core = %d, for release %llu @ %6.2lfsec.\n",
				sched_getcpu(), thread_count, current_time - core_member.start_time);
	}
	
	pthread_exit(NULL);
}
