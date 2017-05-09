//============================================================================
//   File:          ann.h
//   Author:        Michael Koonts
//   Date:          April 14, 2017
//============================================================================
#include <stdlib.h>
#include <iostream>
#include <random>
#include <map>

#include "network.h"
#include "util.h"
#include "data.h"
#include "sample.h"
//============================================================================
const unsigned int HIDDEN_LAYERS = 2;
const unsigned int LAYER_SIZE = 14;
const unsigned int ITERATIONS = 5000;
//============================================================================
Data m_data;
shared_ptr<vector<sample>> m_dataSet;
map<string, vector<double>> m_typeToVector;
map<vector<double>, string> m_vectorToType;
map<string, int> m_sampleCounts;
bool m_quiet = false;
//============================================================================
vector<double> convert(const double raw[], int size);
//============================================================================
int catagorize(vector<double> raw);
//============================================================================
double push(network net, shared_ptr<vector<sample>> dataSet);
//============================================================================
void train(network net, shared_ptr<vector<sample>> dataSet);
//============================================================================
void printVector(vector<double> vec);
//============================================================================