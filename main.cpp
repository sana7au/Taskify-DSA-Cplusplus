#include <iostream>
#include "taskManager.h"

using namespace std;

int main() {
    TaskManager manager;
    int choice;

    while (true) 
    {
        cout<<"\n========== TASK MENU =========="<<endl;
        cout<<"1. Add Task"<<endl;
        cout<<"2. Delete Task"<<endl;
        cout<<"3. Undo Delete"<<endl;
        cout<<"4. Mark Finished"<<endl;
        cout<<"5. Auto Move Missed Tasks"<<endl;
        cout<<"6. Search by Category"<<endl;
        cout<<"7. Show Active Tasks"<<endl;
        cout<<"8. Show All Stacks"<<endl;
        cout<<"9. Export Summary"<<endl;
        cout<<"10. Exit"<<endl;

        cout<<"Enter your choice: ";
        cin>>choice;
        cin.ignore();
        
        switch (choice)
        {
        case 1: {
            manager.addTask();

            break;
        }

        case 2: {
            int id;
            cout<<"Enter ID to delete: ";
            cin>>id;
            cin.ignore();
            manager.deleteTask(id);

            break;
        }

        case 3: {
            manager.undoDelete();

            break;
        }

        case 4: {
            int id;
            cout<<"Enter ID to finish: ";
            cin>>id;
            cin.ignore();
            manager.markFinished(id);

            break;
        }

        case 5: {
            manager.autoMoveMissedTasks();

            break;
        }

        case 6: {
            string cat;
            cout<<"Enter category: ";
            getline(cin, cat);
            manager.searchByCategory(cat);

            break;
        }

        case 7: {
            manager.showAllActiveTasks();

            break;
        }

        case 8: {
            manager.showAllStacks();

            break;
        }

        case 9: {
            manager.exportSummary();

            break;
        }

        case 10: {
            cout<<"Saving summary..."<<endl;
            manager.exportSummary();
            cout<<"Goodbye!"<<endl;

            break;
        }
        
        default: {
            cout<<"Invalid Input! "<<endl;
            break;
        }

        }

        cout<<"\nPress any key to continue...";
        cin.get();
    }

    return 0;
}