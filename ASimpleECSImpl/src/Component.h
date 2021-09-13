#pragma once

struct ComponentBase
{
    template <typename T>
    static ComponentType GetComponentID()
    {
        static ComponentType id = ComponentBase::CompIdRefCount++;
        
        return id;
    }

    ComponentType CompId = 0;
    virtual ~ComponentBase() = default;

private:
    static ComponentType CompIdRefCount;
};

struct TagComponent : public ComponentBase
{
    std::string Tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag)
        : Tag(tag) {}
};

struct HealthComponent : public ComponentBase
{
    int CurrentHealth;
    int MaxHealth;

    HealthComponent(int max, int current)
        : MaxHealth(max), CurrentHealth(current) {}
};

struct TransformComponent : public ComponentBase
{
    mat4 Transform{ 1.0f };

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const mat4& transform)
        : Transform(transform) {}

    operator mat4& () { return Transform; }
    operator const mat4& () const { return Transform; }
};

struct SpriteRendererComponent : public ComponentBase
{
    vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

    SpriteRendererComponent() = default;
    SpriteRendererComponent(const SpriteRendererComponent&) = default;
    SpriteRendererComponent(const vec4& color)
        : Color(color) {}
};

struct CameraComponent : public ComponentBase
{
    bool Primary = true;
    bool FixedAspectRatio = false;
    float PanSpeed = 1.0f;
    
    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
    CameraComponent(float speed)
        : PanSpeed(speed) {}
};