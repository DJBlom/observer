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
	#include "../tests/scheduler_test.h"
}




TEST_GROUP(scheduler)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};




TEST(scheduler, scheduler_init)
{
	CHECK(scheduler_init(0, 10000000));
}


TEST(scheduler, scheduler)
{

}
