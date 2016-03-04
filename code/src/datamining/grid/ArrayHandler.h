/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _ARRAYHANDLER_H
#define _ARRAYHANDLER_H

#include "MpiProxy.h"

class  ArrayHandler
{
	public:
		/**
		 * The constructor of the ArrayHandler
		 * @param nr_of_dimensions the number of dimensions in the virtual multidimensional array
		 *				musst be bigger than zero
		 * @param memory is the MpiProxy that provide acces to the Grid data
		 *				musst not be NULL
		 */
		ArrayHandler(int nr_of_dimensions, MpiProxy* memory);
		/**
		 * The deconstructor of the ArrayHandler it deletes the memory
		 */
		~ArrayHandler();
		/**
		 * Getter for the time array
		 * @param index the index in the virtual multidimensional array
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 * @return returns the time of the Grid point
		 */
		long get_time(int* index);
		/**
		 * Return the surnding Grid points these are 2 to the power nr_of_dimensions many
		 * @parm parameter the parameter of the task
		 *				musst be nr_of_dimensions long
		 *				musst not be NULL
		 * @return returns an array of the indices of the Grid points that surroundet the task it has the following form:
		 * 				x;y;z;...x+1;y;z;...x;y+1;z;...x+1;y+1;z;...x;y;z+1;...
		 * 				therfor it is nr_of_dimensions times 2 to the power of nr_of_dimensions long
		 */
		int* get_enviroment_index(double* parameter);
		/**
		 * Getter for dimensions
		 * @return returns an copy of the dimensions vektor
		 *					is nr_of_dimensions long
		 */
		int* get_dimensions();
		/**
		 * calutates the distanz form the given point parameter to the grid point index under consideration of the correction_vektor and standardized by the incremnet vektor
		 * @param index the index in the virtual multidimensional array
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 *	@param parameter the parameter of the task
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 * @return returns the distanz between the points
		 */
		double get_corrected_distanz(int* index, double* parameter);
		/**
		 * calls the set_new_array function in the MpiProxy
		 * @param new_dimensions the new size of the time and the correction vektor arry
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL and
		 *				 every value musst be positiv
		 * @param new_offset the new offset of the Grid to the parameter point 0
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 * @param new_increment the new increment vektor for the Grid
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 every value musst be positiv
		 */
		void set_new_array(int* dimensions, double* increment, double* offset);
		/**
		 * Adapt a singel Gridpoint to a given task if the point is the best for that Gridpoint
		 * @param index the index in the virtual multidimensional array
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 * @param parameter the parameter of the task
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 * @param time the new time of the task
		 *				 musst not be negativ
		 */
		void insert_at_point(int* index, double* parameter, long time);
		/**
		 * Calls the same named funktion in the MpiProxy
		 */
		void push_new_array();

	private:
		/**
		 * Setter for the time array
		 * @param index the index in the virtual multidimensional array
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 * @param time the new time of the task
		 *				 musst not be negativ
		 */
		void set_time(int* index, long time);
		/**
		 * Calutates the representated parameter of an Gridpoint
		 * @param index the index in the virtual multidimensional array
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 * @return an array of the parameters
		 *					is nr_of_dimensions long
		 */
		double* get_parameter(int* index);
		/**
		 * Calutates the index of the parameter because this is not always an integer we round
		 * @param parameter the parameter of the task
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 * @return return an array of the indices
		 *					is nr_of_dimensions long
		 */
		int* get_rounded_down(double* parameter);
		/**
		 * Setter for the correction_vektor
		 * @param index the index in the virtual multidimensional array
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 * @param vektor the correction vektor
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 */
		void set_correction_vektor(int* index, double* vektor);
		/**
		 * Getter for the correction_vektor
		 * @param index the index in the virtual multidimensional array
		 *				 musst be nr_of_dimensions long
		 *				 musst not be NULL
		 *				 the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 * @return the correction vektor at the index
		 *					is nr_of_dimensions long
		 */
		double* get_correction_vektor(int* index);
		/**
		 * Getter for offset
		 * @return the offset vektor
		 *					is nr_of_dimensions long
		 */
		double* get_offset();
		/**
		 * Getter for increment
		 * @return the increment vektor
		 *					is nr_of_dimensions long
		 */
		double* get_increment();
		/**
		 * the nr of dimensions of the virtal mulitdimenisonal array
		 */
		int nr_of_dimensions;
		/**
		 * the MpiProxy that provide acces to the Grid data
		 */
		MpiProxy* memory;

};

#endif //_ARRAYHANDLER_H
