// leggo tutte le informazioni sui vari file *.dat

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Reading_files
{   // per leggere i vari modelli all'interno di models.dat
    string file;                                    // models.dat
};

struct Reading_models
{   // per leggere il nome del modello e l'id
    int model_id;                                   // [model1.dat] (esempio)
    string model_name;
};

struct Reading_components
{   // per leggere le informazioni sui componenti nei file dei modelli
    int component_id;                               // [model1.dat] (esempio)
    string component_name;
    double quantity;    // mi tocca mettere double per non avere conflitti con component_id
};

struct Reading_info
{   // per leggere le informazioni sui componenti su components_info.dat
    int component_id;                               // components_info.dat
    string component_name;
    double delivery_time;    // mi tocca mettere double per non avere conflitti con component_id
};

struct Reading_orders
{   // per leggere gli ordini su orders.dat
    int time_stamp;                                 // orders.dat
    int model_id;
    int quantity_ordered;
};

class Invalid{};                                    // per lanciare eccezioni

int main()
{
    // input models.dat
    string input_name = "models.dat";
    ifstream ist {input_name};
    if (!ist)
        throw Invalid();

    // store models
    vector<Reading_files> files;                    // questo è il mio vettore con i model
    string file;
    while (ist >> file)
        files.push_back(Reading_files{file});
    ist.close();    // chiudo ist

    // store model_id, model_name
    vector<Reading_models> models;                  // questo è il mio vettore con i model_id, model_name
    for (int i=0; i < files.size(); ++i)
    {
        // input [model1.dat] (esempio)
        string input_name = files[i].file;
        ifstream ist {input_name};
        if (!ist)
            throw Invalid();

        // store prima riga di[model1.dat] (esempio)
        int model_id;
        string model_name;
        ist >> model_id >> model_name;
        models.push_back(Reading_models{model_id, model_name});         // store prima riga
    }
    
    // store component_id, component_name, quantity
    vector<Reading_components> components;          // questo è il mio vettore con i component_id, component_name, quantity
    for (int i=0; i < files.size(); ++i)
    {
        // input [model1.dat] (esempio)
        string input_name = files[i].file;
        ifstream ist {input_name};
        if (!ist)
            throw Invalid();

        // store dalla seconda riga in poi su [model1.dat] (esempio)
        int burn1;      // variabile scarto
        string burn2;   // variabile scarto
        int component_id;
        string component_name;
        double quantity;

        ist >> burn1;   // brucio prima parola
        ist >> burn2;   // brucio seconda parola, in totale brucio la prima riga
        while (ist >> component_id >> component_name >> quantity)
            components.push_back(Reading_components{component_id, component_name, quantity});   // store tutto il resto
    }

    // input components_info.dat
    input_name = "components_info.dat";
    ifstream ist_info {input_name};
    if (!ist_info)
        throw Invalid();

    // store component_id, component_name, delivery_time (file components_info.dat)
    vector<Reading_info> informations;              // questo è il mio vettore con i model_id, model_name, delivery_time
    int component_id;
    string component_name;
    double delivery_time;
    while (ist_info >> component_id >> component_name >> delivery_time)
        informations.push_back(Reading_info{component_id, component_name, delivery_time});   // store
    ist_info.close();    // chiudo ist_info

    // **************************
    // ***** lettura ordini *****
    // **************************

    // input orders.dat
    input_name = "orders.dat";
    ifstream ist_orders {input_name};
    if (!ist_orders)
        throw Invalid();

    // store time_stamp, model_id e quantity_ordered
    vector<Reading_orders> orders;                  // questo è il mio vettore con i time_stamp, model_id e quantity_ordered
    int time_stamp;
    int model_id;
    int quantity_ordered;
    while (ist_orders >> time_stamp >> model_id >> quantity_ordered)
        orders.push_back(Reading_orders{time_stamp, model_id, quantity_ordered});   // store

    // *********************
    // ***** print all *****
    // *********************

    cout << "I file con i modelli sono: ";          // ***** debug *****
    for (int i=0; i < files.size(); ++i)            // ***** debug *****
        cout << files[i].file << " ";               // ***** debug *****
    cout << endl;                                   // ***** debug *****

    cout << "I model_id sono: ";                    // ***** debug *****
    for (int i=0; i < models.size(); ++i)           // ***** debug *****
        cout << models[i].model_id << " ";          // ***** debug *****
    cout << endl;                                   // ***** debug *****

    cout << "I model_name sono: ";                  // ***** debug *****
    for (int i=0; i < models.size(); ++i)           // ***** debug *****
        cout << models[i].model_name << " ";        // ***** debug *****
    cout << endl;                                   // ***** debug *****

    cout << "I component_id sono: ";                // ***** debug *****
    for (int i=0; i < components.size(); ++i)       // ***** debug *****
        cout << components[i].component_id << " ";  // ***** debug *****
    cout << endl;                                   // ***** debug *****

    cout << "I component_name sono: ";              // ***** debug *****
    for (int i=0; i < components.size(); ++i)       // ***** debug *****
        cout << components[i].component_name << " ";// ***** debug *****
    cout << endl;                                   // ***** debug *****

    cout << "Le quantity sono: ";                   // ***** debug *****
    for (int i=0; i < components.size(); ++i)       // ***** debug *****
        cout << components[i].quantity << " ";      // ***** debug *****
    cout << endl;                                   // ***** debug *****

    cout << "Le delivery_time sono: ";              // ***** debug *****
    for (int i=0; i < informations.size(); ++i)     // ***** debug *****
        cout << informations[i].delivery_time << " ";//***** debug *****
    cout << endl;                                   // ***** debug *****

    // ************************
    // ***** print orders *****
    // ************************

    cout << "Gli ordini sono:\n";
    for (int i=0; i < orders.size(); ++i)
    {
        cout << orders[i].time_stamp << " "
            << orders[i].model_id << " "
            << orders[i].quantity_ordered
            << endl;
    }

}   // end main()
