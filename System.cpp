#include "System.h"
#include <iostream>
#include <fstream>

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
	if (month == 0) {  //lo faccio solo al primo giro
		fill_data(); //riempio model_types che mi serve per leggere i file modelX che contengono le componenti da produrre
		//components_needed[month] = fill_components_month();

	}
}

void System::fill_data() {
	//(1) riempio model_types e models_infos
	std::ifstream ist {"models.txt"};
    if (!ist)
		throw Invalid();

    // store models
    std::vector<std::string> model_files;                  // questo è il mio vettore con i model
    std::string file;
    while (ist >> file)
        model_files.push_back(std::string{file});
    ist.close();    // chiudo ist

    // store model_id, model_name
    for (int i=0; i < model_files.size(); ++i)
    {
        // input [model1.dat] (esempio)
        std::string input_name = model_files[i];
        std::ifstream ist2 {input_name};
        if (!ist2)
			throw Invalid();

        // store prima riga di[model1.dat] (esempio)
        int model_id;
        std::string model_name;
        ist2 >> model_id >> model_name;
        model_types.push_back(model{model_id, model_name});         // store prima riga

		int component_id;
        std::string component_name;
        int quantity;
		std::vector<component> tmp;

        while (ist2 >> component_id >> component_name >> quantity)
            tmp.push_back(component{component_id, component_name, quantity});   // store tutto il resto

		models_infos.push_back(tmp);
    }

	//(2) riempio components_infos
	std::ifstream ist_info {"component_info.txt"};
    if (!ist_info)
        throw Invalid();

    // store component_id, component_name, delivery_time (file components_info.dat)
    int component_id;
    std::string component_name;
    double delivery_time;
    while (ist_info >> component_id >> component_name >> delivery_time)
        components_infos.push_back(component_info{component_id, component_name, delivery_time});   // store
    ist_info.close();    // chiudo ist_info
}

std::vector<component> System::fill_components_month() {

}
