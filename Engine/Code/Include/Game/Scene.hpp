#pragma once

#include <string>
#include <rfl/json.hpp>



#include "Systems/Entity/Entity.hpp"


class Engine;


struct Vec3
{
    float x, y, z;

    Vec3() = default;
    Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    explicit Vec3(const Maths::Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    explicit operator Maths::Vector3() const { return Maths::Vector3{x, y, z}; }

};


struct Vec2
{
    float x, y;

    Vec2() = default;
    Vec2(const float x, const float y, const float z) :
        x(x), y(y) {}
    explicit Vec2(const Maths::Vector2& v) :
        x(v.x), y(v.y) {}
    explicit operator Maths::Vector2() const { return Maths::Vector2{ x, y}; }
};


struct Quat
{
    float x, y, z, w;

    Quat() = default;
    Quat(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    explicit Quat(const Maths::Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
    explicit operator Maths::Quaternion() const { return Maths::Quaternion{x, y, z, w}; }
};


struct Vec3Helper
{
    float x, y, z;

    static Vec3Helper from_class(const Vec3& v) noexcept { return Vec3Helper{v.x, v.y, v.z}; }
    [[nodiscard]] Vec3 to_class() const { return Vec3{x, y, z}; }
};


struct QuatHelper {
    float x, y, z, w;

    static QuatHelper from_class(const Quat& q) noexcept { return QuatHelper{q.x, q.y, q.z, q.w}; }

    [[nodiscard]] Quat to_class() const { return Quat{x, y, z, w}; }
};


template <class ReaderType, class WriterType, class ProcessorsType>
struct rfl::parsing::Parser<ReaderType, WriterType, Vec3, ProcessorsType> : CustomParser<ReaderType, WriterType, ProcessorsType, Vec3, Vec3Helper> {};


template <class ReaderType, class WriterType, class ProcessorsType>
struct rfl::parsing::Parser<ReaderType, WriterType, Quat, ProcessorsType> : CustomParser<ReaderType, WriterType, ProcessorsType, Quat, QuatHelper> {};


struct TransformComponentData
{
    Vec3 globalPosition;
    Quat globalRotation;
    Vec3 globalScale;

    Vec3 localPosition;
    Quat localRotation;
    Vec3 localScale;

    template <typename Archive>
    void reflect(Archive& ar) { ar(globalPosition, globalRotation, globalScale, localPosition, localRotation, localScale); }
};


struct ModelComponentData
{
    std::string texturePath;
    std::string modelPath;
};


struct LightComponentData
{
    Vec3 position;
    Vec3 direction;
    Vec3 color;

    LightType type;
    float intensity;
    float ambientStrength;
    float specularStrength;

    template <typename Archive>
    void reflect(Archive& ar) { ar(position, direction, color, type); }
};


struct CameraComponentData
{
    bool isActive;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    float fieldOfView;

    Vec3 eye;
    Vec3 center;
};


struct RigidbodyComponentData
{
    JPH::EActivation isActive;
    std::weak_ptr<Entity>& entity;
    ColliderType type;
    JPH::uint8 layer;
    Vec3 boxSize;
    Vec2 capsuleSize;
    float sphereSize;
};

using SerializedComponent = rfl::Variant<
    TransformComponentData,
    ModelComponentData,
    LightComponentData,
    CameraComponentData,
    RigidbodyComponentData>;


template <typename Archive>
void reflect(Archive& ar, SerializedComponent& component)
{
    rfl::visit([&](auto&& comp) { ar(comp); }, component);
}


struct EntityData
{
    std::string entityName;
    uint16_t entityUUID;
    bool isActive;

    std::string componentType;
    std::vector<SerializedComponent> components;

    template <typename Archive>
    void reflect(Archive& ar) { ar(entityName, entityUUID, isActive, components); }
};


struct SceneData
{
    std::unordered_map<std::string, EntityData> Entities;

    template <typename Archive>
    void reflect(Archive& ar) { ar(Entities); }
};



class Scene
{
public:
    Scene()= default;
    ~Scene()= default;

    void RegisterScene(EntityManager& a_entityManager);

    void LoadScene(std::string filename, const EntityManager& a_entityManager);
    void SaveScene(const std::string& filepath, const EntityManager& a_entityManager);

    static bool CheckIfFileDetected(const std::string& a_filename);
};