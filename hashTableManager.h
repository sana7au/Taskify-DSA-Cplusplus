#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "tasks.h"

using namespace std;

class HashTableManager {
private:
    int tableSize;
    vector< list<Task> > table;

    int stringToKey(const string& s) 
    {
        int sum = 0;
        for (int i = 0; i < (int)s.length(); i++)
        {
            sum += (int)s[i];
        }
        return sum;
    }

    int divisionHash(const string& key) 
    {
        int k = stringToKey(key);
        if (k < 0)
        {
            k = -k;
        }
        return k % tableSize;
    }

public:
    HashTableManager(int size = 31) 
    {
        tableSize = size;
        table.resize(tableSize);
    }

    void insertTask(const Task& t) 
    {
        int index = divisionHash(t.category);
        table[index].push_back(t);
    }

    void removeTask(const Task& t) 
    {
        int index = divisionHash(t.category);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) 
        {
            if (it->id == t.id) 
            {
                table[index].erase(it);
                return;
            }
        }
    }

    void displayCategory(const string& cat) 
    {
        int index = divisionHash(cat);

        cout<<"\n=== Tasks in category: "<<cat<<" ==="<<endl;
        bool found = false;

        for (auto& t : table[index]) 
        {
            if (t.category == cat) 
            {
                t.displayInfo();
                found = true;
            }
        }

        if (!found) 
        {
            cout<<"No tasks found in this category"<<endl;
        }
    }

    int countCategory(const string& cat) 
    {
        int index = divisionHash(cat);
        int c = 0;
        for (auto& t : table[index])
        {
            if (t.category == cat)
            {
                c++;
            }
        }
        return c;
    }

    string buildCategoryCountsString() 
    {
        string s = "Category-wise count: \n";
        vector<string> seen;

        for (int i = 0; i < tableSize; i++) 
        {
            for (auto& t : table[i]) 
            {
                bool exists = false;
                for (int k = 0; k < (int)seen.size(); k++) 
                {
                    if (seen[k] == t.category) 
                    { 
                        exists = true; 
                        break; 
                    }
                }
                if (!exists)
                {
                    seen.push_back(t.category);
                }
            }
        }

        if (seen.empty()) 
        {
            s += " - (none)\n";
            return s;
        }

        for (int i = 0; i < (int)seen.size(); i++) 
        {
            s += " - " + seen[i] + " : " + to_string(countCategory(seen[i])) + "\n";
        }
        return s;
    }
};