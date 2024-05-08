#include <bits/stdc++.h>
using namespace std;
typedef long long int li;
#define lc cout << "--------------------------------------------------------" << endl;
const li MOD = 1e9 + 7;

vector<vector<li>> chunksPlacement; // this data structure stores the vectors {timstamp,machine,job,chunk} for a valid scheduling(for minimum number of machines)
vector<set<li>> assignedChunks;     // this data structure stores the final assignment of chunks to machine(for minimum number of machines), if it there exists a valid scheduling
vector<pair<li, li>> finishTimes;   // this data structure stores the finishing times for all jobs

bool sortByCond(const vector<li> &a, const vector<li> &b) // this is used to order the chunksPlacement data structure to print the data in order to timestamps
{
    if (a[0] != b[0])
        return a[0] < b[0];
    if (a[1] != b[1])
        return a[1] < b[1];
    if (a[2] != b[2])
        return a[2] < b[2];
    return a[3] < b[3];
}

// for some number of machines,we want to check if there exists assignments and scheduling
bool checkScheduling(li chunks, li jobs, vector<multiset<li>> adj, vector<li> dj, li b, li s, li machines)
{
    vector<set<li>> assignedChunksForMachine(machines); // this data structure stores the assignment of chunks to machine for a particular number of machines

    li unSatisfied = jobs;                               // stores the count of unsatisfied jobs
    li maxDeadline = *max_element(dj.begin(), dj.end()); // deadline of the job that finishes last

    vector<pair<li, li>> deadlines; // stores the pair <deadline,job>
    for (li i = 0; i < jobs; i++)
    {
        pair<li, li> r = {dj[i], i};
        deadlines.push_back(r);
    }
    sort(deadlines.begin(), deadlines.end()); // we sort this data structure as we want to analyze the job that finishes the earliest

    li ptr = 0; // counter variable

    vector<vector<set<li>>> assignedAt(machines, vector<set<li>>(maxDeadline + 1));   // stores the chunks which are being executed by a machine at a partcular time stamp
    vector<vector<li>> busyVirtualMachines(machines, vector<li>(maxDeadline + 1, 0)); // stores the number of busy virtual machines at a particular time stamp

    vector<vector<li>> chunksPlacementForMachine; // this data structure stores the vectors {timstamp,machine,job,chunk} for a particular number of machines
    vector<pair<li, li>> finishTimesForMachine;   // this data structure stores the finish times of jobs when they are excuted with some number of machines

    for (li i = 1; i <= maxDeadline; i++) // iterate till the largest deadline
    {
        while (unSatisfied) // if there still exists an unsatisfied job
        {
            queue<li> q;
            li job = deadlines[ptr].second;      // job id
            multiset<li> totalChunks = adj[job]; // total unassigned chunks for that job
            for (auto i : totalChunks)           // put them in a queue
                q.push(i);
            li prev = q.size();                              // storing queue size initially
            li deadlineForCurrentJob = deadlines[ptr].first; // deadline for the job under consideration
            while (!q.empty())                               // till there exists any unassigned chunk
            {
                li chunk = q.front();                               // first unassigned chunk
                for (li machine = 0; machine < machines; machine++) // iterate through all machines
                {
                    if (assignedChunksForMachine[machine].count(chunk)) // if this chunk was already assigned to this machine
                    {
                        bool c = false;                                                         // check variable
                        for (li timestamp = i; timestamp <= deadlineForCurrentJob; timestamp++) // iterate through the allowed timestamps
                        {
                            if (busyVirtualMachines[machine][timestamp] < s && !assignedAt[machine][timestamp].count(chunk)) // if there exists any valid timestamp which has atleast one idle virtual machine and that chunk is not being executed by that machine at that time stamp
                            {
                                // execute this chunk on this machine
                                busyVirtualMachines[machine][timestamp]++;                                     // number of busy virtual machines increases
                                assignedAt[machine][timestamp].insert(chunk);                                  // now the chunk is being used by this machine at this timestamp
                                totalChunks.erase(totalChunks.find(chunk));                                    // chunk erase from the list of chunks of job
                                chunksPlacementForMachine.push_back({timestamp, machine + 1, chunk, job + 1}); // updated chunk placement
                                q.pop();                                                                       // chunk removed from queue
                                if (q.size() == 0)                                                             // job finishes execution
                                    finishTimesForMachine.push_back({job, timestamp});
                                c = true;
                                break;
                            }
                        }
                        if (c)
                            break; // go to next chunk/job
                    }
                    else if (assignedChunksForMachine[machine].size() != b) // if this chunk was not assigned to the machine
                    {
                        bool c = false;                                                         // check variable
                        for (li timestamp = i; timestamp <= deadlineForCurrentJob; timestamp++) // iterate through the allowed timestamps
                        {
                            if (busyVirtualMachines[machine][timestamp] < s) // if there exists any valid timestamp which has atleast one idle virtual machine
                            {
                                // execute this chunk on this machine
                                busyVirtualMachines[machine][timestamp]++;                                     // number of busy virtual machines increases
                                assignedAt[machine][timestamp].insert(chunk);                                  // now the chunk is being used by this machine at this timestamp
                                totalChunks.erase(totalChunks.find(chunk));                                    // chunk erase from the list of chunks of job
                                assignedChunksForMachine[machine].insert(chunk);                               // chunk is now assigned to this machine
                                chunksPlacementForMachine.push_back({timestamp, machine + 1, chunk, job + 1}); // updated chunk placement
                                q.pop();                                                                       // chunk removed from queue
                                if (q.size() == 0)
                                    finishTimesForMachine.push_back({job, timestamp}); // job finishes execution
                                c = true;
                                break;
                            }
                        }
                        if (c)
                            break; // go to next chunk/job
                    }
                }
                if (q.size() == prev) // chunk couldn't be assigned to any machine at any time stamp, scheduling not possible
                    return false;
                prev = q.size(); // updated queue size
            }
            adj[deadlines[ptr].second] = totalChunks; // updated list of unassigned chunks
            if (totalChunks.size() == 0)              // all chunks assigned for that job
            {
                unSatisfied--; // job satisfied
                ptr++;         // go to next job
            }
        }
        if (unSatisfied == 0) // all jobs satisfied
        {
            // storing as final assignment(when the code ends, this corresponds to minimum number of machines)
            chunksPlacement = chunksPlacementForMachine;
            assignedChunks = assignedChunksForMachine;
            finishTimes = finishTimesForMachine;
            return true;
        }
    }
    // all jobs couldn't be satisfied(try putting the deadlines as 0)
    // if (unSatisfied != 0)
        return false;
    // cout << "Not all jobs satisfied" << endl;
}

int main()
{

    li choice;
    bool check = false;
    cout << "Enter 1 for your own test case\nEnter 2 for test case taken from readme.md/testcasegenerator.cpp" << endl;
    cin >> choice;

    if (choice == 1)
        check = true;

    if (!check)
        cout << "Enter the numbers = ";

    // taking inputs
    if (check)
        cout << "Enter number of virtual machines on a machine(s) = ";
    li s;
    cin >> s;

    if (check)
        cout << "Enter the max number of chunks that can be assigned to a machine(b) = ";
    li b;
    cin >> b;

    if (check)
        cout << "Enter the max number of different chunks = ";
    li chunks;
    cin >> chunks;

    if (check)
        cout << "Enter number of jobs = ";
    li jobs;
    cin >> jobs;

    // storing total number of chunks assigned to all jobs
    li sumOfChunks = 0;

    // storing the chunks assigned to all jobs
    vector<multiset<li>> adj(jobs);

    // storing deadlines for all jobs
    vector<li> dj(jobs);
    for (li i = 0; i < jobs; i++)
    {
        if (check)
            cout << "Enter deadline of job " << i + 1 << " = ";
        cin >> dj[i];

        if (check)
            cout << "Enter number of chunks to be executed for job " << i + 1 << " = ";
        li k;
        cin >> k;

        sumOfChunks += k;
        if (check)
            cout << "Enter the chunks = ";
        for (li j = 0; j < k; j++)
        {
            li chunk;
            cin >> chunk;
            adj[i].insert(chunk);
        }
    }

    // applying binary search on answer
    li low = 1, high = sumOfChunks;
    li mid;
    li ans = -1;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (checkScheduling(chunks, jobs, adj, dj, b, s, mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    if (ans == -1)
        cout << "No valid schedule exists for this input data" << endl;
    else
    {
        // printing all the necessary data
        cout << "The minimum number of machines required is = " << ans << endl;
        cout << "Please refer to schedule.txt for the mapping of jobs and chunks to machines and their scheduling in different time slots" << endl;
        sort(chunksPlacement.begin(), chunksPlacement.end(), sortByCond);

        ofstream outputFile("schedule.txt");
        outputFile << "------------------------------ SCHEDULE FOR " << ans << " MACHINES ------------------------------" << endl;

        li prev = 0;
        for (auto cp : chunksPlacement)
        {
            if (cp[0] != prev)
                outputFile << "\nTime stamp => " << cp[0] << endl;
            outputFile << "Chunk " << cp[2] << " of job " << cp[3] << " is executed by Machine " << cp[1] << endl;
            prev = cp[0];
        }
        li machine = 1;
        outputFile << "\n--------------------------------------------------------" << endl;
        outputFile << "\n\nCHUNK ASSIGNMENT TO MACHINES (max number of distinct chunks to a machine => b = " << b << ") :-\n\n";
        for (auto i : assignedChunks)
        {
            outputFile << "Assigned chunks to Machine " << machine++ << " = ";
            for (auto j : i)
                outputFile << j << " ";
            outputFile << endl;
        }

        outputFile << "\n--------------------------------------------------------" << endl;
        outputFile << "\n\nFINISHING TIME OF JOBS :- \n\n";
        sort(finishTimes.begin(), finishTimes.end());
        for (auto i : finishTimes)
            outputFile << "For Job = " << i.first + 1 << ", it's execution is finished at time " << i.second << ", which does not exceed it's deadline = " << dj[i.first] << endl;

        outputFile.close();
    }
    return 0;
}