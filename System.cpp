<<<<<<< HEAD
#include "System.h"

void System::check_situation() {
	month++;
	order_components();
	if (ordine_evaso())
		print();
}

void System::print() {
	//std::cout << "\nmonth: " << month << "\n";
}

void System::order_components() {

}
=======
#include "System.h"

void System::check_situation() {
	month++;
	order_components();
	if (ordine_evaso())
		print();
}

void System::print() {
	//std::cout << "\nmonth: " << month << "\n";
}

void System::order_components() {

}
>>>>>>> ee44ec15c15a13e8f6600e234b0ab4d4fc3a8776
