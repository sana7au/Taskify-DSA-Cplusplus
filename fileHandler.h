#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class FileHandler {
public:
    string fileName;

    FileHandler(string name = "SummaryReport.txt") 
    {
        fileName = name;
    }

    void saveSummary(const string& summary) 
    {
        ofstream file(fileName, ios::app);

        if (!file.is_open()) 
        {
            cout<<"Error opening file!"<<endl;
            return;
        }
        file<<summary<<endl<<endl;
        file.close();
        cout<<"Summary saved!"<<endl;
    }

    void clearFile() 
    {
        ofstream file(fileName, ios::trunc);

        file.close();
        cout<<"File cleared!"<<endl;
    }
};