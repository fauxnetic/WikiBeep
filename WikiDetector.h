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

#ifndef WIKIDETECTOR_H
#define WIKIDETECTOR_H

#include <string>

#include "IndicatorFrame.h"
#include "SharedData.h"


class WikiDetector
{
 
public:
    WikiDetector(SharedData*);

	void detectWikipediaActivity();
	
private:
    	bool frameSeen(IndicatorFrame&);
	
	int stringToInt(std::string&);
	double stringToDouble(std::string&);

	
	char m_tSharkBuffer[4096];
	SharedData* m_sharedData;
};


#endif
