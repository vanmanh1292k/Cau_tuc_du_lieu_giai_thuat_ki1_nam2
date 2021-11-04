#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
	unsigned int X, n;
	cout << "input hex: ";
	cin >> hex >> X;
	cout << "input number of bit: ";
	cin >> n; // input variable and bit n
	//Инициализируем маску согласно варианту 2:
	//Определяем в старшем разряде 128-битного числа единицу и сдвигаем ее до n-го разряда
	unsigned int mask = 0x80000000 >> (128 - n);
	X |= mask; // OR
	cout << "dec: " << X << endl;
	cout << "hex: " << hex << X;
	return 0;
}


//int main() {
//	unsigned int X;
//	cout << "input hex: ";
//	cin >> hex >> X; //input value, hexadecimal system
//	int len = (int)log2(X) + 1; //assign the length of the binary bit sequence
//	
//	for (int i = 0; i < len; i += 2) {  // run from left to right
//		unsigned int mask = (1UL << i); // set mask
//		X |= mask; // OR, set odd position bits to 1
//	}
//	cout << "dec: " << X << endl;
//	cout << "hex: " << hex << X;
//	return 0;
//}



//int main() {
//	int X;
//	cin >> hex >> X;
//	int len = (int)log2(X) + 1;
//	unsigned int mask = (1UL); // set mask = ...000100000
//	for (int i = 0; i < 5; i ++) {
//		mask |= (1UL << i); // set mask = ....000000001 -> ..000011111
//	}
//	cout << mask << endl;
//	for (int i = 9; i < len; i++) {
//		mask |= (1UL << i); // set mask = ....11111000011111
//	}
//	X &= mask;
////	X &= mask; // END, set remove 5 bits left
//	cout << X;
//	return 0;
//}

//int main(){
//	int X;
//	cin >> hex >> X;
//	X = X << 5; // 2 ^ 5 = 32, Move the bits to the left 5 times
//	cout << X;
//	return 0;
//}


//int main() {
//	int X;
//	cin >> hex >> X;
//	X = X >> 5; // 2 ^ 5 = 32, Move the bits to the right 5 times
//	cout << X;
//	return 0;
//}


//int main() {
//	unsigned int X, n; 
//	cin >> hex >> X;
//	cin >> n; // input variable and bit n
//	//unsigned int mask = (1UL << (n - 1)); // move the bits to the left n-1 times
//	//Инициализируем маску согласно варианту 2:
//	//Определяем в старшем разряде 128-битного числа единицу и сдвигаем ее до n-го разряда
//	unsigned int mask = 0x80000000 >> (127 - n);
//	X |= mask; // OR
//	cout << X;
//	return 0;
//}



