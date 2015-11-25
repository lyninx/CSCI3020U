#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>


#define MASTER 0

#define RANGE_START 1
#define RANGE_END 1000

void master(int n_proc){
	int n_sent = 0, n_recv = 0; 
	int size = 0;
	int r = 0;
	int split_range_end = floor(RANGE_END / (n_proc - 1));
	size = split_range_end - RANGE_START;
	
	int range[2] = { 0 };
	MPI_Status status;  

    for (int i = 1; i < n_proc; ++i)
    {
        // Send CHUNK_SIZE of data to each process initially
        // Sends data, of type double to process 'i'
        r = (i - 1)*size + (i);
    	range[0] = r ;
    	range[1] = r + size;
    	printf("sent range: %d - %d\n", range[0], range[1]);

        MPI_Send(&range, 2, MPI_INT, i, n_sent, MPI_COMM_WORLD);
        n_sent++;
    }

    int result[size];
    for (int i = 0; i < n_proc - 1; ++i)
    {
        // Receive the computed chunk back from the slave
        MPI_Recv(result, size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        // Get the process that sent the data and send it the next chunk
        //proc = status.MPI_SOURCE;
        n_recv = status.MPI_TAG;
        
        // Copy the results from the slave into the results array
        for (int i = 0; i < size; ++i)
        {
        	if(result[i] != 0){
        		printf("%d, ", result[i]);	
        	}
            
        }
        printf("\n\n");
    }
}
void slave(int proc_id)
{
	int range[2] = { 0, 0 };  // The chunk to receive for calculations
    int n_recv = 0;     
    int num_primes = 0;
    bool prime = true;           
    MPI_Status status;                 // MPI status struct

    // Receive the chunk to calculate from MASTER
    MPI_Recv(range, 2, MPI_INT, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    n_recv = status.MPI_TAG;

        // Perform our "calculation" to return back to MASTER
            //result[i] = chunk[i] * chunk[i];
    int size = range[1] - range[0];
    int res[size];
    for(int i = 0; i < size; i++){
    	res[i] = 0;
    }
    for(int i = range[0]; i < range[1]; i++){
    	prime = true;
    	for(int j = 2; j <= i/2; j++){
    		if(i % j == 0){
    			prime = false;
    		}
    	}
    	if(prime && i > 1){
    		//printf("prime: %d\n", i);
    		num_primes = num_primes + 1;
    		res[num_primes] = i;
    	}
    	
    }

        printf("calculated range: %d - %d\n", range[0], range[1]);

        // Send the results back to MASTER, include in TAG the chunk that was calculated
        MPI_Send(res, size, MPI_INT, MASTER, n_recv, MPI_COMM_WORLD);
        
        // Wait for the next chunk of data to be received

    
}
int main(int argc, char* argv[]){
    int proc_id;            // Process rank
    int n_proc;             // Number of processes

    // Initialize MPI
    MPI_Init(&argc, &argv);
    
    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    

    if (proc_id == MASTER)
    {
        master(n_proc);
    }
    else
    {
        slave(proc_id);
    }

    // Required to terminate all MPI processes
    MPI_Finalize();
}