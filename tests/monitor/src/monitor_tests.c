/******************************************************************************/
/* monitor_tests.c --- monitor unit tests for baculua                         */
/* Copyright (c) 2013 Thomas Hartman (rokstar83@gmail.com)                    */
/*                                                                            */
/* This program is free software; you can redistribute it and/or              */
/* modify it under the terms of the GNU General Public License                */
/* as published by the Free Software Foundation; either version 2             */
/* of the License, or the License, or (at your option) any later              */
/* version.                                                                   */
/*                                                                            */
/* This program is distributed in the hope that it will be useful             */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              */
/* GNU General Public License for more details.                               */
/******************************************************************************/
#include "monitor_tests.h"
#include "baculua_error.h"
#include <monitor.h>

/* START TEST DEFINITIONS */

void test_connect_monitor()
{
   monitor mon;
   int err;

   mon.sock = 0;
   mon.director_name = "homer";
   mon.director_host_name = "homer";
   mon.portno = DEFAULT_DIRECTOR_PORTNO;

   err = connect_monitor(&mon, 3);
   disconnect_monitor(&mon);

   CU_ASSERT(err == 0);
}

void test_bad_connect()
{
   {
      monitor mon;
      int err;
      
      /* Test connecting to a non-existant host */
      
      mon.sock = 0;
      mon.director_name = "bad_host";
      mon.director_host_name = "bad_host";
      mon.portno = DEFAULT_DIRECTOR_PORTNO;
      
      err = connect_monitor(&mon, 3);
      disconnect_monitor(&mon);
      
      CU_ASSERT_EQUAL(err, 2);
   }

   /* Test connecting to an existing host, but one that isn't listening on 
      the DEFAULT_DIRECTOR_PORTNO */
   {
      monitor mon;
      int err;
      struct timeval timout;

      mon.sock = 0;
      mon.director_name = "google";
      mon.director_host_name = "google.com";
      mon.portno = DEFAULT_DIRECTOR_PORTNO;
      
      err = connect_monitor(&mon, 3);
      disconnect_monitor(&mon);
      
      CU_ASSERT_EQUAL(err, 6);
   }
}

/* END TEST DEFINITIONS */

CU_pSuite monitor_test_suite()
{
  CU_pSuite suite = NULL;

  suite = CU_add_suite("monitor_suite", NULL, NULL);

  CU_add_test(suite, "test_connect_monitor", test_connect_monitor);
  CU_add_test(suite, "test_bad_connect", test_bad_connect);
  /* ADD TESTS TO SUITE HERE */

  return suite;
}
