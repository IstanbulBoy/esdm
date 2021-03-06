#ifndef H5_ESDM_H
#define H5_ESDM_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <glib.h>


#define DEBUG 1


#ifdef DEBUG
	#define info(...) fprintf(stderr, "[H5 ESDM] "__VA_ARGS__);
#else
 	#define info(...)
#endif


#define warn(...) fprintf(stderr, "[H5 ESDM] Warning: "__VA_ARGS__);
#define fail(...) { fprintf(stderr, "[H5 ESDM] Error: "__VA_ARGS__); exit(1); }


/* HDF5 related integer defintions e.g. as required for herr_t */

#define SUCCEED    0






typedef enum type {
	MEMVOL_FILE,
	MEMVOL_GROUP,
	MEMVOL_DATASET,
	MEMVOL_ATTRIBUTE,
	MEMVOL_DATASPACE,
	MEMVOL_DATATYPE
} H5VL_esdm_object_type_t;


typedef struct {
	hid_t dscpl_id;
	int dim;
} H5VL_esdm_dataspace_t;



typedef struct H5VL_esdm_link_t {
	hid_t dummy;
	// TODO: consolidate with object?
} H5VL_esdm_link_t;


typedef struct H5VL_esdm_attribute_t {
    hid_t acpl_id;
    hid_t aapl_id;
    hid_t dxpl_id;
} H5VL_esdm_attribute_t;


typedef struct H5VL_esdm_datatype_t {
	hid_t lcpl_id;
	hid_t tcpl_id;
	hid_t tapl_id;
	hid_t dxpl_id;
} H5VL_esdm_datatype_t;


typedef struct H5VL_esdm_dataset_t {
	hid_t dcpl_id;
	hid_t dapl_id;
	hid_t dxpl_id;

	char * name;	
    //H5VL_loc_params_t loc_params;
    hid_t dataspace;
    hid_t datatype;
} H5VL_esdm_dataset_t;


typedef struct H5VL_esdm_groupt_t {
	GHashTable * childs_tbl;
	GArray * childs_ord_by_index_arr; 

	hid_t gcpl_id;
	hid_t gapl_id;
	hid_t dxpl_id;

	char * name;
} H5VL_esdm_group_t;


typedef struct H5VL_esdm_file_t {
	H5VL_esdm_group_t root_grp; // it must start with the root group, since in many cases we cast files to groups

	char * name;
	int mode_flags; // RDWR etc.

	hid_t fcpl_id;
	hid_t fapl_id;
	hid_t dxpl_id;

} H5VL_esdm_file_t;





typedef struct H5VL_esdm_object_t {
	H5VL_esdm_object_type_t type;
	void * object;
	/* union {
		H5VL_esdm_group_t* group;
		H5VL_esdm_dataset_t* dataset;
		H5VL_esdm_datatype_t* datatype;
	} object; */
} H5VL_esdm_object_t;


static void H5VL_esdm_group_init(H5VL_esdm_group_t * group);



#endif
