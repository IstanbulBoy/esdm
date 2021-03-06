/* This file is part of ESDM.                                              
 *                                                                              
 * This program is is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU Lesser General Public License as published by  
 * the Free Software Foundation, either version 3 of the License, or            
 * (at your option) any later version.                                          
 *                                                                              
 * This program is is distributed in the hope that it will be useful,           
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                                 
 * You should have received a copy of the GNU Lesser General Public License        
 * along with ESDM.  If not, see <http://www.gnu.org/licenses/>.           
 */                                                                         


/**
 * @file
 * @brief This file implements ESDM datatypes, and associated methods.
 */


#include <esdm.h>
#include <esdm-internal.h>


/**
 * ESDM Fragments
 *
 */
esdm_status_t esdm_fragment_create() {
	ESDM_DEBUG(0, "Creating Fragment.");
	return ESDM_SUCCESS;
}

esdm_status_t esdm_fragment_destroy() {
	ESDM_DEBUG(0, "Destroying Fragment.");
	return ESDM_SUCCESS;
}



/**
 * ESDM Datasets
 *
 */
esdm_status_t esdm_dataset_create() {
	return ESDM_SUCCESS;
}

esdm_status_t esdm_dataset_destroy() {
	return ESDM_SUCCESS;
}
