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

#include "UIUpdater.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <unistd.h> // sleep (posix)
#include <math.h>

#include "IndicatorFrame.h"


UIUpdater::UIUpdater(SharedData* sharedData)
{
	m_sharedData = sharedData;
}


void UIUpdater::update()
{		
	// Loop forever
	for(;;)
	{
		// Update every second
		sleep(1);
		
		
		m_sharedData->lock();
		
		double currentTSharkTime = m_sharedData->tsharkTimeNow;
	
		// Throw away any stale frame information, true if modified
		updateFrameBuffer(currentTSharkTime, m_sharedData->recentPotentialDNSFramesIn);
		updateFrameBuffer(currentTSharkTime, m_sharedData->recentPotentialDNSFramesOut);

		// Assess and update UI as appropriate


		int countDNSInFrames = m_sharedData->recentPotentialDNSFramesIn.size();
		int countDNSOutFrames = m_sharedData->recentPotentialDNSFramesOut.size();

		m_sharedData->unlock();

		std::cout << std::setw(9) << currentTSharkTime << "\t";
		std::cout << "\033[32mIn:"; // Go GREEN
		generateBars(std::cout, (double)countDNSInFrames);
		//std::cout << "\tI:" << countDNSInFrames;
		std::cout << "\033[34mO:"; // Go BLUE
		generateBars(std::cout, (double)countDNSOutFrames);
		//std::cout << "\tO:" << countDNSOutFrames;
		std::cout << "\033[0m";  // Return to normal colour
		std::cout << std::endl;
		

		if(meetsAlertThreshold(countDNSInFrames, countDNSOutFrames))
		{
			// Make a noise
			alert();
		}

	}
}

bool UIUpdater::updateFrameBuffer(double currentTime, std::list<IndicatorFrame>& frameBuffer)
{
	double timeMinusDelay = currentTime - (5.0); // 5 seconds ago
	bool bufferModified = false;
	int deleteCount = 0;

	std::list<IndicatorFrame>::iterator it;
	for(it = frameBuffer.begin(); it != frameBuffer.end(); ++it)
	{
		double savedFrameTimestamp = it->getTimestamp();

		if(savedFrameTimestamp >= timeMinusDelay)
		{
			// Elements inserted in order of time, 
			// there can be no more to delete after this.
			
			break;
		}

		deleteCount++;
	}

	// Deletes elements before timeMinusDelay
	if(deleteCount > 0)
	{
		frameBuffer.erase(frameBuffer.begin(), it);
		bufferModified = true;
	}

	
/*	std::cout << "NOW: " << currentTime << std::endl;
	for(std::list<IndicatorFrame>::iterator it = frameBuffer.begin(); it != frameBuffer.end(); ++it)
	{
		std::cout << it->getTimestamp() << " ";
	}
	std::cout << std::endl;
*/

	return bufferModified;
}


bool UIUpdater::meetsAlertThreshold(int indicatorsIn, int indicatorsOut)
{
	return indicatorsIn > 10 && indicatorsOut > 10;
}


void UIUpdater::alert()
{
	// Character generates a speaker tone
	std::cout << "\a";
}


void UIUpdater::generateBars(std::ostream& outStream, double currentValue)
{
	const int maxBars = 15;
	const double valueAtMax = 100.0;
	const double barsPerValue = (double)maxBars / valueAtMax;
	
	int barCount = ceil(currentValue * barsPerValue);
	int emptyCount = maxBars - barCount; 

	if(barCount > maxBars)
	{
		barCount = maxBars;
	}
	
	for(int i=0; i < barCount + 1; i++)
	{
		outStream << "|";
	}

	for(int i=0; i < emptyCount; i++)
	{
		outStream << " ";
	}

	return;
}
