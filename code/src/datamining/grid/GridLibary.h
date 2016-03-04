/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _GRIDLIBARY_H
#define _GRIDLIBARY_H
#include <string>


class GridLibary {
	public:
		/**
		 * transfer multidimensional indices into one dimensional
		 * @param dimensions the dimensions of the room
		 * 				musst be at least nr_of_dimensions long (if its longer the overhead will be ignored)
		 * 				musst not be Null
		 * 				every item musst be bigger than zero
		 * @param index the multidimensional indices
		 * 				musst be at least nr_of_dimensions long (if its longer the overhead will be ignored)
		 *				musst not be Null
		 *				the nth item in index musst be in range from zero to the nth item in dimensions for all n in range from zero to nr_of_dimensions - 1
		 * @param nr_of_dimensions the number of items that should be noticed
		 * @return the onedimensional index
		 */
		static int get_index(int* dimensions, int* index, int nr_of_dimensions);
		/**
		 * calculates the lenght of a vektor
		 * @param vektor the vektor whichs lenght sould be calculatet
		 * 				musst be at least nr_of_dimensions longer
		 * @param nr_of_dimensions the number of items that should be noticed
		 */
		static double get_length_of_vektor(double* vektor, int nr_of_dimensions);
		/**
		 * calculate first Array minus secound array item for item for lenght items
		 * @param first_array the one Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param second_array the other Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param lenght the the number of items that should be substracted
		 * @return the result Array
		 * 				 is lenght long
		 */
		static double* subtract_array(double* first_array, double* second_array, int lenght);
		/**
		 * calculate first Array divided by the secound array item for item for lenght items
		 * @param first_array the one Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param second_array the other Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param lenght the the number of items that should be divided
		 * @return the result Array
		 * 				 is lenght long
		 */
		static double* divide_array(double* array, double* factor, int lenght);
		/**
		 * calculate first Array plus secound array item for item for lenght items
		 * @param first_array the one Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param second_array the other Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param lenght the the number of items that should be added
		 * @return the result Array
		 * 				 is lenght long
		 */
		static double* add_array(double* first_array, double* second_array, int lenght);
		/**
		 * calculate first Array multiplyed by the secound array item for item for lenght items
		 * @param first_array the one Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param second_array the other Array
		 * 				musst be at least lenght long
		 * 				musst not be Null
		 * @param lenght the the number of items that should be multiplyed
		 * @return the result Array
		 * 				 is lenght long
		 */
		static double* multiply_array(long* first_array, double* second_array, int lenght);
		/**
		 * it calculate a array with factors form a given array with longuerurs
		 * @param lenght the array with the longuerurs
		 *				musst be lenght_lenght long
		 *				every item musst not be negativ
		 * @param lenght_lenght the lenght of the array lenght
		 * @return the Array of factors
		 *				 is lenght_lenght long
		 *				 the sum of all factors is 1
		 */
		static double* kastrati_value(double* lenght, int lenght_lenght);

		//#if PRINTGRID || ARRAY_HANDLER_DEBUG || GRID_DATA_MINING_DEBUG || GRID_LIBARY_DEBUG || MPI_PROXY_DEBUG

		static void print_name(std::string name);

		static void print_array_int(std::string name, int* array, int lenght);

		static void print_array_long(std::string name, long* array, int lenght);

		static void print_array_double(std::string name, double* array, int lenght);

		static void print_int(std::string name, int to_print);

		static void print_long(std::string name, long to_print);

		static void print_double(std::string name, double to_print);

		//#endif
};

#endif //_GRIDLIBARY_H
