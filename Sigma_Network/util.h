/*
    These are utility function headers that I commonly use in my software.

    Copyright(C) 2016  Michael Brett Koonts

    This program is free software : you can redistribute it and / or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//============================================================================
//   File:          util.h
//   Author:        Michael Koonts
//   Date:          June 11, 2016
//   Description:   Commonly needed functionality for console based programs
//============================================================================
#pragma once
#ifndef UTIL_H_
#define UTIL_H_

#define WINDOWSSYSTEM 1

#if WINDOWSSYSTEM
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
#include <iostream>
#include <iomanip>
#include <string>
//========================================================================
// REQUIRES: Two valid time stamps
// MODIFIES: nothing
// EFFECTS: Calculates the difference between the provided time stamps and
//          prints the result to standard out in both milliseconds and 
//          DD:HH:MM:SS.
//========================================================================
#if WINDOWSSYSTEM
//========================================================================
// Windows version
//========================================================================
void PrintTimeDifference(const FILETIME &start, const FILETIME &end);
#else
//========================================================================
// Linux version
//========================================================================
void PrintTimeDifference(const timeval &start, const timeval &end);
#endif
//========================================================================
// REQUIRES: Nothing
// MODIFIES: STDOUT
// EFFECTS: Calculates what percentage position is of end and returns the 
//          result.
//========================================================================
int calcPercentageComplete(int position, int end);
//========================================================================
// REQUIRES: If percent is 100, finished should be true.
// MODIFIES: STDOUT
// EFFECTS: Changes the last three charactors sent to STDOUT to the 
//          perecent value provided, or to "done" if finished == true.
//========================================================================
int updateOutputPercentage(int percent, bool finished);
//========================================================================
// REQUIRES: Nothing
// MODIFIES: STDOUT
// EFFECTS: Outputs a status message to STDOUT followed by "... ". For use
//          with updateOutputPercentage method above.
//========================================================================
void outputStatusMessage(std::string message);

#endif