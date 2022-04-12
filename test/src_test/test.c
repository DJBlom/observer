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





TEST_GROUP(First)
{
	void setup()
	{
	}



	void teardown()
	{
	}
};



TEST(First, fit)
{
	CHECK(1 % 100 == 0);
}
