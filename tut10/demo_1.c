/*
 * Tutorial 10 MPI Demo for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Author: Jonathan Gillett
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

#define DATA_SIZE 10000
#define CHUNK_SIZE 100

void master(int n_proc)
{
    double data[DATA_SIZE] = { 0 };
    double chunks[CHUNK_SIZE] = { 0 };
    double results[DATA_SIZE] = { 0 };
}

//////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char* argv[])
{
    int proc_id;            // Process rank
    int n_proc;             // Number of processes

    // Initialize MPI
    // Must be done in main thread, can only be initialized once
    // Initializes the MPI execution environment
    MPI_Init(&argc, &argv);
    
    // Get the current process id
    // Gives the rank of the calling process in the communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
    // Get the current number of processes
    // Gives the size of the group associated with a communicator
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Display a "Hello world" message from each child/parent
    if (proc_id == MASTER)
    {
        printf( "Hello world from MATER, process %d of %d\n", proc_id, n_proc);
    }
    else
    {
        printf( "Hello world from SLAVE, process %d of %d\n", proc_id, n_proc);
    }

    // Required to terminate all MPI processes
    // Terminates the MPI execution environment
    MPI_Finalize();
}