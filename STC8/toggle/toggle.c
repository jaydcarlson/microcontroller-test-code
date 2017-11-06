#include "N76E003.h"
#include "Function_Define.h"

void main()
{
	P00_PushPull_Mode;
	while(1)
	{
		P00 = !P00;
	}
}