#include "model.h"
#include "diagrams.h"

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

void Model::loadXML(const std::string &filename) {
    // empty xml tree object
    pt::ptree tree;

    pt::read_xml(filename, tree);
};

void Model::storeXML(const std::string &filename) {
    // empty xml tree object
    pt::ptree tree;

    pt::write_xml(filename, tree);
};
