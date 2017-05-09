/*
    This is a driver for Sigma Net, which is a simple Artificial Neural
    Network

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
//   File:      ann.cpp
//   Author:    Michael Koonts
//   Date :     April 14, 2017
//============================================================================
#include "ann.h"
//============================================================================
int main(int argc, char **argv)
{
    if(argc < 5) return 1;
    //convert argv into std::string
    /*This seems like a strange thing to have to do, but I was getting some
    really odd behavour parsing out the command line args.  This seems to have
    eliminated the problem.*/
    string args[10];
    for(int i = 0; i < argc; i++){
        args[i] = argv[i];
    }
    string db, tb;
    bool valid[2] = {0,0};
    for(int i = 1; i < argc; i++){
        if (args[i] == "-d") {
            db = args[i + 1];
            valid[0] = true;
            i++;
        } else if (args[i] == "-t") {
            tb = args[i + 1];
            valid[1] = true;
            i++;
        } else if (args[i] == "-q"){
            m_quiet = true;
        } else { 
            cout << args[i] << " is not a valid option" << endl;
        }
    }
    if (!valid[0] || !valid[1]) return 1;

    m_data.init(db, tb);
    m_data.printMetaData();

    m_dataSet = m_data.getDataSet(true);
    m_typeToVector = m_data.getTypeToVector();
    m_vectorToType = m_data.getVectorToType();
    m_sampleCounts = m_data.getSampleCounts();

    double percent = 0, oldPercent = 0;
    shared_ptr<vector<sample>> dataSet;
    network dnet(m_data.getTableName());
    if (dnet.restoreNetwork()) {
        cout << "Restoring saved network." << endl;
        dataSet = m_data.getDataSet(false);
        oldPercent = push(dnet, dataSet);
        if(oldPercent < 95) {
            cout << "Saved network is not accurate enough." << endl;
            cout << "Attempting to improve it...";
            train(dnet, m_data.getDataSet(true));
            percent = push(dnet, m_data.getDataSet(false));
            if (percent > oldPercent) {
                cout << "Saving improved network." << endl;
                dnet.writeNetwork();
            } 
        }
    } else {
        network dnet(m_data.getTableName(), 
                        m_data.getAttributeCount(), 
                        m_data.getCatagoryCount(), 
                        m_data.getCatagoryCount() / 2, 
                        m_data.getAttributeCount() * 2);
        dataSet = m_data.getDataSet(true);
        cout << "Before training" << endl;
        oldPercent = push(dnet, dataSet);
        train(dnet, dataSet);
        cout << "After training" << endl;
        dataSet = m_data.getDataSet(false);
        percent = push(dnet, dataSet);
        if (percent > oldPercent) {
           dnet.writeNetwork();
        }
    }
    return 0;
}
//============================================================================
vector<double> convert(const double raw[], int size)
{
    vector<double> converted;
    for (int i = 0; i < size; i++) {
        converted.push_back(raw[i]);
    }
    return converted;
}
//============================================================================
int catagorize(vector<double> raw)
{
    int index = 0;
    double current = raw.at(index);
    for (int i = 0; i < raw.size(); i++) {
        if (current < raw.at(i)) {
            current = raw.at(i);
            index = i;
        }
    }
    return index;
}
//============================================================================
double push(network net, shared_ptr<vector<sample>> dataSet)
{
    vector<double> input;
    vector<double> expected;
    vector<double> actual;
    double correct = 0;
    int i = 0;
    vector<sample>::iterator currentSample = dataSet->begin();
    //network dnet(data.getTableName(), data.getAttributeCount(), data.getCatagoryCount(), HIDDEN_LAYERS, LAYER_SIZE);
    while(currentSample != dataSet->end()){
        //currentSample->printSample();
        input = currentSample->getValues();
        expected = m_typeToVector[currentSample->getClassification()];
        actual = net.push(input);
        if (m_data.classVector(m_data.getCatagoryCount(), catagorize(actual)) == expected) correct++;
        if (i % 10 == 0 && !m_quiet) {
            cout << "Actual = ";
            printVector(actual);
            cout << " ";
            cout << "Expected = ";
            printVector(expected);
            if (m_data.classVector(m_data.getCatagoryCount(), catagorize(actual)) != expected){
                cout << " x";
            }
            cout << endl;
        }
        i++;
        currentSample++;
    }
    double total = m_data.getSampleCount();
    double percent = (correct / total) * 100;
    cout << correct << "/" << total << " = " << percent << "% correct." << endl;
    return percent;
}
//============================================================================
void train(network net, shared_ptr<vector<sample>> dataSet)
{
    vector<double> input;
    vector<double> expected;
    vector<double> actual;
    vector<sample>::iterator currentSample = dataSet->begin();
#if WINDOWSSYSTEM
	FILETIME tStart, tEnd;
	GetSystemTimeAsFileTime(&tStart);
#else
	struct timeval profileStart, profileEnd;
	gettimeofday(&profileStart, NULL);
#endif
    int p = 0, oldp = -1;
    int iterations = m_data.getSampleCount() * ITERATIONS;
    outputStatusMessage("Training the network");

    for (unsigned int g = 0; g < ITERATIONS; g++) {
        p = calcPercentageComplete(g, ITERATIONS);
        if (oldp < p) {
            oldp = updateOutputPercentage(p, false);
        }
        currentSample = dataSet->begin();
        while(currentSample != dataSet->end()){
            input = currentSample->getValues();
            expected = m_typeToVector[currentSample->getClassification()];
            actual = net.push(input);
            net.train(input, expected);
            currentSample++;
        }
    }
    updateOutputPercentage(p, true);
#if WINDOWSSYSTEM
	GetSystemTimeAsFileTime(&tEnd);
	PrintTimeDifference(tStart, tEnd);
#else
	gettimeofday(&profileEnd, NULL);
	PrintTimeDifference(profileStart, profileEnd);
#endif
}
//============================================================================
void printVector(vector<double> vec)
{
    cout << "(";
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec.at(i);
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")";
}
//============================================================================