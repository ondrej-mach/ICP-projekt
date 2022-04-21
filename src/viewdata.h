#ifndef VIEWDATA_H
#define VIEWDATA_H

#include <vector>

struct ClassRepresentation {
    int x, y;

};

struct LinkRepresentation {
    enum Type {
        ASSOCIATION,
        AGGREGATION,
        COMPOSITION,
        GENERALIZATION,
    };

    ClassRepresentation *from;
    ClassRepresentation *to;
    Type type;
};

struct ClassDiagram {
    std::vector<ClassRepresentation> classes;
    std::vector<LinkRepresentation> links;
};

struct SequenceDiagram {

};

struct Command {
    enum Type {
        SWITCH_TAB,
        RENAME,
        CHANGE_PROPS,
        ADD_LINK,
        ADD_CLASS,
    };
    Type type;
    union {
        int newTab;
    };
};

struct ViewData {
    ClassDiagram classDiagram;
    std::vector<SequenceDiagram> sequenceDiagrams;
    int tabIndex;
};

#endif
