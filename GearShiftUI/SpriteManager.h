#pragma once
#include <memory>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_map>

/// \brief Manager simplu de texturi cu caching.
///
/// Încarcă texturi de pe disc la prima cerere și le reține într-un cache
/// (map de la path la SDL_Texture*). Oferă și metode helper pentru desen.
class SpriteManager
{
public:
    /// \brief Desenează o textură pe întregul dreptunghi dat.
    ///
    /// \param rect Dreptunghiul destinație în coordonate ecran.
    /// \param texture Textura de desenat (poate fi nullptr).
    void drawTextureOverRect(SDL_Rect rect, SDL_Texture* texture);

    /// \brief Desenează o textură rotită peste dreptunghiul dat.
    ///
    /// \param rect Dreptunghiul destinație în coordonate ecran.
    /// \param texture Textura de desenat (poate fi nullptr).
    /// \param angleRadians Unghiul de rotație în radiani în jurul centrului rect-ului.
    void drawTextureOverRect(const SDL_Rect& rect, SDL_Texture* texture, double angleRadians);

    /// \brief Obține (și cache-uiește) textura pentru un path dat.
    ///
    /// Dacă textura nu este încă încărcată, o încarcă prin IMG_LoadTexture,
    /// o introduce în cache și apoi o întoarce.
    ///
    /// \param path Calea către fișierul imagine.
    /// \return Pointer la SDL_Texture sau nullptr în caz de eroare.
    SDL_Texture* getTexture(const std::string& path);

    /// \brief Creează un SpriteManager pentru un anumit SDL_Renderer.
    /// \param renderer Renderer-ul folosit la încărcare și desen.
    SpriteManager(SDL_Renderer* renderer);

    /// \brief Destructor – distruge toate texturile din cache.
    ~SpriteManager();
private:
    /// \brief Cache de texturi indexate după path.
    std::unordered_map<std::string, SDL_Texture*> textureCache;
    /// \brief Renderer-ul asociat, folosit pentru LoadTexture și RenderCopy.
    SDL_Renderer* renderer;
};
