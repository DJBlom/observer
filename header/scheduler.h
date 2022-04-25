#ifndef _SCHEDULER_TEST_H
#define _SCHEDULER_TEST_H

#include <signal.h>

#include <time.h>



struct scheduler_members
{
	long frame_count;
	int count;
	bool abort_system;
	struct sigaction action;
	timer_t timer;
	struct itimerspec start_time;
	struct itimerspec last_time;
};
struct scheduler_members sched_member;


bool scheduler_init(long frame_count, int sec, long nsec);

void scheduler(int sigint);

#endif










/**
 * By calling this function, it should 
 * initialize the scheduler by arming 
 * the interval timer and setting up 
 * the signal that will trigger it.
 *
 * NOTE: This function will return false
 * 	 upon failure, and true upon 
 * 	 success.
 */
bool scheduler_init(long frame_count, int sec, long nsec)
{
	sched_member.frame_count = frame_count;

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
 * This function represents the scheduler, 
 * which will be in charge of the real-time 
 * service scheduling. Upon system abort, 
 * it will disarm the interval timer and 
 * free all the semaphores.
 */
void scheduler(int sigint)
{
	if (sched_member.abort_system || sched_member.count == sched_member.frame_count)
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

	if ((sched_member.count % 100) == 0)
		sem_post(&core_member.sem_s[0]);

	if ((sched_member.count % 20) == 0)
		sem_post(&core_member.sem_s[1]);

	if ((sched_member.count % 10) == 0)
		sem_post(&core_member.sem_s[2]);

	if ((sched_member.count % 5) == 0)
		sem_post(&core_member.sem_s[3]);

	if ((sched_member.count % 50) == 0)
		sem_post(&core_member.sem_s[4]);
}
