/*
    This is a test driver for Sigma Net, which is a simple Artificial Neural
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
//   File:      test.cpp
//   Author:    Michael Koonts
//   Date :     April 7, 2016
//============================================================================
#include "test.h"
//============================================================================
int main(int argc, char *argv[])
{
    

    // vector<double> tmp = typeToVector["setosa"];
    // printVector(tmp);
    // cout << endl;
    // cout << vectorToType[tmp] << endl;

    data data;
    data.init();
    //data.collectMetaData();
    data.printMetaData();
    //data.testQuery();

    shared_ptr<vector<sample>> dataSet = data.getDataSet(true);

    map<string, vector<double>> typeToVector = data.getTypeToVector();
    map<vector<double>, string> vectorToType = data.getVectorToType();
    map<string, int> sampleCounts = data.getSampleCounts();
    
    cout << "Before training" << endl;
    vector<double> input;
    vector<double> expected;
    vector<double> actual;
    double correct = 0;
    int i = 0;
    vector<sample>::iterator currentSample = dataSet->begin();
    network dnet(data.getTableName(), data.getAttributeCount(), data.getCatagoryCount(), HIDDEN_LAYERS, LAYER_SIZE);
    while(currentSample != dataSet->end()){
        //currentSample->printSample();
        input = currentSample->getValues();
        expected = typeToVector[currentSample->getClassification()];
        actual = dnet.push(input);
        if (data.classVector(data.getCatagoryCount(), catagorize(actual)) == expected) correct++;
        if (i % 100 == 0 && !QUIET) {
            cout << "Actual = ";
            printVector(actual);
            cout << " ";
            cout << "Expected = ";
            printVector(expected);
            cout << endl;
        }
        i++;
        currentSample++;
    }
    double total = data.getSampleCount();
    double percent = (correct / total) * 100;
    cout << correct << "/" << total << " = " << percent << "% correct." << endl;
    

    struct timeval profileStart, profileEnd;
    gettimeofday(&profileStart, NULL);

    int p = 0, oldp = -1;
    outputStatusMessage("Training the network");

    for (unsigned int g = 0; g < ITERATIONS; g++) {
        p = calcPercentageComplete(g, ITERATIONS);
        if (oldp < p) {
            oldp = updateOutputPercentage(p, false);
        }
        //int current = cat(engine);
        currentSample = dataSet->begin();
        while(currentSample != dataSet->end()){
            input = currentSample->getValues();
            expected = typeToVector[currentSample->getClassification()];
            actual = dnet.push(input);
            dnet.train(input, expected);
            currentSample++;
        }
    }
    updateOutputPercentage(p, true);

    gettimeofday(&profileEnd, NULL);
    PrintTimeDifference(profileStart, profileEnd);
    cout << "After training" << endl;
    dataSet = data.getDataSet(false);
    currentSample = dataSet->begin();
    correct = 0;
    i = 0;
    while(currentSample != dataSet->end()){
        //currentSample->printSample();
        input = currentSample->getValues();
        expected = typeToVector[currentSample->getClassification()];
        actual = dnet.push(input);
        if (data.classVector(data.getCatagoryCount(), catagorize(actual)) == expected) correct++;
        if (i % 100 == 0 && !QUIET) {
            cout << i << ") Actual = ";
            printVector(actual);
            cout << " ";
            cout << "Expected = ";
            printVector(expected);
            cout << endl;
        }
        i++;
        currentSample++;
    }
    //cout << i << endl;
    total = data.getSampleCount();
    percent = (correct / total) * 100;
    cout << correct << "/" << total << " = " << percent << "% correct." << endl;
    dnet.writeNetwork();
    //percent = 0;
    //double oldPercent = 0;
    // network net("test", ATTRIBUTES, CATAGORIES, HIDDEN_LAYERS, LAYER_SIZE);
    // network rnet("test");


    //percent = push(net, 0);

    // if (rnet.restoreNetwork()) {
    //     cout << "Restoring saved network." << endl;
    //     oldPercent = push(rnet, 0);
    // }

    //train(net, ITERATIONS);

    //cout << "After training" << endl;
    //percent = push(net, TRAINING_SAMPLES);

    // if (percent > oldPercent) {
    //     net.writeNetwork();
    // }
    // system("pause");
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
double push(network net, int start)
{
    vector<double> input;
    vector<double> expected;
    vector<double> actual;
    double correct = 0;
    for (unsigned int h = 0; h < CATAGORIES; h++) {
        for (unsigned int i = start; i < SAMPLES; i++) {
            input = convert(DATA[h][i], ATTRIBUTES);
            expected = convert(catagory[h], CATAGORIES);
            actual = net.push(input);
            if (catagorize(actual) == h) correct++;
            if (i % 10 == 0 && !QUIET) {
                cout << "Actual = ";
                printVector(actual);
                cout << " ";
                cout << "Expected = ";
                printVector(expected);
                cout << endl;
            }
        }
    }
    double total = ((SAMPLES * CATAGORIES) - (start * CATAGORIES));
    double percent = (correct / total) * 100;
    cout << correct << "/" << total << " = " << percent << "% correct." << endl;
    return percent;
}
//============================================================================
void train(network net, int iterations)
{
    vector<double> input;
    vector<double> expected;
    vector<double> actual;
    mt19937 engine;
#if WINDOWSSYSTEM
    FILETIME tStart, tEnd;
    GetSystemTimeAsFileTime(&tStart);
#else
    struct timeval profileStart, profileEnd;
    gettimeofday(&profileStart, NULL);
#endif
    engine.seed(random_device()());
    uniform_int_distribution<int> cat(0, 2);
    uniform_int_distribution<int> sample(0, 11);

    int percent = 0, oldpercent = -1;
    outputStatusMessage("Training the network");

    for (unsigned int g = 0; g < iterations; g++) {
        percent = calcPercentageComplete(g, iterations);
        if (oldpercent < percent) {
            oldpercent = updateOutputPercentage(percent, false);
        }
        int current = cat(engine);
        input = convert(DATA[current][sample(engine)], ATTRIBUTES);
        expected = convert(catagory[current], CATAGORIES);
        actual = net.push(input);
        net.train(input, expected);
    }
    updateOutputPercentage(percent, true);
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