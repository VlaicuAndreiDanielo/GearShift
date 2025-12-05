#pragma once

class ICommand {
public:
    virtual ~ICommand() = default;
    
    virtual bool canExecute() const { return true; }
    
    virtual void execute() = 0;

    virtual void undo() {}
    
    virtual bool canUndo() const { return false; }
    
    virtual const char* getDescription() const = 0;
};