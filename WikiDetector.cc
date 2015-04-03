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

#include "WikiDetector.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <vector>


WikiDetector::WikiDetector(SharedData* sharedData)
{
	m_sharedData = sharedData;
}


void WikiDetector::detectWikipediaActivity()
{
	// Open TShark Pipe and read output into buffer
	const char *tSharkString = "tshark	-i mon0 "\
	                     	 "-l "\
	                         "-T fields "\
	                         //"-e frame.number "
	                         "-e frame.time_relative "\
	                         //"-e frame.len "
	                         //"-e radiotap.length "
	                         "-e wlan.fc.protected "\
	                         //"-e wlan.sa "
	                         "-e wlan.da "\
	                         "-e data.len "\
	                         "-E header=n "\
	                         "-E separator=/s "\
	                         "-E quote=n "\
	                         "-E occurrence=f";
	FILE* lsofFile_p = popen(tSharkString, "r");

	if (!lsofFile_p)
	{
		std::cout << "E: Failed to execute TShark command." << std::endl;
		return;
	}
	else
	{
		std::cout << "Executing TShark: " << tSharkString << std::endl;
	}


	while (fgets(m_tSharkBuffer, sizeof(m_tSharkBuffer), lsofFile_p)) 
	{
		// Process each TShark output line...
		// Copy each spaced separated element into vector
		std::vector<std::string> frameInfo;

		std::istringstream infoStream(m_tSharkBuffer);
		std::copy(  std::istream_iterator<std::string>(infoStream),
					std::istream_iterator<std::string>(),
					std::back_inserter<std::vector<std::string> >(frameInfo));
		
		//std::cout << m_tSharkBuffer << std::endl;
		//std::cout << frameInfo.size() << std::endl;
		
		// Convert to real value types
		double timeStamp = stringToDouble(frameInfo.at(0));
		int frameProtected = stringToInt(frameInfo.at(1));
		int dataLength;

		// Some frames will not have a destination or data payload...
		// Handle the shorter vector gracefully
		std::string frameDestination;
		
		if(frameInfo.size() > 2)
		{
			frameDestination = frameInfo.at(2);
		}
		else
		{
			frameDestination = "--:--:--:--:--:--";
		}

		if(frameInfo.size() > 3)
		{
			dataLength = stringToInt(frameInfo.at(3));
		}
		else
		{
			dataLength = 0;
		}
		
		IndicatorFrame observedFrame(timeStamp, dataLength, frameProtected, frameDestination);

		// Will set to true if any of the following return true
		bool stateChange = false;
		
		// Process observed frame, returns true if recorded
		frameSeen(observedFrame);

	}


	// Tidy open TShark handle
	pclose(lsofFile_p);

	return;
}


bool WikiDetector::frameSeen(IndicatorFrame& observedFrame) 
{
	bool recorded = false;
	bool ignore = false;
	
	m_sharedData->lock();
	m_sharedData->tsharkTimeNow = observedFrame.getTimestamp();
	
	if(!observedFrame.isProtected())
	{
		// Ignore non-encrypted frames
		ignore = true;
	}
	
	if(observedFrame.getDestination() == "ff:ff:ff:ff:ff:ff")
	{
		// Ignore broadcast frames
		ignore = true;
	}

	if(!ignore)
	{
		switch(observedFrame.getLength())
		{
			case 79:	// www.wikipedia.org
			case 78:	// xx.wikipedia.org
				m_sharedData->recentPotentialDNSFramesIn.push_back(observedFrame);
				m_sharedData->totalIndicatorsSeen++;
			
				recorded = true;
				break;

			case 95:   // Reply www.wikipedia.org
			case 94:   // Reply xx.wikipedia.org
			case 262:  // [As above, for Cisco IV-padding]
			case 261:  // [As above, for Cisco IV-padding]
				m_sharedData->recentPotentialDNSFramesOut.push_back(observedFrame);
				m_sharedData->totalIndicatorsSeen++;
			
				recorded = true;
				break;

			default:
				break;
		}
	}
	
	m_sharedData->unlock();
	return recorded;
}


int WikiDetector::stringToInt(std::string& text)
{
	std::stringstream ss(text);
	int result;
	return ss >> result ? result : 0;
}


double WikiDetector::stringToDouble(std::string& text)
{
	std::istringstream iss(text);
	double x;
	if (!(iss >> x))
		return 0;
	return x;
} 
