#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "tasks.h"

using namespace std;

class StackManager {
public:
    vector<Task> stackData;
    string stackType;

    StackManager() 
    {
        stackType = " ";
    }

    StackManager(string type) 
    { 
        stackType = type; 
    }

    void pushTask(const Task& t) 
    {
        stackData.push_back(t);
    }

    Task popTask() 
    {
        Task topTask;
        if (stackData.empty())
        {
            return topTask;
        }
        topTask = stackData.back();
        stackData.pop_back();
        return topTask;
    }

    Task peekTask() 
    {
        Task topTask;
        if (stackData.empty())
        {
            return topTask;
        }
        return stackData.back();
    }

    bool isEmpty() 
    { 
        return stackData.empty(); 
    }

    void displayAll() 
    {
        cout<<"\n=== "<<stackType<<" Tasks ==="<<endl;

        if (stackData.empty()) 
        {
            cout<<"No tasks"<<endl;
            return;
        }

        for (int i = (int)stackData.size() - 1; i >= 0; i--) 
        {
            stackData[i].displayInfo();
        }
    }
};