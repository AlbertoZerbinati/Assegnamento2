#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>


struct component
{   // per leggere le informazioni sui componenti nei file dei modelli
    int component_id;                               // [model1.dat] (esempio)
    std::string component_name;
    double quantity;    // mi tocca mettere double per non avere conflitti con component_id
};

#endif
