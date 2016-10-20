#include <stdio.h>
#include <memvol.h>
#include <time.h>

void benchmark(FILE *f, int mode) {
    puts("Benchmark started...");
    /* setup */
    struct timespec begin;
    struct timespec end;
    unsigned long delta_create;
    unsigned long delta_dataset_create;
    unsigned long delta_write;
    unsigned long delta_read;
    unsigned long delta_close;
    hid_t fid, fprop, space, did;
    herr_t status;

    fprop = H5Pcreate(H5P_FILE_ACCESS);

    if (mode == 1) {
        hid_t vol_id = H5VL_memvol_init();
        H5Pset_vol(fprop, vol_id, &fprop);
    }

 	const int nloops = 10;
    
    
    for (int c = 0; c < nloops; c++) {
        char name[12];
        sprintf(name, "test%d.h5", c);

        int data_size = 10*c;
        hsize_t dims[2] = {data_size, data_size};	
        int data[data_size][data_size];
        int data_read[data_size][data_size];
        int counter = 0;
        for (int i = 0; i < data_size; i++) {
            for (int j = 0; j < data_size; j++) {
                data[i][j] = 1000 + ++counter;
            }
        }

        space = H5Screate_simple(2, dims, NULL);

        /* H5Fcreate */
        clock_gettime(CLOCK_MONOTONIC, &begin);

        fid = H5Fcreate(name, H5F_ACC_TRUNC, H5P_DEFAULT, fprop);

        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_create += (end.tv_nsec - begin.tv_nsec);

        /* H5Dcreate */
        clock_gettime(CLOCK_MONOTONIC, &begin);

	    did = H5Dcreate2(fid, "/test", H5T_NATIVE_INT, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);	

        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_dataset_create += (end.tv_nsec - begin.tv_nsec);

        /* H5Dwrite */
        clock_gettime(CLOCK_MONOTONIC, &begin);

	    status = H5Dwrite(did, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_write += (end.tv_nsec - begin.tv_nsec);

        /* H5Dread */
        clock_gettime(CLOCK_MONOTONIC, &begin);

	    status = H5Dread(did, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data_read);

        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_read += (end.tv_nsec - begin.tv_nsec);

        /* H5Dclose */
        clock_gettime(CLOCK_MONOTONIC, &begin);

	    status = H5Dclose(did);
        
        clock_gettime(CLOCK_MONOTONIC, &end);
        delta_close += (end.tv_nsec - begin.tv_nsec);

        status = H5Sclose(space);
        status = H5Fclose(fid);

        const char* hardware;
        if (mode == 1) {
            hardware = "memvol";
        } else {
            hardware = "standard";
        }

        /* Dataframe Outline:
         * "HDFversion" "Hardware" "H5Fcreate" "H5Dcreate" "H5Dwrite" "H5Dread" "H5Dclose"
         */
        fprintf(f, "\"%s\" %lu %lu %lu %lu %lu\n", hardware, delta_create, delta_dataset_create, delta_write, delta_read, delta_close);
    }
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
