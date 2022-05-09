//
// Created by Artur on 08.05.2022.
//

#include "Vertex.h"

Vertex::Vertex(int labelVal, int colorVal)
: label{labelVal}, color{colorVal}{

}

void Vertex::addAdjacent(Vertex* vxPtr) {
    adjacent.push_back(vxPtr);
}

bool Vertex::operator<(const Vertex &rhs) {
    if(rhs.getLabel() > label)
        return true;
    else
        return false;
}

bool Vertex::operator>(const Vertex &rhs) {
    if(rhs.getLabel() > label)
        return false;
    else
        return true;
}
