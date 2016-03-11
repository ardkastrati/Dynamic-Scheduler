/**
 * This class provides basic functionalities used in the 'Arrayhandler' and 'GridDatamining' classes.
 */


#ifndef _GRIDLIBARY_H
#define _GRIDLIBARY_H
#include <string>


class GridLibrary {
	public:
		/**
		 * Transfers multi-dimensional indices into one dimensional indices.
		 * @param dimensions the dimensions of the room
		 * 				must be at least nr_of_dimensions long (if it is longer the overhead will be ignored)
		 * 				must not be Null
		 * 				every item must be greater than zero
		 * @param index the multi-dimensional indices
		 * 				must be at least nr_of_dimensions long (if it's longer the overhead will be ignored)
		 *				must not be Null
		 *				the nth item in index must be in range [zero, nth item in dimensions] for all n in range [zero, nr_of_dimensions - 1].
		 * @param nr_of_dimensions the number of items considered
		 * @return the one dimensional index
		 */
		static int get_index(int* dimensions, int* index, int nr_of_dimensions);
		/**
		 * Calculates the length of a vector.
		 * @param vector the vector which length should be calculated
		 * 				must be at least nr_of_dimensions long
		 * @param nr_of_dimensions the number of items considered
		 */
		static double get_length_of_vector(double* vector, int nr_of_dimensions);
		/**
		 * Subtracts second_array[i] from first_array[i] for i in range [0, length] and returns the resulting array.
		 * @param first_array the array subtracted from
		 * 				must be at least length long
		 * 				must not be Null
		 * @param second_array the array to be subtracted
		 * 				must be at least length long
		 * 				must not be Null
		 * @param length the number of items that are subtracted
		 * @return the result Array
		 * 				 is length long
		 */
		static double* subtract_array(double* first_array, double* second_array, int length);
		/**
		 * Divides first_array[i] by second_array[i] for i in range [0, length] and returns the resulting array.
		 * @param first_array the array to be divided
		 * 				must be at least length long
		 * 				must not be Null
		 * @param second_array the array to set divided by
		 * 				must be at least length long
		 * 				must not be Null
		 * @param length the number of items that should be divided
		 * @return the result Array
		 * 				 is length long
		 */
		static double* divide_array(double* array, double* factor, int length);
		/**
		 * Adds first_array[i] to second_array[i] for i in range [0, length] and returns the resulting array.
		 * @param first_array the first array to be added up
		 * 				must be at least length long
		 * 				must not be Null
		 * @param second_array the second array to be added up
		 * 				must be at least length long
		 * 				must not be Null
		 * @param length the the number of items added up
		 * @return the result Array
		 * 				 is length long
		 */
		static double* add_array(double* first_array, double* second_array, int length);
		/**
		 * Multiplies first_array[i] by second_array[i] for i in range [0, length] and returns the resulting array.
		 * @param first_array the one array
		 * 				must be at least length long
		 * 				must not be Null
		 * @param second_array the other array
		 * 				must be at least length long
		 * 				must not be Null
		 * @param length the the number of items multiplied
		 * @return the result Array
		 * 				 is length long
		 */
		static double* multiply_array(long* first_array, double* second_array, int length);
		/**
		 * Calculates an array with factors from a given array with longueurs.
		 * @param length the array with the longueurs
		 *				must be length_length long
		 *				every item must not be negative
		 * @param length_length the length of the array 'length'
		 * @return the array of factors
		 *				 is length_length long
		 *				 the sum of all factors is 1
		 */
		static double* kastrati_value(double* length, int length_length);

		//#if PRINTGRID || ARRAY_HANDLER_DEBUG || GRID_DATA_MINING_DEBUG || GRID_LIBRARY_DEBUG || MPI_PROXY_DEBUG

		static void print_name(std::string name);

		static void print_array_int(std::string name, int* array, int length);

		static void print_array_long(std::string name, long* array, int length);

		static void print_array_double(std::string name, double* array, int length);

		static void print_int(std::string name, int to_print);

		static void print_long(std::string name, long to_print);

		static void print_double(std::string name, double to_print);

		//#endif
};

#endif //_GRIDLIBARY_H
