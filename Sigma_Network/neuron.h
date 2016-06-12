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
//   File:          neuron.h
//   Author:        Michael Koonts
//   Date:          June 11, 2016
//   Description:   Class definition of neuron. This is a virtual base class. 
//                  
//============================================================================
#pragma once
#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <memory>
#include <random>

using namespace std;

class neuron
{
public:
    const double TRAINING_RATE = 0.01;
    const double DECAY_RATE = 0.000001;

protected:
    vector<shared_ptr<double>> m_input;
    shared_ptr<double> m_output;
    vector<double> m_weight;
    vector<double> m_oldWeight;
    double m_trianingRate = TRAINING_RATE;
    double m_error;
    bool m_hidden;

public:
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Initializes a new neuron that uses the provided pointers as 
    //          input/output.
    //========================================================================
    neuron(
        vector<shared_ptr<double>> input,
        shared_ptr<double> output,
        bool hidden = true);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Destroys this
    //========================================================================
    virtual ~neuron();
    //========================================================================
    // REQUIRES: A valid output in m_output
    // MODIFIES: this
    // EFFECTS: Adjusts the weights of all the input weights in the sigmoid
    //========================================================================
    virtual void train(double expected) = 0;
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Calculates and sets the output of this
    //========================================================================
    virtual void push() = 0;
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Replaces the current weight vector with the one provided
    //========================================================================
    void setWeights(vector<double> weights);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Returns the vector of weights currently in use by this
    //========================================================================
    vector<double> getWeights();
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: this
    // EFFECTS: Adjusts the trianing rate
    //========================================================================
    void setTrainingRate(double rate);
    //========================================================================
    // REQUIRES: Nothing
    // MODIFIES: Nothing
    // EFFECTS: Returns the current training rate
    //========================================================================
    double getTrainingRate();
    //========================================================================
    // REQUIRES: One of the calculate<>Error methods to have been called
    // MODIFIES: Nothing
    // EFFECTS: Returns the product of the indexed weight and the current 
    //          error.
    //========================================================================
    double getWeightedError(unsigned int weight);
};

#endif