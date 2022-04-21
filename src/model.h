#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
namespace pt = boost::property_tree;

#include "viewdata.h"


class Model {
public:
    Model();
    void loadXML(const std::string &filename);
    void storeXML(const std::string &filename);
    ViewData& getViewData();
    void applyCommand(Command cmd);
    void undo();
    void redo();

private:
    // Can store complete state of the model at one time
    struct Snapshot {
        pt::ptree tree;
        int tab;
    };

    Snapshot baseState;
    Snapshot currentState;

    ViewData viewData;

    std::vector<Command> commandStack;
    // Head is at the last command, that was applied to the currentState
    unsigned csHead;
    // Top is at the last command, that can be recovered by Redo
    unsigned csTop;

    void executeCommand(Snapshot &state, Command cmd);

};

#endif
