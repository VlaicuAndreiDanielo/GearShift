#pragma once

/// \brief Interfață de bază pentru toate comenzile (Command pattern).
///
/// Comenzile pot fi executate, opțional anulate (undo), și furnizează o
/// descriere textuală pentru logging și debugging.
class ICommand {
public:
    /// \brief Destructor virtual necesar pentru folosirea prin pointer la interfață.
    virtual ~ICommand() = default;

    /// \brief Verifică dacă comanda poate fi executată în starea curentă.
    ///
    /// Implementările pot valida contextul (ex. starea jocului). Implicit true.
    /// \return true dacă poate fi executată, false altfel.
    virtual bool canExecute() const { return true; }

    /// \brief Execută efectiv comanda.
    ///
    /// Implementările concrete trebuie să definească această metodă.
    virtual void execute() = 0;

    /// \brief Anulează efectul comenzii, dacă este suportat.
    ///
    /// Implementarea implicită nu face nimic.
    virtual void undo() {}

    /// \brief Indică dacă această comandă suportă operația de undo.
    ///
    /// Implicit false. Dacă o comandă suprascrie \c undo(), ar trebui să
    /// suprascrie și \c canUndo() pentru a întoarce true.
    virtual bool canUndo() const { return false; }

    /// \brief Descriere textuală a comenzii.
    ///
    /// Folosită pentru logging, debugging și UI (de ex. meniuri de debug).
    virtual const char* getDescription() const = 0;
};
