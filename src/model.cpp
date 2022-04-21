#include "model.h"
#include "modeldata.h"

#include <string>
#include <vector>
#include <map>



Model::Model() {
    csHead = -1;
    csTop = -1;

}

void Model::loadXML(const std::string &filename) {
    // empty tree object
    pt::ptree tree;
    pt::read_xml(filename, tree);

    bool classDiagramFound = false;
    // for each diagram
    for (pt::ptree::value_type &diagram: tree) {
        std::string diagramType = diagram.second.get<std::string>("<xmlattr>.type");

        if (diagramType == "class") {
            // There can be only one class diagram
            if (classDiagramFound) {
                throw 1;
            }
            // Diagram name for tab
            // = diagram.second.get<std::string>("<xmlattr>.name");

            for (auto &element: diagram.second) {
                if (element.first == "class") {
                    ClassRepr cr{};
                    std::string name = element.second.get<std::string>("<xmlattr>.name");

                    cr.x = element.second.get<double>("<xmlattr>.x");
                    cr.y = element.second.get<double>("<xmlattr>.y");

                    for (auto &child: element.second) {
                        if (child.first == "attribute") {
                            cr.attributes.push_back(child.second.data());
                        } else if (child.first == "method") {
                            cr.methods.push_back(child.second.data());
                        } else {
                            throw 1;
                        }
                    }

                    currentState.classDiagram.classes[name] = cr;

                } else if (element.first == "link") {
                    LinkRepr lr;

                    std::string type_str = element.second.get<std::string>("<xmlattr>.name");

                    static std::map<std::string, LinkRepr::Type> typeTable{
                        {"aggregation", LinkRepr::AGGREGATION},
                        {"association", LinkRepr::ASSOCIATION},
                        {"composition", LinkRepr::COMPOSITION},
                        {"generalization", LinkRepr::GENERALIZATION},
                    };

                    lr.type = typeTable[type_str];
                    currentState.classDiagram.links.push_back(lr);

                } else {
                    throw 1;
                }
            }
            classDiagramFound = true;
            continue;
        }

        if (diagramType == "sequence") {
            continue;
        }

        // invalid diagram type
        throw 1;
    }

    // Thre must be a class diagram in order to be valid
    if (!classDiagramFound) {
        throw 1;
    }
    baseState = currentState;
}

void Model::storeXML(const std::string &filename) {
    // TODO l8er
    //pt::write_xml(filename, currentState.tree);
}


int Model::getTabIndex() {
    return currentState.tabIndex;
}

std::vector<std::string> Model::getClasses() {
    std::vector<std::string>classNames{};

    for(auto const& tuple: currentState.classDiagram.classes) {
        classNames.push_back(tuple.first);
    }
    return classNames;
}

void Model::changeTab(int index) {
    Command cmd = {Command::SWITCH_TAB, {index}};
    applyCommand(cmd);
};



// High-level, applies command to the current state and commandStack
void Model::applyCommand(Command cmd) {
    executeCommand(currentState, cmd);
    // exceptions?

    csHead++;
    commandStack.resize(csHead+1);
    commandStack[csHead] = cmd;
    csTop = csHead;
}

// Low-level, applies one command to specific snapshot.
// Should be called exclusively by applyCommand
void Model::executeCommand(Snapshot &state, Command cmd) {
    switch(cmd.type) {
        case Command::SWITCH_TAB:
            state.tabIndex = cmd.newTab;
            break;

        default:
            break;
    }
}

void Model::undo() {
    if (csHead >= 0) {
        csHead--;
        currentState = baseState;
        for (auto i=0; i<=csHead; i++) {
            executeCommand(currentState, commandStack[i]);
        }
    }
}

void Model::redo() {
    if (csHead < csTop) {
        csHead++;
        executeCommand(currentState, commandStack[csHead]);
    }
}
