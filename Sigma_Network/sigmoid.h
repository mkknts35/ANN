/*
    This is a class definition for Sigma Net, which is a simple
    Artificial Neural Network

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
//   File:          sigmoid.h
//   Author:        Michael Koonts
//   Date:          April 7, 2016
//   Description:   Class definition of sigmoid
//============================================================================
#pragma once
#ifndef SIGMOID_H
#define SIGMOID_H

#include <vector>
#include <memory>
#include "neuron.h"

using namespace std;

class sigmoid : public neuron
{
public:
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Initializes a new sigmoid that uses the provided pointers as 
    //          input/output.
    //========================================================================
    sigmoid(
        vector<shared_ptr<double>> input,
        shared_ptr<double> output,
        bool hidden = true);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Destroys this
    //========================================================================
    virtual ~sigmoid();
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Uses the Sigma function to return a value between 1 and 0 
    //          exclusive.
    //========================================================================
    double activate(double x);
};

#endif