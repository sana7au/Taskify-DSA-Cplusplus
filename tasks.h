#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

class Task {
public:
    int id;
    string title;
    string description;
    string category;
    int priority;
    string deadline;   // YYYY-MM-DD
    string status;     // Active / Finished / Missed

    Task() 
    {
        id = 0;
        priority = 0;
        status = "Active";
    }

    Task(int _id, string _title, string _desc, string _cat, int _priority, string _deadline) 
    {
        id = _id;
        title = _title;
        description = _desc;
        category = _cat;
        priority = _priority;
        deadline = _deadline;
        status = "Active";
    }

    void displayInfo() const 
    {
        cout<<"\n------------------------------"<<endl;
        cout<<"Task ID: "<<id<<endl;
        cout<<"Title: "<<title<<endl;
        cout<<"Description: "<<description<<endl;
        cout<<"Category: "<<category<<endl;
        cout<<"Priority: "<<priority<<endl;
        cout<<"Deadline: "<<deadline<<endl;
        cout<<"Status: "<<status<<endl;
        cout<<"------------------------------"<<endl;
    }

    bool isDeadlinePassed() 
    {
        time_t now = time(0);
        tm deadline_tm = {};
        int y, m, d;

        if (sscanf(deadline.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
        {
            return false;
        }

        deadline_tm.tm_year = y - 1900;
        deadline_tm.tm_mon  = m - 1;
        deadline_tm.tm_mday = d;
        deadline_tm.tm_hour = 0;
        deadline_tm.tm_min  = 0;
        deadline_tm.tm_sec  = 0;

        time_t deadline_time = mktime(&deadline_tm);
        return now > deadline_time;
    }

    void markFinished()
    { 
        status = "Finished"; 
    }

    void markMissed()
    { 
        status = "Missed"; 
    }
};