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
    // REQUIRES: A valid output in m_output
    // MODIFIES: this
    // EFFECTS: Adjusts the weights of all the input weights in the sigmoid
    //========================================================================
    void train(double expected);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Calculates and sets the output of this
    //========================================================================
    void push();

private:
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Returns a value between 1 and 0 exclusive
    //========================================================================
    double sigma(double x);
    //========================================================================
    // REQUIRES: An index 0 <= weight <= n where n is the number of inputs the 
    //           sigmoid has.
    // MODIFIES: this
    // EFFECTS: The indexed input weight by the amount given.
    //========================================================================
    void adjustWeight(unsigned int weight, double delta);
    //========================================================================
    // REQUIRES: A meaningful value in m_output
    // MODIFIES: this
    // EFFECTS: sets m_error (used if this is in the output layer)
    //========================================================================
    void calculateOutputError(double expected);
    //========================================================================
    // REQUIRES: A meaningful value in m_output
    // MODIFIES: this
    // EFFECTS: sets m_error (used if this is in a hidden layer)
    //========================================================================
    void calculateHiddenError(double expected);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Calculate the amount the designated weight needs to change
    //========================================================================
    double delta(unsigned int i);
};

#endif