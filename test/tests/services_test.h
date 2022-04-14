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



void *service1(void *arg);

void *service2(void *arg);

void *service3(void *arg);

void *service4(void *arg);

void *service5(void *arg);


#endif



void *service1(void *arg)
{
	pthread_exit(NULL);
}



void *service2(void *arg)
{
	pthread_exit(NULL);
}

void *service3(void *arg)
{
	pthread_exit(NULL);
}

void *service4(void *arg)
{
	pthread_exit(NULL);
}

void *service5(void *arg)
{
	pthread_exit(NULL);
}



