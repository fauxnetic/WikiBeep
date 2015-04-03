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


SharedData::SharedData()
{
	pthread_mutex_t m_sharedDataMutex = PTHREAD_MUTEX_INITIALIZER;

	totalIndicatorsSeen = 0;
}


void SharedData::lock()
{
	// Exclusive access to calling thread
	pthread_mutex_lock(&m_sharedDataMutex);
}



void SharedData::unlock()
{
	// Release the mutex
	pthread_mutex_unlock(&m_sharedDataMutex) ;
}	

