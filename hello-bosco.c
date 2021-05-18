/**
 * \file
 *			hello world exercise to learn contiki step-by-step.	This is to 
 *			recreate the hello-world example but added my own notes.
 * \author
 *			Bosco Lau <bosco.kc.lau@gmail.com>
 */

#include "contiki.h"

#include <stdio.h>


/* ======================================================================
	1. Create Makefile. See Makefile in the same directory

	2. Miniumum code required

	PROCESS(name, name_str);
	AUTOSTART_PROCESSES(&name);
	PROCESS_THREAD(name, ev, data){
		PROCESS_BEGIN());
		PROCESS_END();
	}

	make TARGET=native should be successful

	3. Add printf() with timer
		Notes on timer:
			3.1 Declare - static struct etimer
			3.2 Set with expiration - etimer_set()
			3.3 Wait for expiration - PROCESS_WAIT_EVENT_UNTIL()
			3.4 Reset - etimer_reset

	4.	The work
			Here, we simply do a printf() with a counter
			4.1 Define the counter outside PROCESS_THREAD (Notes 4.1)
			4.2 The printf()

	5.	make and run
			At the command line, execute:
				make TARGET=native
				./hello-bosco.native

			The program should run and print the content in printf() 
			every 3 seconds

	Notes:
		4.1 Counter needs to be outside as the PROCESS_THREAD defines the
		    body of a Protothread, which does not save states of automatic
		    variables across blocked WAITs. See sys/process.h for further detail.
===========================================================================*/

PROCESS(hello_bosco_process, "Hello Bosco Process");			// Step 2
AUTOSTART_PROCESSES(&hello_bosco_process);						// Step 2

int i = 0;														// Step 4.1

// ev: event
PROCESS_THREAD(hello_bosco_process, ev, data){					// Step 2

	static struct etimer timer;									// Step 3.1

	PROCESS_BEGIN();											// Step 2

	// Start timer, expiring every 3 seconds					// Step 3.23
	etimer_set(&timer, CLOCK_SECOND * 3);


	while(1){
		printf("Hello Bosco: %3d\n", i++);						// Step 4.2

		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));		// Step 3.3
		etimer_reset(&timer);									// Step 3.4
	}

	PROCESS_END();												// Step 2
}