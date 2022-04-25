#ifndef _SCHEDULER_TEST_H
#define _SCHEDULER_TEST_H

#include <signal.h>

#include <time.h>

#include "core_system.h"

#include "services.h"



struct scheduler_members
{
	int count;
	bool abort_system;
	struct sigaction action;
	timer_t timer;
	struct itimerspec start_time{{1,0}, {1,0}};
	struct itimerspec last_time;
};
struct scheduler_members sched_member;

bool scheduler_init(int sec, long nsec);

void scheduler(int sigint);

#endif








/**
 * sheduler initialization function test. 
 */
bool scheduler_init(int sec, long nsec)
{
	sched_member.count = 0;

	sched_member.abort_system = false;

	if (timer_create(CLOCK_REALTIME, NULL, &sched_member.timer) != 0)
	{
		perror("interval timer createion");
		return false;
	}

	
	sched_member.action.sa_handler 	= &scheduler;

	if (sigemptyset(&sched_member.action.sa_mask) != 0)
	{
		perror("action mask set");
		return false;
	}

	sched_member.action.sa_flags 	= 0;
	
	if (sigaction(SIGALRM, &sched_member.action, NULL) != 0)
	{
		perror("signal setup");
		return false;
	}

	sched_member.start_time.it_interval.tv_sec 	= sec;
	sched_member.start_time.it_interval.tv_nsec 	= nsec;
	sched_member.start_time.it_value.tv_sec 	= sec;
	sched_member.start_time.it_value.tv_nsec 	= nsec;
	
	if (timer_settime(sched_member.timer, 0, &sched_member.start_time, &sched_member.last_time) != 0)
	{
		perror("interval timer armed");
		return false;
	}

	return true;
}










/**
 *
 */
void scheduler(int sigint)
{
	if (sched_member.abort_system)
	{
		sched_member.start_time.it_interval.tv_sec 	= 0;
		sched_member.start_time.it_interval.tv_nsec 	= 0;
		sched_member.start_time.it_value.tv_sec 	= 0;
		sched_member.start_time.it_value.tv_nsec 	= 0;

		if (timer_settime(sched_member.timer, 0, &sched_member.start_time, &sched_member.last_time) != 0)
			perror("disarm interval timer");
	
		for (int i = 0; i < SIZE; i++)
		{
			services_member.abort[i] = true;
			sem_post(&core_member.sem_s[i]);
		}
	}

	sched_member.count++;

	if ((sched_member.count % 2) == 0)
		sem_post(&core_member.sem_s[4]);

	if ((sched_member.count % 5) == 0)
		sem_post(&core_member.sem_s[3]);

	if ((sched_member.count % 10) == 0)
		sem_post(&core_member.sem_s[2]);

	if ((sched_member.count % 20) == 0)
		sem_post(&core_member.sem_s[1]);

	if ((sched_member.count % 100) == 0)
		sem_post(&core_member.sem_s[0]);
}
