#include "model.h"
#include "viewdata.h"

#include <string>
#include <vector>



Model::Model()
{

}

void Model::loadXML(const std::string &filename) {
    // empty xml tree object
    pt::read_xml(filename, baseState.tree);
    currentState.tree = baseState.tree;
}

void Model::storeXML(const std::string &filename) {
    pt::write_xml(filename, currentState.tree);
}

ViewData& Model::getViewData()
{
//    viewData =
//    for (pt::ptree::value_type &v, tree.get_child("debug.modules")) {
//        // The data function is used to access the data stored in a node.
//        m_modules.insert(v.second.data());
//    }
//    return viewData;
}

void Model::applyCommand(Command cmd) {
    executeCommand(currentState, cmd);
    // exceptions?

    csHead++;
    if (csHead >= commandStack.capacity()) {
        commandStack.reserve(csHead+1);
    }

    commandStack[csHead] = cmd;
    csTop = csHead;
}

void Model::executeCommand(Snapshot &state, Command cmd) {
    switch(cmd.type) {
        case Command::SWITCH_TAB:
            state.tab = cmd.newTab;
            break;

        default:
            break;
    }
}

void Model::undo() {
    csHead--;
    currentState = baseState;
    for (unsigned i=0; i<=csHead; i++) {
        executeCommand(currentState, commandStack[i]);
    }
}

void Model::redo() {
    if (csHead < csTop) {
        csHead++;
        executeCommand(currentState, commandStack[csHead]);
    }
}
