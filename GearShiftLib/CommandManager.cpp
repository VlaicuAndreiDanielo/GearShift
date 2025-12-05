#include "CommandManager.h"
#include <SDL2/SDL.h>

CommandManager::~CommandManager() {
    SDL_Log("CommandManager: Destructor - clearing resources");
    clearCommands();
    clearUndoStack();
}

void CommandManager::registerCommand(const std::string& name, std::shared_ptr<ICommand> command) {
    if (name.empty()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Cannot register command with empty name");
        return;
    }
    
    if (!isValidCommand(command)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Cannot register invalid command '%s'", name.c_str());
        return;
    }
    
    if (commands.find(name) != commands.end()) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Overwriting existing command '%s'", name.c_str());
    }
    
    commands[name] = command;
    SDL_Log("CommandManager: Registered command '%s' - %s", name.c_str(), command->getDescription());
}

bool CommandManager::executeCommand(const std::string& name) {
    auto it = commands.find(name);
    if (it == commands.end()) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Command '%s' not found", name.c_str());
        return false;
    }
    
    executeCommand(it->second);
    return true;
}

void CommandManager::executeCommand(std::shared_ptr<ICommand> command) {
    if (!command) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Attempting to execute null command");
        return;
    }
    
    // Check if command can be executed
    if (!command->canExecute()) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Command cannot be executed - %s", command->getDescription());
        return;
    }
    
    try {
        SDL_Log("CommandManager: Executing command - %s", command->getDescription());
        command->execute();
        
        // Add to undo stack if command supports undo
        if (command->canUndo()) {
            undoStack.push(command);
            
            // Limit undo stack size
            while (undoStack.size() > MAX_UNDO_STACK_SIZE) {
                undoStack.pop();
            }
            SDL_Log("CommandManager: Command added to undo stack (stack size: %zu)", undoStack.size());
        }
        
        SDL_Log("CommandManager: Successfully executed command - %s", command->getDescription());
    }
    catch (const std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Exception executing command - %s: %s", 
                    command->getDescription(), e.what());
    }
    catch (...) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Unknown exception executing command - %s", 
                    command->getDescription());
    }
}

bool CommandManager::undo() {
    if (undoStack.empty()) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: No commands to undo");
        return false;
    }
    
    auto command = undoStack.top();
    undoStack.pop();
    
    try {
        command->undo();
        SDL_Log("CommandManager: Undid command - %s", command->getDescription());
        return true;
    }
    catch (const std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Exception undoing command - %s: %s", 
                    command->getDescription(), e.what());
        return false;
    }
}

bool CommandManager::hasCommand(const std::string& name) const {
    return commands.find(name) != commands.end();
}

std::vector<std::string> CommandManager::getCommandNames() const {
    std::vector<std::string> names;
    names.reserve(commands.size());
    
    for (const auto& pair : commands) {
        names.push_back(pair.first);
    }
    
    return names;
}

void CommandManager::clearCommands() {
    commands.clear();
    SDL_Log("CommandManager: Cleared all commands");
}

void CommandManager::clearUndoStack() {
    while (!undoStack.empty()) {
        undoStack.pop();
    }
    SDL_Log("CommandManager: Cleared undo stack");
}

size_t CommandManager::getUndoStackSize() const {
    return undoStack.size();
}

bool CommandManager::isValidCommand(std::shared_ptr<ICommand> command) const {
    if (!command) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Command is null");
        return false;
    }
    
    if (!command->getDescription() || strlen(command->getDescription()) == 0) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "CommandManager: Command has empty description");
        return false;
    }
    
    return true;
}