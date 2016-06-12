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
void sigmoid::train(double expected)
{
    if (m_hidden) {
        calculateHiddenError(expected);
    } else {
        calculateOutputError(expected);
    }
    for (unsigned int i = 0; i < m_weight.size(); i++) {
        adjustWeight(i, delta(i));
    }
    m_trianingRate -= (m_trianingRate * DECAY_RATE);
}
//============================================================================
void sigmoid::push()
{
    double sum = 0;
    for (unsigned int i = 0; i < m_input.size(); i++) {
        sum += *m_input.at(i) * m_weight.at(i);
    }
    *m_output = sigma(sum);
}
//============================================================================
// private
//============================================================================
void sigmoid::adjustWeight(unsigned int weight, double delta)
{
    m_weight.at(weight) += delta;
}
//============================================================================
void sigmoid::calculateOutputError(double expected)
{
    m_error = *m_output * (1 - *m_output) * (expected - *m_output);
    m_oldWeight = vector<double>(m_weight);
}
//============================================================================
void sigmoid::calculateHiddenError(double expected)
{
    m_error = *m_output * (1 - *m_output) * expected;
    m_oldWeight = vector<double>(m_weight);
}
//============================================================================
double sigmoid::sigma(double x)
{
    return 1 / (1 + exp((-1) * x));
}
//============================================================================
double sigmoid::delta(unsigned int i)
{
    return m_trianingRate * m_error * (*m_input.at(i));
}
//============================================================================