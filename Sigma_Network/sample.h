#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class sample : public enable_shared_from_this<sample>
{
private:
    vector<double> values;
    string classification;
public:
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    sample();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    ~sample();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void addValue(double value);
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void setClassification(string classification);
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    vector<double> getValues();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    string getClassification();
    //========================================================================
    // REQUIRES: 
    // MODIFIES: 
    // EFFECTS: 
    //========================================================================
    void printSample();
};

#endif