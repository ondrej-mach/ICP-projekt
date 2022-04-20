#include "model.h"
#include "diagrams.h"

#include <string>
#include <vector>

namespace pt = boost::property_tree;

Model::Model()
{

}

void Model::loadXML(const std::string &filename) {
    // empty xml tree object
    pt::read_xml(filename, tree);
}

void Model::storeXML(const std::string &filename) {
    pt::write_xml(filename, tree);
}

void Model::undo()
{

}

void Model::redo()
{

}
