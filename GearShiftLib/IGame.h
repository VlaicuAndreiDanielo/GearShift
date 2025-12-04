#pragma once
#include <vector>
#include <memory>
#include "IInputState.h"
#include "IGameObject.h"
#include "GameState.h"
#include "IFabric.h"

/// \brief Interfață de nivel înalt pentru logica unui joc.
///
/// Expune operații pentru bucla principală de update, managementul stării,
/// acces la obiecte, pânza de fundal și managerii de scor/fuel.
class IGame {
public:
    /// \brief Actualizează logica jocului pentru un frame.
    ///
    /// \param dt Timpul scurs de la ultimul frame (în secunde).
    /// \param input Starea curentă a input-ului (tastatură, mouse etc.).
    virtual void update(float dt, IInputState& input) = 0;

    /// \brief Pornește o rundă nouă de joc.
    virtual void startGame() = 0;

    /// \brief Pune jocul în pauză.
    virtual void pauseGame() = 0;

    /// \brief Reia jocul din pauză.
    virtual void resumeGame() = 0;

    /// \brief Încheie jocul curent și eliberează resursele rundei.
    virtual void endGame() = 0;

    /// \brief Obține obiectele de joc într-o formă adaptată pentru UI.
    ///
    /// \return Vector de pointeri la IGameObject pentru randare.
    virtual const std::vector<std::shared_ptr<IGameObject>>& getGameObjects() const = 0;

    /// \brief Obține pânza (cloth-ul) utilizată ca efect de fundal.
    virtual std::shared_ptr<IFabric> getFabric() = 0;

    /// \brief Obține pânza (cloth-ul) în variantă constantă.
    virtual const std::shared_ptr<IFabric> getFabric() const = 0;

    /// \brief Obține starea curentă a jocului.
    virtual GameState getState() const = 0;

    /// \brief Obține timpul total scurs în runda curentă.
    virtual float getTime() const = 0;

    /// \brief Aplică o forță în pânză pe baza input-ului de mouse.
    ///
    /// \param x Coordonata X a mouse-ului.
    /// \param y Coordonata Y a mouse-ului.
    /// \param pressed True dacă mouse-ul este apăsat.
    virtual void applyMouseForce(int x, int y, bool pressed) = 0;

    /// \brief Obține managerul de scor.
    virtual std::shared_ptr<class IScoreManager> getScoreManager() const = 0;

    /// \brief Obține managerul de fuel.
    virtual std::shared_ptr<class IFuelManager> getFuelManager() const = 0;

    /// \brief Destructor virtual necesar pentru folosirea prin pointer la interfață.
    virtual ~IGame() = default;
};
