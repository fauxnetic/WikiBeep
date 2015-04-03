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

#include "IndicatorFrame.h"


IndicatorFrame::IndicatorFrame(double timestamp, int dataLength, int protectedVal, std::string destinationAddress)
{
	m_timestamp = timestamp;
	m_length = dataLength;
	m_protected = (protectedVal == 1);

	m_destinationAddress = destinationAddress;
}


double IndicatorFrame::getTimestamp()
{
	return m_timestamp;
}


int IndicatorFrame::getLength()
{
	return m_length;
}


bool IndicatorFrame::isProtected()
{
	return m_protected;
}


std::string IndicatorFrame::getDestination()
{
	return m_destinationAddress;
}
