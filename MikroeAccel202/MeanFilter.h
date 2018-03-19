#ifndef MeanFilter_h
#define MeanFilter_h

#include <Arduino.h>

template <typename Q,int N>             // N - Number of previous values to take into account.
class MeanFilter {			            // Averages input value based on previous values
	public:
        MeanFilter() {
            #warning Q Must sum the results of (x*N)

            #warning Works faster when N = 2^k

        }
        
		virtual void init(Q x=0) = 0;		// Initialisation
		virtual Q update(Q x) = 0;			// Processing stage: inputs the raw new data, returns the averaged result.
};


template <typename Q,int N>
class bufferMean : public MeanFilter<Q,N> {    // Averages the previous N input values, kept in a buffer which is updated
	private:
		Q bufferArr[N];
		byte i;
		Q sum;
		
	public:
		void init(Q x=0) {
			sum = x*N;
			i = N;
			do {
				bufferArr[--i] = x;
			} while (i > 0);
		}
		Q update(Q x) {
			sum -= bufferArr[i];
			sum += bufferArr[i] = x;
			
			if (i == 0)  i = N;
			--i;
			
			return sum/N;
		}
};


template <typename Q,int N>
class accuMean : public MeanFilter<Q,N> { //generates a mean by only interpreting differences in a running sum. New inputs are 
                                                    //compared against the current average before their weighted contribution is added
                                                        //to the running sum, i.e. the average
	private:
		Q accSum;	// Running sum
		
	public:
		void init(Q x=0) {
			accSum = x*N; //initialise the running/accumulated sum 
		}
		Q update(Q x) {
			return (accSum += x - accSum/N) / N; // the (+=) term updates the running sum to only include
                                                    //the difference between new data and the "member" it replaces
		}
};

#endif
