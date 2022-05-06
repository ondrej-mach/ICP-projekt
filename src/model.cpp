/** @file model.cpp
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#include "model.h"

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <QDebug>


Model model;

Model::Model() {
    csHead = -1;
    csTop = -1;
    currentState.tabIndex = 0;
    currentState = baseState;

    // stuff for testing
    // TODO remove before end
    SequenceDiagram sd;
    sd.entities.push_back({SeqEntity::PARTICIPANT, "mycls"});
    sd.entities.push_back({SeqEntity::PARTICIPANT, "bruh"});
    sd.entities.push_back({SeqEntity::PARTICIPANT, "general"});
    sd.name = "Test SD";
    sd.actions.push_back({Action::CREATE, "mycls", "bruh", "create"});
    sd.actions.push_back({Action::SYNC, "mycls", "bruh", "hello1()"});
    sd.actions.push_back({Action::RETURN, "bruh", "mycls", "hello2()"});
    sd.actions.push_back({Action::CREATE, "mycls", "general", "hello3()"});
    sd.actions.push_back({Action::SYNC, "mycls", "general", "hello4()"});
    sd.actions.push_back({Action::RETURN, "general", "mycls", "hello5()"});
    sd.actions.push_back({Action::ACTIVATE, "mycls", "bruh", ""});
    sd.actions.push_back({Action::SYNC, "mycls", "bruh", "hello7()"});
    sd.actions.push_back({Action::DEACTIVATE, "mycls", "bruh", ""});
    sd.actions.push_back({Action::DESTROY, "mycls", "bruh", "destroy"});
    currentState.sequenceDiagrams.push_back(sd);
    SequenceDiagram sd1;
    sd1.entities.push_back({SeqEntity::PARTICIPANT, "mycls"});
    sd1.entities.push_back({SeqEntity::PARTICIPANT, "bruh"});
    sd1.entities.push_back({SeqEntity::PARTICIPANT, "general"});
    sd1.name = "Test SD1";
    sd1.actions.push_back({Action::CREATE, "mycls", "bruh", "create"});
    sd1.actions.push_back({Action::SYNC, "mycls", "bruh", "hello1()"});
    sd1.actions.push_back({Action::RETURN, "bruh", "mycls", "hello2()"});
    sd1.actions.push_back({Action::CREATE, "mycls", "general", "hello3()"});
    sd1.actions.push_back({Action::SYNC, "mycls", "general", "hello4()"});
    sd1.actions.push_back({Action::RETURN, "general", "mycls", "hello5()"});
    sd1.actions.push_back({Action::ACTIVATE, "mycls", "bruh", ""});
    sd1.actions.push_back({Action::SYNC, "mycls", "bruh", "hello7()"});
    sd1.actions.push_back({Action::DEACTIVATE, "mycls", "bruh", ""});
    sd1.actions.push_back({Action::DESTROY, "mycls", "bruh", "destroy"});
    currentState.sequenceDiagrams.push_back(sd1);
}

Model::ClassDiagram::ClassDiagram(pt::ptree &tree) {
    for (auto &element: tree) {
        if (element.first == "<xmlattr>") {
            // do nothing
        } else if (element.first == "class") {
            ClassRepr cr{};
            std::string name = element.second.get<std::string>("<xmlattr>.name");
            cr.name = name;
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
                {"AGGREGATION", LinkRepr::AGGREGATION},
                {"ASSOCIATION", LinkRepr::ASSOCIATION},
                {"COMPOSITION", LinkRepr::COMPOSITION},
                {"GENERALIZATION", LinkRepr::GENERALIZATION},
            };

            lr.type = typeTable[type_str];
            this->links.push_back(lr);

        } else {
            throw 1;
        }
    }
}

Model::SequenceDiagram::SequenceDiagram(pt::ptree &tree)
{
this->name = tree.get<std::string>("<xmlattr>.name");
for (auto &element: tree) {
        if (element.first == "<xmlattr>") {
            // do nothing
        } else if (element.first == "entity") {\

            SeqEntity se{};

            std::string name = element.second.get<std::string>("<xmlattr>.name");
            se.name = name;
            static std::map<std::string, SeqEntity::Type> entityTable{
                {"PARTICIPANT", SeqEntity::Type::PARTICIPANT},
            };
            se.type = entityTable[element.second.get<std::string>("<xmlattr>.type")];

            this->entities.push_back(se);

        } else if (element.first == "interaction") {
            Action action{};

            action.from = element.second.get<std::string>("<xmlattr>.from");
            action.to = element.second.get<std::string>("<xmlattr>.to");

            static std::map<std::string, Model::Action::Type> typeTable{
                {"SYNC", Model::Action::Type::SYNC},
                {"ASYNC", Model::Action::Type::ASYNC},
                {"RETURN", Model::Action::Type::RETURN},
                {"CREATE", Model::Action::Type::CREATE},
                {"DESTROY", Model::Action::Type::DESTROY},
            };
            for (auto &textElement: element.second) {
                if (textElement.first == "text") {
                    action.text = textElement.second.get<std::string>("");
                }
            }
            action.type = typeTable[element.second.get<std::string>("<xmlattr>.type")];
            this->actions.push_back(action);

        } else if (element.first == "action") {
            Action action{};
            action.from = element.second.get<std::string>("<xmlattr>.on");
            static std::map<std::string, Model::Action::Type> typeTable{
                {"ACTIVATE", Model::Action::Type::ACTIVATE},
                {"DEACTIVATE", Model::Action::Type::DEACTIVATE},
            };
            action.type = typeTable[element.second.get<std::string>("<xmlattr>.type")];

            // TODO Optional check if preceeding interaction is binary
            /*std::vector<Model::Action>::iterator iter = this->actions.end();
            Model::Action interaction = *iter;

            if (!interaction.isBinary()) {
                throw 1;
            }*/
            this->actions.push_back(action);

        } else {
            throw 1;
        }
    }
}


void Model::loadXML(const std::string &filename) {
    // empty tree object
    pt::ptree tree;
    pt::read_xml(filename, tree);
    currentState = Snapshot{};

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
            SequenceDiagram seqDiag = SequenceDiagram(diagram.second);
            currentState.sequenceDiagrams.push_back(seqDiag);
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
        pt::ptree clsTree{};

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
        pt::ptree linkTree{};
        switch(link.type) {
            case LinkRepr::ASSOCIATION:
                linkTree.put("<xmlattr>.type", "ASSOCIATION");
                break;
            case LinkRepr::AGGREGATION:
                linkTree.put("<xmlattr>.type", "AGGREGATION");
                break;
            case LinkRepr::COMPOSITION:
                linkTree.put("<xmlattr>.type", "COMPOSITION");
                break;
            case LinkRepr::GENERALIZATION:
                linkTree.put("<xmlattr>.type", "GENERALIZATION");
                break;
        }
        linkTree.put("<xmlattr>.from", link.from);
        linkTree.put("<xmlattr>.to", link.to);
        cdTree.push_back({"link", linkTree});
    }

    tree.push_back({"diagram", cdTree});


    // put each sequence diagram
    for (auto const &sd: currentState.sequenceDiagrams) {
        pt::ptree sdTree{};
        sdTree.put("<xmlattr>.type", "sequence");
        sdTree.put("<xmlattr>.name", sd.name);
        pt::ptree entityTree{};
        for(auto entity: sd.entities) {
            entityTree.put("<xmlattr>.name", entity.name);
            switch(entity.type) {
                case Model::SeqEntity::Type::PARTICIPANT:
                    entityTree.put("<xmlattr>.type", "PARTICIPANT");
                    break;
                 default: throw 1;
                    break;
            }
            sdTree.push_back({"entity", entityTree});
        }

        for(auto interaction: sd.actions) {
            pt::ptree interactionTree{};
            static std::map<Model::Action::Type, std::string> typeTable{
                {Model::Action::Type::SYNC, "SYNC"},
                {Model::Action::Type::ASYNC, "ASYNC"},
                {Model::Action::Type::RETURN, "RETURN"},
                {Model::Action::Type::CREATE, "CREATE"},
                {Model::Action::Type::DESTROY, "DESTROY"},
                {Model::Action::Type::ACTIVATE, "ACTIVATE"},
                {Model::Action::Type::DEACTIVATE, "DEACTIVATE"},
            };
            if(interaction.isBinary()) {
                interactionTree.put("<xmlattr>.type", typeTable[interaction.type]);
                interactionTree.put("<xmlattr>.from", interaction.from);
                interactionTree.put("<xmlattr>.to", interaction.to);
                interactionTree.add("text", interaction.text);
                sdTree.push_back({"interaction", interactionTree});
            }
            else {
                interactionTree.put("<xmlattr>.type", typeTable[interaction.type]);
                interactionTree.put("<xmlattr>.on", interaction.from);
                sdTree.push_back({"action", interactionTree});
            }
        }
        tree.push_back({"diagram", sdTree});
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

std::vector<std::string> Model::getSeqDiagrams() const
{
    std::vector<std::string> classNames;

    for (auto &sd: currentState.sequenceDiagrams) {
        classNames.push_back(sd.name);
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

std::vector<Model::SeqEntity> Model::getEntities(std::string name) const
{
    for (auto &sd: currentState.sequenceDiagrams) {
        if (sd.name == name) {
            return sd.entities;
        }
    }
    throw 1;
}

std::vector<Model::Action> Model::getActions(std::string name) const
{
    for (auto &sd: currentState.sequenceDiagrams) {
        if (sd.name == name) {
            return sd.actions;
        }
    }
    throw 1;
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

void Model::addSeqDiagram()
{
    Command cmd;
    cmd.type = Command::ADD_SEQ_DIAGRAM;
    applyCommand(cmd);
}

void Model::addLink(LinkRepr link) {
    Command cmd;
    cmd.type = Command::ADD_LINK;
    cmd.link = link;
    applyCommand(cmd);
}

void Model::removeLink(std::string from, std::string to) {
    Command cmd;
    cmd.type = Command::REMOVE_LINK;
    cmd.from = from;
    cmd.to = to;
    applyCommand(cmd);
}

void Model::addEntity(std::string sdName) {
    Command cmd;
    cmd.type = Command::ADD_ENTITY;
    cmd.sdName = sdName;
    applyCommand(cmd);
}

void Model::removeEntity(QString diagName, QString entityName) {
    Command cmd;
    cmd.type = Command::REMOVE_ENTITY;
    cmd.sdName = diagName.toStdString();
    cmd.entityName = entityName.toStdString();
    applyCommand(cmd);
}

void Model::addInteraction(QString sdName, QString from, QString to, Action::Type type) {
    Command cmd;
    cmd.type = Command::ADD_INTERACTION;
    cmd.from = from.toStdString();
    cmd.to = to.toStdString();
    cmd.sdName = sdName.toStdString();
    cmd.actionType = type;
    applyCommand(cmd);
}

void Model::removeInteraction(QString diagName, int index) {
    Command cmd;
    cmd.type = Command::REMOVE_INTERACTION;
    cmd.sdName = diagName.toStdString();
    cmd.index = index;
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

        case Command::REMOVE_LINK:
            removeLinkExecute(state, cmd.from, cmd.to);
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

        case Command::ADD_SEQ_DIAGRAM:
            addSeqDiagramExecute(state);
            break;

        case Command::ADD_ENTITY:
            addEntityExecute(state, cmd.sdName);
            break;

        case Command::REMOVE_ENTITY:
            removeEntityExecute(state, cmd.sdName, cmd.entityName);
            break;

        case Command::ADD_INTERACTION:
            addInteractionExecute(state, cmd.sdName, cmd.from, cmd.to, cmd.actionType);
            break;

        case Command::REMOVE_INTERACTION:
            removeInteractionExecute(state, cmd.sdName, cmd.index);
            break;

        default:
            throw 1;
            break;
    }
}

void Model::addInteractionExecute(Snapshot &state, std::string sdName, std::string from, std::string to, Action::Type actionType) {
    SequenceDiagram *seqDiag;
    for (auto &sd: state.sequenceDiagrams) {
        if (sd.name == sdName) {
                seqDiag = &sd;
                break;
        }
    }

    // Write new message according to interaction type
    static std::map<Model::Action::Type, std::string> typeTable {
        {Model::Action::Type::SYNC, "new_sync_message"},
        {Model::Action::Type::ASYNC, "new_async_message"},
        {Model::Action::Type::RETURN, "return"},
        {Model::Action::Type::CREATE, "create"},
        {Model::Action::Type::DESTROY, "destroy"},
    };

    // Check if create interaction already exists on to item
    if (actionType == Action::Type::CREATE) {
        for (auto isCreateAction: seqDiag->actions) {
            if (((to == isCreateAction.to) || (to == isCreateAction.from))
             && (isCreateAction.type == Action::Type::CREATE)) {
                return;
            }
        }
    }
    for (auto isCreateAction: seqDiag->actions) {
        if (((to == isCreateAction.to) || (to == isCreateAction.from)
        || (from == isCreateAction.from) || (from == isCreateAction.to))
         && (isCreateAction.type == Action::Type::DESTROY)) {
            return;
        }
    }

    // Create a new interaction, push it to seq. diagram
    Action action{actionType, from, to, typeTable[actionType]};
    seqDiag->actions.push_back(action);
}

void Model::removeInteractionExecute(Snapshot &state, std::string sdName, int index) {

    SequenceDiagram *seqDiag;
    for (auto &sd: state.sequenceDiagrams) {
        if (sd.name == sdName) {
                seqDiag = &sd;
                break;
        }
    }

    // Delete interaction from seq. diagram
    seqDiag->actions.erase(seqDiag->actions.begin() + index);
}


void Model::addEntityExecute(Snapshot &state, std::string sdName) {

    std::vector<SequenceDiagram> &existingSds = state.sequenceDiagrams;
    SequenceDiagram *seqDiag;

    for (auto &sd: existingSds) {
        if (sd.name == sdName) {
                seqDiag = &sd;
                break;
        }
    }

    std::string newName = "NewEntity";
    int n = 1;
    std::vector<Model::SeqEntity> existingEntities = this->getEntities(sdName);

    for (auto &entity: existingEntities) {
        if (entity.name == newName) {
            newName = "NewEntity" + std::to_string(n);
            n++;
        }
    }

    // Create a new entity, push it to seq. diagram
    SeqEntity entity {SeqEntity::Type::PARTICIPANT, newName};
    seqDiag->entities.push_back(entity);
}

void Model::removeEntityExecute(Snapshot &state, std::string sdName, std::string entityName) {
    SequenceDiagram *seqDiag;
    for (auto &sd: state.sequenceDiagrams) {
        if (sd.name == sdName) {
                seqDiag = &sd;
                break;
        }
    }
    for (auto it=seqDiag->actions.begin(); it!=seqDiag->actions.end(); ) {
        auto &interaction = *it;
        if ((interaction.to == entityName) || (interaction.from == entityName)) {
           it = seqDiag->actions.erase(it);
        } else {
            it++;
        }
    }
    for (std::vector<SeqEntity>::iterator it = seqDiag->entities.begin(); it != seqDiag->entities.end(); ) {
        auto &entity = (*it);
        if (entity.name == entityName) {
            it = seqDiag->entities.erase(it);
            return;
        } else {
            ++it;
        }
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

void Model::removeLinkExecute(Snapshot &state, std::string from, std::string to) {
    for (std::vector<LinkRepr>::iterator it = state.classDiagram.links.begin(); it != state.classDiagram.links.end(); ) {
        auto &existingLink = (*it);
        if ((existingLink.from == from) && (existingLink.to == to)) {
            it = state.classDiagram.links.erase(it);
            return;
        } else {
            ++it;
        }
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
           it = state.classDiagram.links.erase(it);
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

void Model::addSeqDiagramExecute(Snapshot &state) {
    auto &sds = state.sequenceDiagrams;
    std::string newName = "Sequence diagram";
    int n = 1;

    while (find_if(sds.begin(), sds.end(), [newName](auto x){return x.name == newName;}) != sds.end()) {
        newName = "Sequence diagram " + std::to_string(n);
        n++;
    }

    SequenceDiagram newSeqDiagram;
    newSeqDiagram.name = newName;
    sds.push_back(newSeqDiagram);
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

bool Model::Action::isBinary() {
    return (type == SYNC)
           || (type ==  ASYNC)
           || (type == RETURN)
           || (type == CREATE)
           || (type == DESTROY);
}
