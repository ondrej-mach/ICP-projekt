#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "diagrams.h"



class Model {
public:
    Model();
    void loadXML(const std::string &filename);
    void storeXML(const std::string &filename);
    void undo();
    void redo();

private:
    boost::property_tree::ptree tree;

};

#endif
