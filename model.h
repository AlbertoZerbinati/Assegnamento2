#ifndef MODEL_H
#define MODEL_H

#include <iostream>

struct model
{   // per leggere il nome del modello e l'id
    int model_id;
    std::string model_name;
};

inline std::ostream& operator<< (std::ostream& os, const model& m) {
    os << "--  " << m.model_id << ", " << m.model_name << ".\n";
    return os;
};

#endif
