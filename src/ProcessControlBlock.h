#ifndef _PROCESS_CONTROL_BLOCK_H_
#define _PROCESS_CONTROL_BLOCK_H_

#include <vector>

using namespace std;

class ProcessControlBlock
{
private:
    int pid;                            // Unique id of the process
    vector<ProcessControlBlock *> childProcesses; // Pointers of all children of the process
    int parentProcess;                 // The pid of the parent of the process
    bool zombieProcess;             // True is process is a zombie process, false otherwise
    bool waiting;                       // True if this process is waiting for a child process to terminate.

public:
    ProcessControlBlock(int &pid) : pid(pid), childProcesses(0), parentProcess(0), zombieProcess(0), waiting(0) {}

    ~ProcessControlBlock()
    {
        for (auto child : childProcesses)
        {
            delete child;
        }
        ClearChildren();
    }

    int GetPid() const
    {
        return pid;
    }

    // Adds a pointer to a child process of this ProcessControlBlock
    void AddChildProcess(ProcessControlBlock *child_process)
    {
        childProcesses.push_back(child_process);
    }

    // Sets the process to waiting or not waiting
    void SetWaitingState(bool state)
    {
        waiting = state;
    }

    // Marks the process as a zombie (1) or not a zombie (0)
    void SetZombie(bool state)
    {
        zombieProcess = state;
    }

    // Returns true if the process is waiting, otherwise returns false
    bool IsWaiting()
    {
        return waiting;
    }

    // Returns true if the process is a zombie process. Returns false otherwise
    bool IsZombieProcess() const
    {
        return zombieProcess;
    }

    // If the process has a child that is a zombie, returns the pid of that child. If it does not, returns 0.
    int ProcessHasZombieChild() const
    {
        for (auto itr = childProcesses.begin(); itr != childProcesses.end(); itr++)
        {
            if ((*itr)->zombieProcess)
            {
                return (*itr)->pid;
            }
        }
        return 0;
    }

    // Returns true if the process has children.
    bool HasChildren() const
    {
        return !childProcesses.empty();
    }

    // When called on a process, removes the given child if it is found in childProcesses.
    void RemoveChild(ProcessControlBlock *&child)
    {
        for (auto itr = childProcesses.begin(); itr != childProcesses.end(); itr++)
        {
            if ((*itr) == child)
            {
                childProcesses.erase(itr);
                return;
            }
        }
    }

    // Sets the parent pid of a process
    void SetParent(const int parent_pid)
    {
        parentProcess = parent_pid;
    }

    // Returns the parent pid of a process
    int GetParent()
    {
        return parentProcess;
    }

    // Returns a constant reference to the vector of child processes.
    const vector<ProcessControlBlock *> &GetChildren() const
    {
        return childProcesses;
    }

    // Clears the vector of child processes.
    void ClearChildren()
    {
        childProcesses.clear();
    }
};

#endif // _PROCESS_CONTROL_BLOCK_H_