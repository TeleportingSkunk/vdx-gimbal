#include <MeanFilter.h>

#define T unsigned
#define N 64

const byte pinIn = A0;

bufferMean<T,N> meanB;
accuMean<T,N> meanA;

T x;

void setup(){
	Serial.begin(9600);
	
	x = analogRead(pinIn);
	
	meanB.init(x);
	meanA.init(x);
}

void loop(){
	x = analogRead(pinIn);
	
	Serial.println();    Serial.print(x);
	Serial.print('\t');  Serial.print(meanB.update(x));
	Serial.print('\t');  Serial.print(meanA.update(x));
	
	delay(20);
}
