/** @file tool.h
 *  @brief Tools that can be selected.
 *
 *  @author Ondřej Mach (xmacho12)
 *  @author Rostislav Lán (xlanro00)
 */

#ifndef TOOL_H
#define TOOL_H

enum Tool{
    // class diagram tools
    TOOL_MOUSE,
    TOOL_ASSOCIATE,
    TOOL_AGGREGATE,
    TOOL_COMPOSE,
    TOOL_GENERALIZE,
    TOOL_CLASS,
    TOOL_DELETE,
    // seq. diagram tools
    TOOL_OBJECT,
    TOOL_ACTIVATE,
    TOOL_DEACTIVATE,
    TOOL_CREATE_MESSAGE,
    TOOL_ASYNC_MESSAGE,
    TOOL_SYNC_MESSAGE,
    TOOL_RETURN_MESSAGE,
    TOOL_DESTROY_MESSAGE,
};

#endif // TOOL_H
