#include "model.h"
#include "modeldata.h"

#include <string>
#include <vector>
#include <map>


Model model;

Model::Model() {
    csHead = -1;
    csTop = -1;

    // everything is empty by default
    currentState.classDiagram = ClassDiagram{};
    currentState.classDiagram.classes = std::map<std::string, ClassRepr>{};
    currentState.sequenceDiagrams = std::map<std::string, SequenceDiagram>{};

    currentState.tabIndex = 0;

    currentState = baseState;
}

Model::ClassDiagram::ClassDiagram() {}

Model::ClassDiagram::ClassDiagram(pt::ptree &tree) {
    for (auto &element: tree) {
        if (element.first == "<xmlattr>") {
            // do nothing
        } else if (element.first == "class") {
            ClassRepr cr{};
            std::string name = element.second.get<std::string>("<xmlattr>.name");

            cr.x = element.second.get<double>("<xmlattr>.x");
            cr.y = element.second.get<double>("<xmlattr>.y");

            for (auto &child: element.second) {
                if (child.first == "<xmlattr>") {
                    // do nothing
                } else if (child.first == "attribute") {
                    cr.attributes.push_back(child.second.data());
                } else if (child.first == "method") {
                    cr.methods.push_back(child.second.data());
                } else {
                    throw 1;
                }
            }

            this->classes[name] = cr;

        } else if (element.first == "link") {
            LinkRepr lr;

            std::string type_str = element.second.get<std::string>("<xmlattr>.type");
            lr.from = element.second.get<std::string>("<xmlattr>.from");
            lr.to = element.second.get<std::string>("<xmlattr>.to");

            static std::map<std::string, LinkRepr::Type> typeTable{
                {"aggregation", LinkRepr::AGGREGATION},
                {"association", LinkRepr::ASSOCIATION},
                {"composition", LinkRepr::COMPOSITION},
                {"generalization", LinkRepr::GENERALIZATION},
            };

            lr.type = typeTable[type_str];
            this->links.push_back(lr);

        } else {
            throw 1;
        }
    }
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
            classDiagramFound = true;

            // Diagram name for tab
            // = diagram.second.get<std::string>("<xmlattr>.name");
            currentState.classDiagram = ClassDiagram(diagram.second);

        } else if (diagramType == "sequence") {
            continue;
        } else {
            // invalid diagram type
            throw 1;
        }
    }

    // Thre must be a class diagram in order to be valid
    if (!classDiagramFound) {
        throw 1;
    }
    baseState = currentState;
    csHead = -1;
    csTop = -1;
}

void Model::storeXML(const std::string &filename) {
    // TODO l8er
    pt::ptree tree;

    // put class diagram
    pt::ptree cdTree;
    cdTree.put("<xmlattr>.type", "class");
    for (auto const &cls: currentState.classDiagram.classes) {
        pt::ptree clsTree;
        clsTree.put("<xmlattr>.name", cls.first);
        clsTree.put("<xmlattr>.x", cls.second.x);
        clsTree.put("<xmlattr>.y", cls.second.y);

        for (auto const &attr: cls.second.attributes) {
            clsTree.add("attribute", attr);
        }
        for (auto const &method: cls.second.methods) {
            clsTree.add("method", method);
        }
        cdTree.push_back({"class", clsTree});
    }
    for (auto &link: currentState.classDiagram.links) {
        pt::ptree linkTree;
        //linkTree.put("<xmlattr>.type", link.type);
        linkTree.put("<xmlattr>.from", link.from);
        linkTree.put("<xmlattr>.to", link.to);
        linkTree.push_back({"link", linkTree});
    }

    tree.push_back({"diagram", cdTree});


    // put each sequence diagram
    for (auto const &sd: currentState.sequenceDiagrams) {
        // TODO
    }

    pt::write_xml(filename, tree);
}


int Model::getTabIndex() const {
    return currentState.tabIndex;
}

std::vector<std::string> Model::getClasses() const {
    std::vector<std::string> classNames;

    for (auto &classPair: currentState.classDiagram.classes) {
        classNames.push_back(classPair.first);
    }
    return classNames;
}

Model::ClassRepr Model::getClass(std::string name) const
{
    return currentState.classDiagram.classes.at(name);
}

std::vector<Model::LinkRepr> Model::getLinks() const
{
    return currentState.classDiagram.links;
}

bool Model::classExists(std::string name) const {
    auto &existingClasses = currentState.classDiagram.classes;
    return existingClasses.find(name) != existingClasses.end();
}

bool Model::canUndo() const
{
    return csHead >= 0;
}

bool Model::canRedo() const
{
    return csHead < csTop;
}

void Model::addClass(double x, double y) {
    Command cmd;
    cmd.type = Command::ADD_CLASS;
    cmd.x = x;
    cmd.y = y;
    applyCommand(cmd);
}

void Model::removeClass(std::string name) {
    Command cmd;
    cmd.type = Command::REMOVE_CLASS;
    cmd.currentName = name;
    applyCommand(cmd);
}

void Model::changeClassProperties(std::string name, Model::ClassRepr cls)
{
    Command cmd;
    cmd.type = Command::CHANGE_CLASS_PROPS;
    cmd.cls = cls;
    cmd.currentName = name;
    applyCommand(cmd);
}

void Model::changeTab(int index) {
    Command cmd;
    cmd.type = Command::SWITCH_TAB;
    cmd.newTab = index;
    applyCommand(cmd);
}

void Model::addLink(LinkRepr link) {
    Command cmd;
    cmd.type = Command::ADD_LINK;
    cmd.link = link;
    applyCommand(cmd);
}

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

        case Command::ADD_LINK:
            addLinkExecute(state, cmd.link);
            break;

        case Command::ADD_CLASS:
            addClassExecute(state, cmd.x, cmd.y);
            break;

        case Command::CHANGE_CLASS_PROPS:
            changeClassPropertiesExecute(state, cmd);
            break;

        case Command::REMOVE_CLASS:
            removeClassExecute(state, cmd.currentName);
            break;

        default:
            throw 1;
            break;
    }
}

void Model::addLinkExecute(Snapshot &state, LinkRepr newLink) {
    for (auto &existingLink: state.classDiagram.links) {
        if ((existingLink.from == newLink.from) && (existingLink.to == newLink.to)) {
            // rewrite the existing link
            existingLink.type = newLink.type;
            return;
        }
    }
    // link between those two does not exist, so we have to add it
    // check if referenced classes exist
    auto &existingClasses = state.classDiagram.classes;
    if ((existingClasses.find(newLink.to) != existingClasses.end())
            && (existingClasses.find(newLink.from) != existingClasses.end())) {
        // add the link
        state.classDiagram.links.push_back(newLink);
    } else {
        throw 1;
    }
}

void Model::addClassExecute(Snapshot &state, double x, double y) {
    auto &existingClasses = state.classDiagram.classes;

    std::string newName = "NewClass";
    int n = 1;

    while (existingClasses.find(newName) != existingClasses.end()) {
        newName = "NewClass" + std::to_string(n);
        n++;
    }

    ClassRepr cls = {newName, {"+attribute"}, {"+method"}, x, y};
    existingClasses[newName] = cls;
}

void Model::removeClassExecute(Snapshot &state, std::string name) {
    // remove all the links associated with this class to prevent inconsistencies
    auto &links = state.classDiagram.links;
    for (auto it=links.begin(); it!=links.end(); ) {
        auto &link = *it;
        if ((link.from == name) || (link.to == name)) {
           state.classDiagram.links.erase(it);
        } else {
            it++;
        }
    }
    // finaly remove the class itself
    state.classDiagram.classes.erase(name);
}

void Model::changeClassPropertiesExecute(Snapshot &state, Command cmd) {
    auto &existingClasses = state.classDiagram.classes;

    // Class with this name does not exist
    if (existingClasses.find(cmd.currentName) == existingClasses.end()) {
        throw 1;
    }

    auto &curName = cmd.currentName;
    auto &newName = cmd.cls.name;
    // Do we have to rename or just set new attributes?
    if (curName == newName) {
        // name is the same
        existingClasses[newName] = cmd.cls;
    } else {
        // name was changed
        if (existingClasses.find(newName) == existingClasses.end()) {

            existingClasses.erase(curName);
            existingClasses[newName] = cmd.cls;

            // change the links referring to this name
            auto &links = state.classDiagram.links;
            for (auto &link: links) {
                if (link.from == curName) {
                    link.from = newName;
                }
                if (link.to == curName) {
                    link.to = newName;
                }
            }

        } else {
            // class with that name already exists
            throw 1;
        }
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
