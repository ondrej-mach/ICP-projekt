/** @file model.h
 *  @brief Application's internal representation of all the data.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <list>
#include <qstring.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
namespace pt = boost::property_tree;

#include <vector>
#include <string>
#include <map>
#include <QVector>

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
            //NEW,
            //DELETE,
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
    void removeLink(std::string from, std::string to);
    void changeClassProperties(std::string name, ClassRepr cls);
    void changeTab(int index);
    //seq. diagram
    void addSeqDiagram();
    void addEntity(std::string sdName);
    void removeEntity(QString diagName, QString entityName);
    void addInteraction();
    void removeInteraction(QString diagName, QVector<double> coords);
    void addActivity();
    void removeActivity();

    void undo();
    void redo();



private:
    // Can keep every executed command in order to recereate it later
    struct Command {
        enum Type {
            SWITCH_TAB,
            CHANGE_CLASS_PROPS, // changing class methods, attributes, renaming
            ADD_LINK,
            REMOVE_LINK,
            ADD_CLASS,
            REMOVE_CLASS,
            ADD_SEQ_DIAGRAM,
            ADD_ENTITY,
            REMOVE_ENTITY,
            ADD_INTERACTION,
            REMOVE_INTERACTION,
            ADD_ACTIVITY,
            REMOVE_ACTIVITY,
        };
        Type type;

        int newTab; // SWITCH_TAB    
        ClassRepr cls; // CHANGE_CLASS_PROPS
        LinkRepr link; // ADD_LINK
        std::string currentName; // CHANGE_CLASS_PROPS, REMOVE_CLASS
        std::string from; //REMOVE_LINK
        std::string to; //REMOVE_LINK
        int x, y; // ADD_CLASS
        std::string sdName; //sequence diag. name
        std::string entityName; //entity name
        std::string actionName;
        QVector<double> coords;
    };

    struct ClassDiagram {
        // constructor from ptree
        ClassDiagram() = default;
        ClassDiagram(pt::ptree &tree);

        std::map<std::string, ClassRepr> classes;
        std::vector<LinkRepr> links;
    };

    struct SequenceDiagram {
        SequenceDiagram() = default;
        SequenceDiagram(pt::ptree &tree);

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
    void removeLinkExecute(Snapshot &state, std::string from, std::string to);
    void addClassExecute(Snapshot &state, double x=0, double y=0);
    void removeClassExecute(Snapshot &state, std::string name);
    void changeClassPropertiesExecute(Snapshot &state, Command cmd);

    void addSeqDiagramExecute(Snapshot &state);
    void addEntityExecute(Snapshot &state, std::string sdName /*, entita na smazani string*/);
    void removeEntityExecute(Snapshot &state, std::string sdName, std::string entityName);
    void addInteractionExecute(Snapshot &state/*, jakej sd string, interakce na pridani string*/);
    void removeInteractionExecute(Snapshot &state, std::string sdName, QVector<double> coords);
    //smazat
    void addActivityExecute(Snapshot &state);
    void removeActivityExecute(Snapshot &state);
};

extern Model model;

#endif
