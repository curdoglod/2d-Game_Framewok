#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "sprite.h"
#include "engine.h"
#include "Utils.h"


class Component; 
class Image; 
class SceneManager; 

class Object {
public:
    bool Crossing(Object* obj, const float& x_range, const float& y_range);
    bool Crossing(Object* obj);

    Vector2 GetPosition() const;
    Vector2 GetSize() const ;

    void InitSize(Image* img);
    void InitSize();

    void SetPosition(const Vector2& vec2);
    void SetPositionOnPlatform(const Vector2 & vec2);
    void MoveY(const float& pos_y);
    void MoveX(const float& pos_x);

    void SetLayer(int layer);
    int GetLayer() const;
    void AddComponent(Component* component);
    Component* GetComponent(const std::type_info& ti) const;

    template<typename T>
    void RemoveComponent();
  
    void update(float deltaTime);
    SceneManager* GetScene() const;
    SDL_Renderer* GetRenderer() const;
    void UpdateEvents(SDL_Event& event);
    void SetActive(bool status);
    template <typename T>
    T* GetComponent() const {
        Component* comp = this->GetComponent(typeid(T));
        return dynamic_cast<T*>(comp);
    }
  
    friend class Engine; 
    friend class SceneManager;
private:
    virtual ~Object();
    Object(SceneManager* _game, SDL_Renderer* renderer_);
    SDL_Renderer* renderer;
    SceneManager* currentScene;
    std::vector<Component*> components;
    Vector2 position;
    Vector2 size;
    int layer;
    bool active; 
    float deltatime;
};

#endif // OBJECT_H
