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
        std::string name="";
        std::vector<std::string> attributes{};
        std::vector<std::string> methods{};
        double x=0, y=0;
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

    struct SeqEntity {
        enum Type {
            PARTICIPANT,
        };

        Type type;
        std::string name;
    };

    struct Action {
        enum Type {
            // binary from -> to
            SYNC,
            ASYNC,
            RETURN,
            CREATE,
            DESTROY,
            // unary, use only [from] attribute
            ACTIVATE,
            DEACTIVATE,
            NEW,
            DELETE,
        };

        Type type;
        std::string from;
        std::string to;
        // text is only used on binary interactions
        std::string text;

        bool isBinary();
    };


    Model();

    void loadXML(const std::string &filename);
    void storeXML(const std::string &filename);

    // functions to read the model
    int getTabIndex() const;
    // class diagram
    std::vector<std::string> getClasses() const;
    std::vector<std::string> getSeqDiagrams() const;
    ClassRepr getClass(std::string name) const;
    std::vector<LinkRepr> getLinks() const;
    // sequence diagram
    std::vector<SeqEntity> getEntities(std::string name) const;
    std::vector<Action> getActions(std::string name) const;


    bool classExists(std::string name) const;
    bool canUndo() const;
    bool canRedo() const;


    // model manipulations
    void addClass(double x=0, double y=0);
    void removeClass(std::string name);
    void addLink(LinkRepr link);
    void changeClassProperties(std::string name, ClassRepr cls);
    void changeTab(int index);

    void addSeqDiagram();

    void undo();
    void redo();




private:
    // Can keep every executed command in order to recereate it later
    struct Command {
        enum Type {
            SWITCH_TAB,
            CHANGE_CLASS_PROPS, // changing class methods, attributes, renaming
            ADD_LINK,
            ADD_CLASS,
            REMOVE_CLASS,
            ADD_SEQ_DIAGRAM,
        };
        Type type;

        int newTab; // SWITCH_TAB    
        ClassRepr cls; // CHANGE_CLASS_PROPS
        LinkRepr link; // ADD_LINK
        std::string currentName; // CHANGE_CLASS_PROPS, REMOVE_CLASS
        int x, y; // ADD_CLASS
    };

    struct ClassDiagram {
        // constructor from ptree
        ClassDiagram() = default;
        ClassDiagram(pt::ptree &tree);
        std::map<std::string, ClassRepr> classes;
        std::vector<LinkRepr> links;
    };

    struct SequenceDiagram {
        std::string name;
        std::vector<SeqEntity> entities;
        std::vector<Action> actions;
    };

    // Can store complete state of the model at one time
    struct Snapshot {
        ClassDiagram classDiagram;
        std::vector<SequenceDiagram> sequenceDiagrams;
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

    void addLinkExecute(Snapshot &state, LinkRepr newLink);
    void addClassExecute(Snapshot &state, double x=0, double y=0);
    void removeClassExecute(Snapshot &state, std::string name);
    void changeClassPropertiesExecute(Snapshot &state, Command cmd);

    void addSeqDiagramExecute(Snapshot &state);
};

extern Model model;

#endif
