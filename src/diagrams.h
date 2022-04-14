#ifndef DIAGRAMS_H
#define DIAGRAMS_H

#include <vector>

struct ClassRepresentation {
    int x, y;

};

enum LinkType {
    LINK_ASSOCIATION,
    LINK_DIRECTED_ASSOC,
    LINK_AGGREGATION,
    LINK_COMPOSITION,
    LINK_INHERITANCE,
    LINK_REALIZATION
};

struct LinkRepresentation {
    ClassRepresentation *from;
    ClassRepresentation *to;
    LinkType type;
};

struct ClassDiagram {
    std::vector<ClassRepresentation> classes;
    std::vector<LinkRepresentation> links;
};

struct SequenceDiagram {

};

#endif
