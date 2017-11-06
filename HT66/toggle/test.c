#include "HT66F0185.h"

void main()
{
	_pac1 = 0;
	while(1) {
		_pa ^= 2;
	}	
}