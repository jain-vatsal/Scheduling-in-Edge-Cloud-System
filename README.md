# Edge-Cloud Job Scheduling

This project aims to efficiently schedule data-intensive jobs in an Edge-Cloud system. The scheduling algorithm minimizes the total number of active nodes required to process all jobs while meeting their deadlines. 

## Problem Statement
The problem involves scheduling a set of J jobs arriving at time 0 in a cloud system consisting of N homogeneous physical machines (nodes). Each job has a deadline and requires access to a set of equal-sized data chunks stored in a distributed file system. Jobs can run in parallel on the same or different machines, and replication of data chunks is allowed.

## Algorithm Overview
The scheduling algorithm follows a systematic approach to efficiently allocate resources and schedule data-intensive jobs in an Edge-Cloud system. Here's a detailed explanation of the steps involved:

1. **Input Data Handling**:
   - The algorithm begins by taking input data such as the total number of chunks, jobs, chunk assignments to jobs, deadlines for each job, and machine constraints like the maximum number of chunks a machine can handle and the number of simultaneous jobs a machine can process.

2. **Binary Search for Minimum Machines**:
   - To optimize resource utilization, the algorithm employs binary search to find the minimum number of machines required for scheduling. This approach helps in narrowing down the search space efficiently.

3. **Job Scheduling**:
   - The core of the algorithm lies in scheduling jobs efficiently while meeting their deadlines. It iterates through each job, prioritizing those with earlier deadlines.
   - For each job, the algorithm attempts to assign its chunks to available machines within the specified deadline. It optimizes chunk allocation to minimize the number of active nodes required.

4. **Chunk Assignment and Machine Utilization**:
   - Various data structures are utilized to represent chunk assignments to machines, machine states, and scheduling details. These structures help in tracking the utilization of each machine and ensuring efficient resource allocation.
   - The algorithm ensures that each machine operates within its capacity by considering factors like the maximum number of chunks it can handle and the number of simultaneous jobs it can process.

5. **Output Generation**:
   - Once the scheduling process is complete, the algorithm outputs the minimum number of machines required for scheduling. It also generates a `schedule.txt` file containing detailed information about the scheduling, including chunk assignments to machines and job execution times.

6. **Optimization and Scalability**:
   - While the algorithm provides an efficient solution for small to moderate-sized inputs, it can be further optimized for larger datasets. Optimization techniques such as parallel processing and heuristic-based scheduling can enhance scalability and performance.

7. **Error Handling and Validation**:
   - The algorithm incorporates error handling mechanisms to detect and handle scenarios where valid scheduling is not possible due to resource constraints or conflicting deadlines. Proper validation ensures the reliability and accuracy of the scheduling process.

By following these steps, the scheduling algorithm effectively addresses the challenges of scheduling data-intensive jobs in an Edge-Cloud environment, providing a balance between resource utilization and job completion within deadlines.

## How to Use
1. If you want to test a random test case, first compile the C++ code (`testcasegenerator.cpp`).
2. Compile and run the provided C++ code (`scheduler.cpp`).
3. Enter input data such as the number of chunks, jobs, chunk assignments, deadlines, and machine constraints.
4. The algorithm will output the minimum number of machines required and generate a `schedule.txt` file containing scheduling details.

## Files
- `hpcProblemStatement.pdf `: Problem statement. 
- `scheduler.cpp`: C++ implementation of the scheduling algorithm.
- `testcasegenerator.cpp`: C++ implementation for generating random test cases.
- `schedule.txt`: Output file containing scheduling details(initial file contains schedule for Input 1 given below, the inputs can be modified as per need).
- `README.md`: Project documentation.
- `report.pdf`: Detailed report on the algorithm, code, and complexity analysis.

## Collaborators
- [Vatsal Jain](https://github.com/jain-vatsal)
- [Jethwani Siddhant Pratap](https://github.com/sidling1)

## Example Input
#### you can directly paste these sample inputs on your terminal and run, or create your own test case

##### Input 1 :- 
2 2 5 3 1 2 1 4 2 3 2 3 4 3 2 3 5 

##### Input 2 :- 
4 5 10 4 5 2 1 2 5 2 4 6 3 4 10 3 2 5 2 1 3

## Example output
- Minimum number of machines = 3
- Minimum number of machines = 2
