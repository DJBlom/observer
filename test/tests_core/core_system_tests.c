/********************************************************
 * Contents: Tests for observer.
 *
 * Author: Dawid Blom.
 *
 * Date: 29/03/2022.
 *
 *
 * NOTE: This file contains all tests created during the 
 * 	 engineering of observer.
 ********************************************************/
#include "CppUTest/TestHarness.h"
#include <sched.h>

extern "C"
{
	#include "../tests/core_system_test.h"
}




TEST_GROUP(core_system)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};


// Core system initialization test.
TEST(core_system, core_system_init)
{
	pid_t main_pid = getpid();
	double start_time = core_system_real_time();
	int priority = sched_get_priority_max(SCHED_FIFO);
	
	CHECK(core_system_init(SCHED_FIFO, priority, start_time, main_pid));
}


// Core system setup test.
TEST(core_system, core_system_setup)
{
	CHECK(core_system_setup());
}



// Core system clock test.
TEST(core_system, core_system_real_time)
{
	LONGS_EQUAL(0, core_system_real_time());
}
