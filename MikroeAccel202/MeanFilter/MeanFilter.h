#ifndef MeanFilter_h
#define MeanFilter_h

#include <Arduino.h>

template <typename T,int N>             // N - Number of previous values to take into account.
class MeanFilter {			            // Averages input value based on previous values
	public:
        MeanFilter() {
            #warning T Must sum the results of (x*N)

            #warning Works faster when N = 2^k

        }
        
		virtual void init(T x=0) = 0;		// Initialisation
		virtual T update(T x) = 0;			// Processing stage: inputs the raw new data, returns the averaged result.
};


template <typename T,int N>
class bufferMean : public MeanFilter<T,N> {    // Averages the previous N input values, kept in a buffer which is updated
	private:
		T bufferArr[N];
		byte i;
		T sum;
		
	public:
		void init(T x=0) {
			sum = x*N;
			i = N;
			do {
				bufferArr[--i] = x;
			} while (i > 0);
		}
		T update(T x) {
			sum -= bufferArr[i];
			sum += bufferArr[i] = x;
			
			if (i == 0)  i = N;
			--i;
			
			return sum/N;
		}
};


template <typename T,int N>
class accuMean : public MeanFilter<T,N> { //generates a mean by only interpreting differences in a running sum. New inputs are 
                                                    //compared against the current average before their weighted contribution is added
                                                        //to the running sum, i.e. the average
	private:
		T accSum;	// Running sum
		
	public:
		void init(T x=0) {
			accSum = x*N; //initialise the running/accumulated sum 
		}
		T update(T x) {
			return (accSum += x - accSum/N) / N; // the (+=) term updates the running sum to only include
                                                    //the difference between new data and the "member" it replaces
		}
};

#endif
