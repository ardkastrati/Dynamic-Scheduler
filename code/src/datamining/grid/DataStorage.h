/**
 * This class stores all data used in the grid data  mining procedures.
 */

#ifndef _DATASTORAGE_H
#define _DATASTORAGE_H


class DataStorage {
	public:
		/**
		 * The constructor of the DataStorage
		 * and the attributes with default values
		 * @param nr_of_dimensions the number of dimensions in the virtual multi-dimensional array
		 *				must be greater than zero
		 */
		DataStorage(int nr_of_dimensions);
		/**
		 * The destructor of the DataStorage
		 */
		~DataStorage();
		/**
		 * Getter for the dimensions array.
		 * @return a copy of the actual dimensions
		 */
		int* get_dimensions();
		/**
		 * Getter for the offset vector.
		 * @return a copy of the offset vector of the grid origin to the mathematical origin
		 */
		double* get_offset();
		/**
		 * Getter for the increment vector.
		 * @return a copy of the increment vector
		 */
		double* get_increment();
		/**
		 * Getter for the runtime array.
		 * @param index of the grid point whose time is requested
		 *				must not be negative
		 * @return the time of the grid point with the index index
		 */
		long get_time(int index);
		/**
		 * Getter for the correction vector of a single grid point.
		 * @param index of the correction vector array
		 *				must not be negative
		 * @return the value of the correction vector at the point with index index
		 */
		double get_correction_vector(int index);
		/**
		 * Set new values for dimensions, offset and increment
		 * @param new_dimensions the new size of the time and the correction vector array
		 *				must be nr_of_dimensions long
		 *				must not be NULL
		 * @param new_offset the new offset of the grid origin to the mathematical origin.
		 *				must be nr_of_dimensions long
		 *				must not be NULL
		 * @param new_increment the new increment vector for the grid
		 *				must be nr_of_dimensions long
		 *				must not be NULL
		 */
		void set_new_array(int* new_dimensions, double* new_offset, double* new_increment);
		/**
		 * Setter for the correction_vector.
		 * @param index the index of the correction vector array
		 *				must not be negative
		 * @param new_vector_value the new vector value
		 */
		void set_correction_vector(int index, double new_vector_value);
		/**
		 * Setter for the time array.
		 * @param index the index of the grid point whose time should be changed
		 *				must not be negative
		 * @param new_time the new time of the grid point
		 *				must not be negative
		 */
		void set_time(int index, long new_time);
	private:
		/**
		 * An array that is nr_of_dimensions long and stores the dimensions of the virtual multi-dimensional time and correction vector array.
		 */
		int* dimensions;
		/**
		 * The offset vector is a vector from the mathematical origin to the grid origin.
		 * It is nr_of_dimensions long.
		 * The units depends on the scientific code.
		 */
		double* offset;
		/**
		 * The increment vector contains the step size for each dimension.
		 * It is nr_of_dimensions long.
		 * The units depend on the scientific code.
		 */
		double* increment;
		/**
		 * The vector from the particular grid point to the nearest measurement.
		 * The correction_vector array is nr_of_dimensions multiplied by the length of the time array long.
		 * Its units depend on the scientific code.
		 */
		double* correction_vector;
		/**
		 * The array containing the actual grid points.
		 * This is a one dimensional representation of a multidimensional array.
		 * It is the product of the items contained in 'dimensions' long.
		 * The unit used is milli-seconds.
		 */
		long* time;
		/**
		 * The nr of dimensions of the virtual multi-dimensional array.
		 */
		int nr_of_dimensions;
};

#endif //_DATASTORAGE_H
