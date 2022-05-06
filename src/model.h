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

    /** @brief Laods the data from a file.
     *  @param filename Name of the XML file containing diagrams.
     *  @return Void.
     */
    void loadXML(const std::string &filename);

    /** @brief Saves the data in a file.
     *  @param filename Name of the output XML file.
     *  @return Void.
     */
    void storeXML(const std::string &filename);

    // functions to read the model

    /** @brief Gets the index of the selected tab.
     *  @return The index of currently selected tab.
     */
    int getTabIndex() const;

    // class diagram

    /** @brief Gets the the list of all names of classes in class diagram.
     *  @return Vector of names of all the classes.
     */
    std::vector<std::string> getClasses() const;

    /** @brief Gets the the list of all names of sequence diagrams.
     *  @return Vector of names of all the sequence diagrams.
     */
    std::vector<std::string> getSeqDiagrams() const;

    /** @brief Gets the data representation of a class.
     *  @param name The name of the class.
     *  @return The structure contataining all the data about the class.
     */
    ClassRepr getClass(std::string name) const;

    /** @brief Gets all the relationships in the class diagram.
     *  @return Vector of all the relationships from the class diagram.
     */
    std::vector<LinkRepr> getLinks() const;

    // sequence diagram

    /** @brief Gets all the entities in given sequence diagram.
     *  @param name The name of the sequence diagram.
     *  @return Vector of all the entities from the sequence diagram.
     */
    std::vector<SeqEntity> getEntities(std::string name) const;

    /** @brief Gets all the actions in given sequence diagram.
     *  @param name The name of the sequence diagram
     *  @return Vector of all the actions from the sequence diagram.
     */
    std::vector<Action> getActions(std::string name) const;

    /** @brief Checks, whether the class exists in the class diagram.
     *  @param name The name of the class
     *  @return Void.
     */
    bool classExists(std::string name) const;

    /** @brief Checks, whether the undo operation is available.
     *  @return True if the model can undo.
     */
    bool canUndo() const;

    /** @brief Checks, whether the redo operation is available.
     *  @return True if the model can redo.
     */
    bool canRedo() const;


    // model manipulations

    /** @brief Adds class to the current model's class diagram.
     *
     *  The name of the new class is generated inside the model.
     *
     *  @param x The x coordinate of the center of the box.
     *  @param y The y coordinate.
     *  @return Void.
     */
    void addClass(double x=0, double y=0);

    /** @brief Deletes class from the class diagram.
     *  @param name Name of the deleted class.
     *  @return Void.
     */
    void removeClass(std::string name);

    /** @brief Adds relationship between two classes in the class diagram.
     *  @param link Structure with all the data about the link.
     *  @return Void.
     */
    void addLink(LinkRepr link);

    /** @brief Deletes relationship from the class diagram.
     *  @param from Name of the class, where the link starts.
     *  @param to Name of the class, where the link ends.
     *  @return Void.
     */
    void removeLink(std::string from, std::string to);

    /** @brief Changes properties of the class.
     *
     *  This can change class' name, coordinates, attributes and methods.
     *
     *  @param name The current name of the class in the model.
     *  @param cls The new properties of the class.
     *  @return Void.
     */
    void changeClassProperties(std::string name, ClassRepr cls);

    /** @brief Changes current tab in the model.
     *  @param index Index of the newly chosen tab.
     *  @return Void.
     */
    void changeTab(int index);

    //seq. diagram

    /** @brief Adds a new sequence diagram to the current model.
     *
     *  @return Void.
     */
    void addSeqDiagram();

    void addEntity(std::string sdName);
    void removeEntity(QString diagName, QString entityName);
    void addInteraction(QString sdName, QString from, QString to, Action::Type type);
    void removeInteraction(QString diagName, int index);
    void addActivity();
    void removeActivity();

    /** @brief Applies undo action to the model
     *  @return Void.
     */
    void undo();

    /** @brief Applies redo action to the model
     *  @return Void.
     */
    void redo();



private:
    /** @brief Keeps every command so it can be executed later.
     *  The structure  stores type and operands of every possible command.
     *  This is a part of command pattern to implement undo/redo functionality.
     */
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
        };
        Type type;

        int newTab; // SWITCH_TAB
        ClassRepr cls; // CHANGE_CLASS_PROPS
        LinkRepr link; // ADD_LINK
        std::string currentName; // CHANGE_CLASS_PROPS, REMOVE_CLASS
        std::string from; //REMOVE_LINK
        std::string to; //REMOVE_LINK
        int x, y; // ADD_CLASS, ADD_INTERACTION
        std::string sdName; //sequence diag. name
        std::string entityName; //entity name
        std::string actionName;
        int index;
        Action::Type actionType;
    };

    /** @brief Representation of a class diagram at one time.
     */
    struct ClassDiagram {
        // constructor from ptree
        ClassDiagram() = default;
        ClassDiagram(pt::ptree &tree);

        std::map<std::string, ClassRepr> classes;
        std::vector<LinkRepr> links;
    };

    /** @brief Representation of a sequence diagram at one time.
     */
    struct SequenceDiagram {
        SequenceDiagram() = default;
        SequenceDiagram(pt::ptree &tree);

        std::string name;
        std::vector<SeqEntity> entities;
        std::vector<Action> actions;
    };

    /** @brief Stores complete state of the model at one time.
     *  Snapshot is all that is needed to display anything in the program.
     *  Entire model consists of base snapshot, current snapshot
     *  and the stack of commands.
     */
    struct Snapshot {
        ClassDiagram classDiagram;
        std::vector<SequenceDiagram> sequenceDiagrams;
        int tabIndex;
    };

    /** @brief Stores the base snapshot of the model.
     *  This snapshot is rarely modified, it is loaded only
     *  at the start of program or when the file is loaded.
     *  It contains the oldest data, that can be recovered with undo function.
     */
    Snapshot baseState;

    /** @brief Stores the current snapshot of the model.
     *  This snapshot is modified every time, any action is taken.
     *  When undo operation is called, this state is recreated from
     *  the base state and command stack.
     */
    Snapshot currentState;

    /** @brief Stores every action taken.
     *  All actions, that user takes are stored on this stack.
     */
    std::vector<Command> commandStack;
    /** @brief Head of the  command stack.
     *  Head is at the last command, that was applied to the currentState.
     *  When undo operation is called, head decrements by one command.
     *  Head should be always synchronised with currentState.
     */
    int csHead;

    /** @brief Top of the command stack
     *  Top is the index of the last command, that can be recovered by Redo.
     *  After user does an action, both top and head shift to it
     *  (All undone commands are discarded).
     */
    int csTop;

    /** @brief Applies new command to the current model.
     *  This function is called by GUI-facing functions.
     *  It applies new command to the model.
     *  That means it modifies the current state
     *  and it saves the command on top of the command stack.
     */
    void applyCommand(Command cmd);

    /** @brief Applies a command to a snapshot
     *  This is a low-level function, that only operates on a snapshot
     *  It does not change command stack in any way (compared to applyCommand)
     *  It is used to apply new commands generated by user
     *  and to do undo/redo operations.
     */
    void executeCommand(Snapshot &state, Command cmd);

    void addLinkExecute(Snapshot &state, LinkRepr newLink);
    void removeLinkExecute(Snapshot &state, std::string from, std::string to);
    void addClassExecute(Snapshot &state, double x=0, double y=0);
    void removeClassExecute(Snapshot &state, std::string name);
    void changeClassPropertiesExecute(Snapshot &state, Command cmd);

    void addSeqDiagramExecute(Snapshot &state);
    void addEntityExecute(Snapshot &state, std::string sdName /*, entita na smazani string*/);
    void removeEntityExecute(Snapshot &state, std::string sdName, std::string entityName);
    void addInteractionExecute(Snapshot &state, std::string sdName, std::string from, std::string to, Action::Type type);
    void removeInteractionExecute(Snapshot &state, std::string sdName, int index);
};

extern Model model;

#endif
