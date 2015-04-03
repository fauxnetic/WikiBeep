/*
 * WikiBeep
 * Copyright (C) 2013 John Atkinson <john@fauxnetic.co.uk>
 * 
 * WikiBeep is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * WikiBeep is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <pthread.h>

#include "SharedData.h"
#include "UIUpdater.h"
#include "WikiDetector.h"


SharedData sharedData;


void* updateFunction(void* arg)
{
	UIUpdater uiUpdater(&sharedData);
	uiUpdater.update();
}

void* detectorFunction(void* arg)
{
	WikiDetector detector(&sharedData);
	detector.detectWikipediaActivity();
}


int main()
{
	// Create thread for detector to run in
	pthread_t detectorThread;
	pthread_create(&detectorThread, NULL, &detectorFunction, NULL);

	// Use this thread for UI Updates
	pthread_t uiThread;
    	pthread_create(&uiThread, NULL, &updateFunction, NULL);


	// These threads will never quit, but for completion's sake...
	pthread_join(detectorThread, NULL);
	pthread_join(uiThread, NULL);
	return 0;
}



