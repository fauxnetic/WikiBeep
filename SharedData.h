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

#ifndef _SHAREDDATA_H_
#define _SHAREDDATA_H_

#include <pthread.h>
#include <list>

#include "IndicatorFrame.h"


// SharedData for sharing data between threads.
// Members are public but lock/unlock should be called prior to access.
class SharedData
{
public:
	SharedData();

	void lock();
	void unlock();
	
	std::list<IndicatorFrame> recentPotentialDNSFramesIn;
	std::list<IndicatorFrame> recentPotentialDNSFramesOut;

	double tsharkTimeNow;

	int totalIndicatorsSeen;

private:
	pthread_mutex_t m_sharedDataMutex;

};

#endif // _SHAREDDATA_H_

