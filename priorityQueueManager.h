#pragma once
#include <iostream>
#include <vector>
#include "tasks.h"

using namespace std;

class PriorityQueueManager {
private:
    vector<Task> heap;

    bool higher(const Task& a, const Task& b) const 
    {
        if (a.priority != b.priority)
        {
            return a.priority > b.priority;  // bigger = more urgent
        }

        if (a.deadline != b.deadline)
        {
            return a.deadline < b.deadline;  // earlier first
        }

        return a.id < b.id;
    }

    void swapTasks(Task& a, Task& b) 
    {
        Task temp = a;
        a = b;
        b = temp;
    }

    void heapifyUp(int i) 
    {
        while (i > 0) 
        {
            int parent = (i - 1) / 2;

            if (higher(heap[i], heap[parent])) 
            {
                swapTasks(heap[i], heap[parent]);
                i = parent;
            } 
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int i) 
    {
        int n = (int)heap.size();

        while (true) 
        {
            int left = i * 2 + 1;
            int right = i * 2 + 2;
            int best = i;

            if (left < n && higher(heap[left], heap[best]))
            {
                best = left;
            }

            if (right < n && higher(heap[right], heap[best]))
            {
                best = right;
            }

            if (best != i) 
            {
                swapTasks(heap[i], heap[best]);
                i = best;
            } 
            else 
            {
                break;
            }
        }
    }

public:
    void addTask(const Task& t) 
    {
        heap.push_back(t);
        heapifyUp((int)heap.size() - 1);
    }

    bool isEmpty() 
    { 
        return heap.empty(); 
    }

    int size() 
    { 
        return (int)heap.size(); 
    }

    Task getTopTask() 
    {
        Task t;
        if (heap.empty())
        {
            return t;
        }
        return heap[0];
    }

    void popTopTask() 
    {
        if (heap.empty())
        {
            return;
        }

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
        {
            heapifyDown(0);
        }
    }

    bool removeTaskById(int id, Task& removed) 
    {
        int index = -1;

        for (int i = 0; i < (int)heap.size(); i++) 
        {
            if (heap[i].id == id) 
            { 
                index = i; break; 
            }
        }

        if (index == -1)
        {
            return false;
        }

        removed = heap[index];

        heap[index] = heap.back();
        heap.pop_back();

        if (index < (int)heap.size()) 
        {
            heapifyDown(index);
            heapifyUp(index);
        }
        return true;
    }

    vector<Task> extractAll() 
    {
        vector<Task> all = heap;
        heap.clear();
        return all;
    }

    void buildFrom(const vector<Task>& items) 
    {
        heap = items;

        for (int i = (int)heap.size() / 2 - 1; i >= 0; i--) 
        {
            heapifyDown(i);
            if (i == 0)
            {
                break;
            }
        }
    }

    void displayAll() 
    {
        cout<<"\n=== Active Tasks (Top = Most Urgent) ==="<<endl;
        if (heap.empty()) 
        {
            cout<<"No active tasks"<<endl;
            return;
        }

        PriorityQueueManager temp;
        temp.buildFrom(heap);

        while (!temp.isEmpty()) 
        {
            temp.getTopTask().displayInfo();
            temp.popTopTask();
        }
    }
};