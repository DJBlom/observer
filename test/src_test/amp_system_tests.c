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
	#include "../tests/amp_system_test.h"
}




TEST_GROUP(amp_system)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};


// Amp system initialization test.
TEST(amp_system, system_init)
{
	int priority = sched_get_priority_max(SCHED_FIFO);

	amp_member.policy = SCHED_FIFO;

	amp_member.priority = priority;

	LONGS_EQUAL(1, amp_member.policy);

	LONGS_EQUAL(99, amp_member.priority);

	CHECK(amp_system_init(SCHED_FIFO, priority));
}





// Amp thread_create.
TEST(amp_system, thread_create)
{
	CHECK(amp_thread_create());
}




// Amp thread_join.
TEST(amp_system, thread_join)
{
	CHECK(amp_thread_join());
}
