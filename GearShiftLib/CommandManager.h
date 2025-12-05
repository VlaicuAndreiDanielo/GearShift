#pragma once
#include "ICommand.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <stack>
#include <vector>

class CommandManager {
private:
    // Map of command names to command objects
    std::unordered_map<std::string, std::shared_ptr<ICommand>> commands;
    
    // Stack for undo functionality
    std::stack<std::shared_ptr<ICommand>> undoStack;
    
    // Maximum number of commands to keep in undo stack
    static const size_t MAX_UNDO_STACK_SIZE = 50;
    
public:
    CommandManager() = default;
    ~CommandManager();
    
    void registerCommand(const std::string& name, std::shared_ptr<ICommand> command);
    
    bool executeCommand(const std::string& name);
    
    void executeCommand(std::shared_ptr<ICommand> command);
    
    bool undo();
    
    bool hasCommand(const std::string& name) const;
    
    std::vector<std::string> getCommandNames() const;
    
    void clearCommands();
    
    void clearUndoStack();
    
    size_t getUndoStackSize() const;
    
    bool isValidCommand(std::shared_ptr<ICommand> command) const;
};