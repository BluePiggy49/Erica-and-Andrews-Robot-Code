#include <valuecontrol.h>

double ValueControl::constrain(double val,double lower,double upper){
	if(val<lower){
		return lower;
	}else if(val>upper){
		return upper;
	}else{
		return val;
	}
}
float ValueControl::exponent_mirrored(float val, int expo){
	return pow( fabs(val) , expo) * (val > 0 ? 1.0 : -1.0);
}
