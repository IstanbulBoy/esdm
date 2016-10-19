#include <stdio.h>
#include <memvol.h>
#include <time.h>

void benchmark(FILE *f, int mode) {
    puts("Benchmark started...");
    /* setup */
    struct timespec begin;
    struct timespec end;
    long delta_create;
    long delta_dataset_create;
    long delta_write;
    long delta_read;
    long delta_close;
    hid_t fid, fprop, space, did;
    herr_t status;

    fprop = H5Pcreate(H5P_FILE_ACCESS);

    if (mode == 1) {
        hid_t vol_id = H5VL_memvol_init();
        H5Pset_vol(fprop, vol_id, &fprop);
    }

    int data_read[3][4];
 	const int nloops = 10000;
    
    
    //for (int i = 0; i < nloops; i++) {
        char name[12];
        /* temp */
        int i = 0;
        sprintf(name, "test%d.h5", i);

	hsize_t dims[2] = {3, 4};	
	int data[3][4];
	int counter = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			data[i][j] = 1000 + ++counter;
		}
	}

	space = H5Screate_simple(2, dims, NULL);

        clock_gettime(CLOCK_MONOTONIC, &begin);
    fid = H5Fcreate(name, H5F_ACC_TRUNC, H5P_DEFAULT, fprop);
        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_create += (end.tv_nsec - begin.tv_nsec);

        clock_gettime(CLOCK_MONOTONIC, &begin);
	did = H5Dcreate2(fid, "/test", H5T_NATIVE_INT, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);	
        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_dataset_create += (end.tv_nsec - begin.tv_nsec);

        clock_gettime(CLOCK_MONOTONIC, &begin);
	status = H5Dwrite(did, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_write += (end.tv_nsec - begin.tv_nsec);


        clock_gettime(CLOCK_MONOTONIC, &begin);
	status = H5Dread(did, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data_read);
        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_read += (end.tv_nsec - begin.tv_nsec);

     

        clock_gettime(CLOCK_MONOTONIC, &begin);
	status = H5Dclose(did);
        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_close += (end.tv_nsec - begin.tv_nsec);

         status = H5Sclose(space);
         status = H5Fclose(fid);

    //}

    /* calculate means */

        printf("\n BUFFER: ");
	
       for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d,", data_read[i][j]);
		}
	}
    
    const char* hardware;
    if (mode == 1) {
        hardware = "memvol";
    } else {
        hardware = "standard";
    }

    /* Dataframe Outline:
     * "HDFversion" "Hardware" "H5Fcreate" "H5Dcreate" "H5Dwrite" "H5Dread" "H5Dclose"
     */
    fprintf(f, "\"%s\" %lu %lu %lu %lu %lu", hardware, delta_create, delta_dataset_create, delta_write, delta_read, delta_close);

    /*
    double avg_create = (double)delta_create;// / nloops;
    fprintf(f, "\nAverage Execution Time for H5Fcreate: %.10f\n", avg_create);

    double avg_dataset_create = (double)delta_dataset_create;// / nloops;
    fprintf(f, "Average Execution Time for H5Dcreate: %.10f\n", avg_dataset_create); 

    double avg_write = (double)delta_write;// / nloops;
    fprintf(f, "Average Execution Time for H5Dwrite: %.10f\n", avg_write);

    double avg_read = (double)delta_read;// / nloops;
    fprintf(f, "Average Execution Time for H5read: %.10f\n", avg_read);

    double avg_close = (double)delta_close;// / nloops;
    fprintf(f, "Average Execution Time for H5Fclose: %.10f\n", avg_close);
    */
}


int main(int argc, char** argv) {

    FILE *f = fopen("benchmark.log", "w");
    if (f == NULL) {
        puts("Error opening file!");
        return 1;
    }
  
    /* HDF standard */
    benchmark(f, 0);

    fprintf(f, "\n");

    /* HDF memvol */
    benchmark(f, 1);

    fclose(f);

	H5VL_memvol_finalize();
}
