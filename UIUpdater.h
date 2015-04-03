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

#ifndef _UIUPDATER_H_
#define _UIUPDATER_H_


#include <list>
#include <string>

#include "SharedData.h"



class UIUpdater
{
public:
	UIUpdater(SharedData*);

	void update();

private:
	bool updateFrameBuffer(double, std::list<IndicatorFrame>& );
	bool meetsAlertThreshold(int, int);
	void alert();

	void generateBars(std::ostream& outStream, double currentValue);

	
	SharedData* m_sharedData;
};

#endif // _UIUPDATER_H_

