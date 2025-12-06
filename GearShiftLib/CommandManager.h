#pragma once
#include "ICommand.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <stack>
#include <vector>

/// \brief Manager pentru comandă (Command pattern) cu suport de undo.
///
/// Reține un registru de comenzi numite și un stack de undo. Se ocupă de:
///  - înregistrarea comenzilor;
///  - executarea lor în siguranță (try/catch + logging);
///  - gestionarea stack-ului de undo până la o dimensiune maximă.
class CommandManager {
private:
    /// \brief Map de la numele comenzii la obiectul comandă.
    std::unordered_map<std::string, std::shared_ptr<ICommand>> commands;

    /// \brief Stack-ul de comenzi ce pot fi anulate (undo).
    std::stack<std::shared_ptr<ICommand>> undoStack;

    /// \brief Dimensiunea maximă a stack-ului de undo.
    static const size_t MAX_UNDO_STACK_SIZE = 50;

public:
    /// \brief Creează un CommandManager gol.
    CommandManager() = default;

    /// \brief Destructor - curăță comenzile și stack-ul de undo.
    ~CommandManager();

    /// \brief Înregistrează o comandă sub un nume dat.
    ///
    /// Dacă numele este deja folosit, comanda existentă va fi suprascrisă.
    ///
    /// \param name Numele comenzii (cheia din map).
    /// \param command Obiectul comandă.
    void registerCommand(const std::string& name, std::shared_ptr<ICommand> command);

    /// \brief Execută o comandă după numele înregistrat.
    ///
    /// \param name Numele comenzii.
    /// \return true dacă s-a găsit comanda și s-a încercat executarea ei, false altfel.
    bool executeCommand(const std::string& name);

    /// \brief Execută direct o comandă dată.
    ///
    /// Verifică \c canExecute(), apelează \c execute() și,
    /// dacă \c canUndo() este true, o introduce în stack-ul de undo.
    ///
    /// \param command Comanda de executat.
    void executeCommand(std::shared_ptr<ICommand> command);

    /// \brief Anulează ultima comandă care suportă undo.
    ///
    /// Apelează \c undo() pe comanda din vârful stack-ului și o scoate din stack.
    /// \return true dacă o comandă a fost anulată, false dacă stack-ul e gol.
    bool undo();

    /// \brief Verifică dacă există o comandă cu numele dat.
    bool hasCommand(const std::string& name) const;

    /// \brief Obține lista cu toate numele de comenzi înregistrate.
    std::vector<std::string> getCommandNames() const;

    /// \brief Șterge toate comenzile înregistrate.
    void clearCommands();

    /// \brief Golește stack-ul de undo.
    void clearUndoStack();

    /// \brief Obține dimensiunea curentă a stack-ului de undo.
    size_t getUndoStackSize() const;

    /// \brief Verifică dacă un obiect comandă este valid pentru înregistrare.
    ///
    /// Verifică dacă pointerul nu este null și dacă \c getDescription()
    /// întoarce un string non-empty.
    ///
    /// \param command Comanda de validat.
    /// \return true dacă este validă, false altfel.
    bool isValidCommand(std::shared_ptr<ICommand> command) const;
};
