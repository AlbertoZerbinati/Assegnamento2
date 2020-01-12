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
