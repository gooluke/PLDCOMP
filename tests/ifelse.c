#include <stdio.h>
#include <inttypes.h>

int square (int a) {
    return a*a;
}

int main(int arg){
	int x = sizeof(int);
	int z = sizeof(int);
	int y = 5;
	z |= y;
	int a = 0; 
	if(square(5)){
		putchar('a');
		return 1;
	}else if(3 > 4){
		putchar('b');
	}else if(3 > 2){
		if(a > 6)
			for(x = 0; x < 3; x++)
			putchar('s');
	}else{
		putchar('c');
	}
    return z;
}
