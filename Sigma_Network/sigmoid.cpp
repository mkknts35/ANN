/*
    This is a class implementation for Sigma Net, which is a simple 
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
//   File:      sigmoid.cpp
//   Author:    Michael Koonts
//   Date :     April 7, 2016
//============================================================================
#include "sigmoid.h"
//============================================================================
// public
//============================================================================
sigmoid::sigmoid(
    vector <shared_ptr<double>> input,
    shared_ptr<double> output,
    bool hidden) : neuron(input, output, hidden){}
//============================================================================
sigmoid::~sigmoid(){}
//============================================================================
// protected
//============================================================================
double sigmoid::activate(double x)
{
    return 1 / (1 + exp((-1) * x));
}
//============================================================================