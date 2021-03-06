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
//   File:      neuron.cpp
//   Author:    Michael Koonts
//   Date :     June 11, 2016
//============================================================================
#include "neuron.h"
//============================================================================
neuron::neuron(
    vector<shared_ptr<double>> input,
    shared_ptr<double> output,
    bool hidden)
{
    m_input = input;
    m_output = output;
    m_hidden = hidden;
    mt19937 engine;
    engine.seed(random_device()());
    uniform_real_distribution<double> dist(0, 1);
    for (unsigned int i = 0; i < m_input.size(); i++) {
        m_weight.push_back(dist(engine));
    }
}
//============================================================================
neuron::~neuron(){}
//============================================================================
void neuron::train(double expected)
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
void neuron::push()
{
    double sum = 0;
    for (unsigned int i = 0; i < m_input.size(); i++) {
        sum += *m_input.at(i) * m_weight.at(i);
    }
    *m_output = activate(sum);
}
//============================================================================
void neuron::setWeights(vector<double> weights)
{
    m_weight = weights;
}
//============================================================================
vector<double> neuron::getWeights()
{
    return m_weight;
}
//============================================================================
void neuron::setTrainingRate(double rate)
{
    m_trianingRate = rate;
}
//============================================================================
double neuron::getTrainingRate()
{
    return m_trianingRate;
}
//============================================================================
double neuron::getWeightedError(unsigned int weight)
{
    return m_error * m_oldWeight.at(weight);
}
//============================================================================
// protected
//============================================================================
void neuron::adjustWeight(unsigned int weight, double delta)
{
    m_weight.at(weight) += delta;
}
//============================================================================
void neuron::calculateOutputError(double expected)
{
    m_error = *m_output * (1 - *m_output) * (expected - *m_output);
    m_oldWeight = vector<double>(m_weight);
}
//============================================================================
void neuron::calculateHiddenError(double expected)
{
    m_error = *m_output * (1 - *m_output) * expected;
    m_oldWeight = vector<double>(m_weight);
}
//============================================================================
double neuron::delta(unsigned int i)
{
    return m_trianingRate * m_error * (*m_input.at(i));
}
//============================================================================