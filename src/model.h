#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <list>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
namespace pt = boost::property_tree;

#include <vector>
#include <string>
#include <map>



class Model {
public:
    struct ClassRepr {
        std::string name;
        std::vector<std::string> attributes;
        std::vector<std::string> methods;
        double x, y;
    };

    struct LinkRepr {
        enum Type {
            ASSOCIATION,
            AGGREGATION,
            COMPOSITION,
            GENERALIZATION,
        };

        std::string from;
        std::string to;
        Type type;
    };

    Model();

    void loadXML(const std::string &filename);
    void storeXML(const std::string &filename);

    // functions to read the model
    int getTabIndex();
    std::vector<std::string> getClasses();
    ClassRepr &getClass(std::string name);
    std::vector<LinkRepr> getLinks();
    bool canUndo();
    bool canRedo();

    // model manipulations
    void addClass(std::string name);
    void renameClass(std::string name, std::string newName);
    void changeClassProperties(std::string name, ClassRepr &cls);
    void changeTab(int index);
    void undo();
    void redo();




private:
    // Can keep every executed command in order to recereate it later
    struct Command {
        enum Type {
            SWITCH_TAB,
            RENAME,
            CHANGE_PROPS,
            ADD_LINK,
            ADD_CLASS,
        };
        Type type;

        int newTab; // SWITCH_TAB
        struct {
            std::string name;
            ClassRepr cls;
        } newProps; // CHANGE_PROPS
    };

    struct ClassDiagram {
        // constructor from ptree
        ClassDiagram();
        ClassDiagram(pt::ptree &tree);
        std::map<std::string, ClassRepr> classes;
        std::vector<LinkRepr> links;
    };

    struct SequenceDiagram {
        std::string name;
    };

    // Can store complete state of the model at one time
    struct Snapshot {
        ClassDiagram classDiagram;
        std::map<std::string, SequenceDiagram> sequenceDiagrams;
        int tabIndex;
    };

    Snapshot baseState;
    Snapshot currentState;

    std::vector<Command> commandStack;
    // Head is at the last command, that was applied to the currentState
    int csHead;
    // Top is at the last command, that can be recovered by Redo
    int csTop;

    void applyCommand(Command cmd);
    void executeCommand(Snapshot &state, Command cmd);

};

#endif
