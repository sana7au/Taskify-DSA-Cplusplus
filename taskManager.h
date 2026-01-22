#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "priorityQueueManager.h"
#include "stackManager.h"
#include "hashTableManager.h"
#include "fileHandler.h"

using namespace std;

class TaskManager {
public:
    PriorityQueueManager priorityQueue;
    StackManager finishedStack {"Finished"};
    StackManager missedStack {"Missed"};
    StackManager undoStack {"Undo"};
    HashTableManager hashTable;
    FileHandler fileHandler {"SummaryReport.txt"};

    int taskCounter = 1;

    void addTask();
    void deleteTask(int id);
    void undoDelete();
    void markFinished(int id);
    void autoMoveMissedTasks();
    void searchByCategory(string category);
    string generateSummary();
    void exportSummary();
    void showAllActiveTasks();
    void showAllStacks();
};

inline void TaskManager::addTask() 
{
    string title, desc, category, deadline;
    int priority;

    cout<<"Enter title: ";
    getline(cin, title);

    cout<<"Enter description: ";
    getline(cin, desc);

    cout<<"Enter category: ";
    getline(cin, category);

    cout<<"Enter priority (1-10): ";
    cin>>priority;
    cin.ignore();

    cout<<"Enter deadline (YYYY-MM-DD): ";
    getline(cin, deadline);

    Task t(taskCounter++, title, desc, category, priority, deadline);
    priorityQueue.addTask(t);
    hashTable.insertTask(t);

    cout<<"Task added"<<endl;
}

inline void TaskManager::deleteTask(int id) 
{
    Task removed;
    bool found = priorityQueue.removeTaskById(id, removed);

    if (found) 
    {
        undoStack.pushTask(removed);
        hashTable.removeTask(removed);
        cout<<"Task deleted"<<endl;
    } 
    else 
    {
        cout<<"Task not found"<<endl;
    }
}

inline void TaskManager::undoDelete() 
{
    if (undoStack.isEmpty()) 
    {
        cout<<"Undo stack empty"<<endl;
        return;
    }

    Task t = undoStack.popTask();
    t.status = "Active";

    priorityQueue.addTask(t);
    hashTable.insertTask(t);

    cout<<"Undo successful"<<endl;
}

inline void TaskManager::markFinished(int id) 
{
    Task finishedT;
    bool found = priorityQueue.removeTaskById(id, finishedT);

    if (found) 
    {
        finishedT.markFinished();
        finishedStack.pushTask(finishedT);
        hashTable.removeTask(finishedT);
        cout<<"Task finished"<<endl;
    } 
    else 
    {
        cout<<"Task not found"<<endl;
    }
}

inline void TaskManager::autoMoveMissedTasks() 
{
    vector<Task> all = priorityQueue.extractAll();
    vector<Task> stillActive;

    for (int i = 0; i < (int)all.size(); i++) 
    {
        if (all[i].isDeadlinePassed()) 
        {
            all[i].markMissed();
            missedStack.pushTask(all[i]);
            hashTable.removeTask(all[i]);
        } 
        else 
        {
            stillActive.push_back(all[i]);
        }
    }

    priorityQueue.buildFrom(stillActive);
    cout<<"Missed tasks moved"<<endl;
}

inline void TaskManager::searchByCategory(string cat) 
{
    hashTable.displayCategory(cat);
}

inline string TaskManager::generateSummary() 
{
    int active = priorityQueue.size();
    int finished = (int)finishedStack.stackData.size();
    int missed = (int)missedStack.stackData.size();
    int undoCount = (int)undoStack.stackData.size();

    string summary = "=== SUMMARY REPORT ===\n";
    summary += "Total tasks created: " + to_string(taskCounter - 1) + "\n";
    summary += "Active tasks: " + to_string(active) + "\n";
    summary += "Finished tasks: " + to_string(finished) + "\n";
    summary += "Missed tasks: " + to_string(missed) + "\n";
    summary += "Deleted tasks (Undo Stack): " + to_string(undoCount) + "\n\n";
    summary += hashTable.buildCategoryCountsString();
    
    return summary;
}

inline void TaskManager::exportSummary() 
{
    fileHandler.saveSummary(generateSummary());
}

inline void TaskManager::showAllActiveTasks() 
{
    priorityQueue.displayAll();
}

inline void TaskManager::showAllStacks() 
{
    finishedStack.displayAll();
    missedStack.displayAll();
    undoStack.displayAll();
}