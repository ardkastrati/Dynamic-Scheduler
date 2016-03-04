/**
 * Project Dynamic Scheduler for Scientific Simulations
 */


#ifndef _MPIPROXY_H
#define _MPIPROXY_H


class MpiProxy {
	public:
		/**
		 * The constructor of the MPI Proxy it initialize the MPI shared memory
		 * and the attributes with default values
		 * @param nr_of_dimensions the number of dimensions in the virtual multidimensional array
		 *				musst be bigger than zero
		 * @param rank the own rank in the MPI world
		 *				musst not be negativ
		 * @param target_rank the rank of the instanz that hold the MPI shared memory
		 *				musst not be negativ
		 */
		MpiProxy(int nr_of_dimensions, int rank, int target_rank);
		/**
		 * The destructor of the MPI Proxy it deletes the MPI shared memory window
		 */
		~MpiProxy();
		/**
		 * Getter for dimensions
		 * @return a copy of the actual dimensions
		 */
		int* get_dimensions();
		/**
		 * Getter for offset
		 * @return a copy of the offset vektor of the grid to the parameter point 0
		 */
		double* get_offset();
		/**
		 * Getter for increment
		 * @return a copy of the increment vektor
		 */
		double* get_increment();
		/**
		 * Getter for the time array
		 * @param index of the Grid point whose time is requestet
		 *				musst not be negativ
		 * @return the time of the Grid point with the index index
		 */
		long get_time(int index);
		/**
		 * Getter for the correction vektor of a singel Grid point
		 * @param index of the correction vektor array
		 *				musst not be negativ
		 * @return the value of the correction vektor at the point with index index
		 */
		double get_correction_vektor(int index);
		/**
		 * Creates a new MPI window with the new size
		 * BUT dose not change something at the old MPI window
		 * @param new_dimensions the new size of the time and the correction vektor arry
		 *				musst be nr_of_dimensions long
		 *				musst not be NULL
		 * @param new_offset the new offset of the Grid to the parameter point 0
		 *				musst be nr_of_dimensions long
		 *				musst not be NULL
		 * @param new_increment the new increment vektor for the Grid
		 *				musst be nr_of_dimensions long
		 *				musst not be NULL
		 */
		void set_new_array(int* new_dimensions, double* new_offset, double* new_increment);
		/**
		 * deletes the old MPI shared Memory and set the new one instead
		 * just callable if taget rank is equal rank and if set_new_array is called before
		 */
		void push_new_array();
		/**
		 * Setter for the correction_vektor
		 * @param index the index of the correction vektor array
		 *				musst not be negativ
		 * @param new_vektor_value the new vektor value
		 */
		void set_correction_vektor(int index, double new_vektor_value);
		/**
		 * Setter for the time array
		 * @param index the index of the Grid point whoes time should be changed
		 *				musst not be negativ
		 * @param new_time the new time of the Grid point
		 *				musst not be negativ
		 */
		void set_time(int index, long new_time);
	private:
		/**
		 * an array that is nr_of_dimensions long and has saved the dimensions of the virtal multidimensional time and correction vektor array
		 */
		int* dimensions;
		/**
		 * the offset vektor is a vektor from the point 0 to the Gridpoint 0
		 * it is nr_of_dimensions long
		 * the units depends on the scientific code
		 */
		double* offset;
		/**
		 * the increment vektor contains the step size for each dimensions
		 * it is nr_of_dimensions long
		 * the units depends on the scientific code
		 */
		double* increment;
		/**
		 * the vektor from the paticular Grid point to the nearest measurement
		 * the correction_vektor array is nr_of_dimensions times the lenght of the time array long
		 * its units depends on the scientific code
		 */
		double* correction_vektor;
		/**
		 * the array with the acutall Grid points in it
		 * it is a one dimensional representation of a multidimensional array
		 * it is the product of the singel items in dimensions long
		 * its units is milli-seconds
		 */
		long* time;
		/**
		 * the nr of dimensions of the virtal mulitdimenisonal array
		 */
		int nr_of_dimensions;
		/**
		 * the MPI rank of the instanz
		 */
		int rank;
		/**
		 * the MPI rank of the instanz that holds the shared memory
		 */
		int target_rank;
};

#endif //_MPIPROXY_H
