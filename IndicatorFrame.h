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

#ifndef _INDICATORFRAME_H_
#define _INDICATORFRAME_H_

#include <string>


class IndicatorFrame
{
public:
	IndicatorFrame(double, int, int, std::string);

	double getTimestamp();
	int getLength();
	bool isProtected();
	std::string getDestination();

private:
	IndicatorFrame() {};
	
	double m_timestamp;
	int m_length;
	bool m_protected;

	std::string m_destinationAddress;
};


#endif // _INDICATORFRAME_H_

