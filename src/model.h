#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "diagrams.h"


class Model {
public:
    Model();
    void loadXML(const std::string &filename);
    void storeXML(const std::string &filename);
    void undo();
    void redo();

private:
    ClassDiagram classDiagram;
    std::vector<SequenceDiagram> seqDiagrams;

};

#endif
