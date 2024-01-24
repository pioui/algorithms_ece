// C++ program to find first n smallest numbers 
#include <iostream> 
#include <algorithm> 
using namespace std; 
int main() 
{ 
	int v[] = { 30, 20, 10, 40, 60, 1, 70, 80 }, i; 

	// Using std::nth_element with n as 3 
	std::nth_element(v, v + 2, v + 8); 

	// Since, n is 3 so now first three numbers will be the 
	// three smallest numbers in the whole array 
	// Displaying first three smallest number 
	for (i = 0; i < 3; ++i) 
	{ 
		cout << v[i] << " "; 
	} 
	return 0; 
} 
