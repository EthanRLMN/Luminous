#pragma once

#include "Jolt/Jolt.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/Body/Body.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Body/BodyID.h"
#include "Jolt/Physics/SoftBody/SoftBodyCreationSettings.h"
#include "Logger.hpp"


class RigidBody
{
public:
    RigidBody() = default;
    ~RigidBody() = default;

    explicit RigidBody(JPH::Body* a_rigidBody) : m_rigidBody(a_rigidBody) {}

    inline void GetSubmergedVolume(const JPH::RVec3Arg a_inSurfacePosition, const JPH::Vec3Arg a_inSurfaceNormal, float& a_outTotalVolume, float& a_outSubmergedVolume, JPH::Vec3& a_outRelativeCenterOfBuoyancy) const { return m_rigidBody->GetSubmergedVolume(a_inSurfacePosition, a_inSurfaceNormal, a_outTotalVolume, a_outSubmergedVolume, a_outRelativeCenterOfBuoyancy); }
    [[nodiscard]] inline float GetFriction() const { return m_rigidBody->GetFriction(); }
    [[nodiscard]] inline float GetRestitution() const { return m_rigidBody->GetRestitution(); }
    [[nodiscard]] inline bool IsRigidBody() const { return m_rigidBody->IsRigidBody(); }
    [[nodiscard]] inline bool IsSoftBody() const { return m_rigidBody->IsSoftBody(); }
    [[nodiscard]] inline bool IsActive() const { return m_rigidBody->IsActive(); }
    [[nodiscard]] inline bool IsStatic() const { return m_rigidBody->IsStatic(); }
    [[nodiscard]] inline bool IsSensor() const { return m_rigidBody->IsSensor(); }
    [[nodiscard]] inline bool IsKinematic() const { return m_rigidBody->IsKinematic(); }
    [[nodiscard]] inline bool IsDynamic() const { return m_rigidBody->IsDynamic(); }
    [[nodiscard]] inline bool CanBeKinematicOrDynamic() const { return m_rigidBody->CanBeKinematicOrDynamic(); }
    [[nodiscard]] inline bool GetAllowSleeping() const { return m_rigidBody->GetAllowSleeping(); }
    [[nodiscard]] inline bool GetCollideKinematicVsNonDynamic() const { return m_rigidBody->GetCollideKinematicVsNonDynamic(); }
    [[nodiscard]] inline bool GetUseManifoldReduction() const { return m_rigidBody->GetUseManifoldReduction(); }
    [[nodiscard]] inline bool GetUseManifoldReductionWithBody(const JPH::Body& a_inBody2) const { return m_rigidBody->GetUseManifoldReductionWithBody(a_inBody2); }
    [[nodiscard]] inline bool GetApplyGyroscopicForce() const { return m_rigidBody->GetApplyGyroscopicForce(); }
    [[nodiscard]] inline bool GetEnhancedInternalEdgeRemoval() const { return m_rigidBody->GetEnhancedInternalEdgeRemoval(); }
    [[nodiscard]] inline bool GetEnhancedInternalEdgeRemovalWithBody(const JPH::Body& a_inBody2) const { return m_rigidBody->GetEnhancedInternalEdgeRemovalWithBody(a_inBody2); }
    [[nodiscard]] inline bool IsInBroadPhase() const { return m_rigidBody->IsInBroadPhase(); }
    [[nodiscard]] inline bool IsCollisionCacheInvalid() const { return m_rigidBody->IsCollisionCacheInvalid(); }
    [[nodiscard]] inline JPH::Body* GetRigidBody() const { return m_rigidBody; }
    [[nodiscard]] inline JPH::BodyID GetRigidBodyID() const { return m_rigidBody->GetID(); }
    [[nodiscard]] inline JPH::EBodyType GetRigidBodyType() const { return m_rigidBody->GetBodyType(); }
    [[nodiscard]] inline JPH::EMotionType GetMotionType() const { return m_rigidBody->GetMotionType(); }
    [[nodiscard]] inline JPH::RVec3 GetPosition() const { return m_rigidBody->GetPosition(); }
    inline JPH::Quat GetRotation() const { return m_rigidBody->GetRotation(); }
    [[nodiscard]] inline JPH::RMat44 GetWorldTransform() const { return m_rigidBody->GetWorldTransform(); }
    [[nodiscard]] inline JPH::RVec3 GetCenterOfMassPosition() const { return m_rigidBody->GetCenterOfMassPosition(); }
    [[nodiscard]] inline JPH::RMat44 GetCenterOfMassTransform() const { return m_rigidBody->GetCenterOfMassTransform(); }
    [[nodiscard]] inline JPH::RMat44 GetInverseCenterOfMassTransform() const { return m_rigidBody->GetInverseCenterOfMassTransform(); }
    inline JPH::MotionProperties* GetMotionProperties() { return m_rigidBody->GetMotionProperties(); }
    inline JPH::MotionProperties* GetMotionPropertiesUnchecked() { return m_rigidBody->GetMotionPropertiesUnchecked(); }
    [[nodiscard]] inline JPH::uint64 GetUserData() const { return m_rigidBody->GetUserData(); }
    inline JPH::Vec3 GetWorldSpaceSurfaceNormal(const JPH::SubShapeID& a_inSubShapeID, const JPH::RVec3Arg a_inPosition) const { return m_rigidBody->GetWorldSpaceSurfaceNormal(a_inSubShapeID, a_inPosition); }
    [[nodiscard]] inline JPH::TransformedShape GetTransformedShape() const { return m_rigidBody->GetTransformedShape(); }
    [[nodiscard]] inline JPH::BodyCreationSettings GetBodyCreationSettings() const { return m_rigidBody->GetBodyCreationSettings(); }
    [[nodiscard]] inline JPH::SoftBodyCreationSettings GetSoftBodyCreationSettings() const { return m_rigidBody->GetSoftBodyCreationSettings(); }
    [[nodiscard]] inline JPH::BroadPhaseLayer GetBroadPhaseLayer() const { return m_rigidBody->GetBroadPhaseLayer(); }
    [[nodiscard]] inline JPH::ObjectLayer GetObjectLayer() const { return m_rigidBody->GetObjectLayer(); }
    [[nodiscard]] inline JPH::CollisionGroup& GetCollisionGroup() const { return m_rigidBody->GetCollisionGroup(); }
    inline JPH::CollisionGroup GetCollisionGroup() { return m_rigidBody->GetCollisionGroup(); }
    inline JPH::Vec3 GetAccumulatedForce() const { return m_rigidBody->GetAccumulatedForce(); }
    inline JPH::Vec3 GetAccumulatedTorque() const { return m_rigidBody->GetAccumulatedTorque(); }
    inline JPH::Mat44 GetInverseInertia() const { return m_rigidBody->GetInverseInertia(); };
    inline JPH::Vec3 GetLinearVelocity() const { return m_rigidBody->GetLinearVelocity(); }
    inline JPH::Vec3 GetAngularVelocity() const { return m_rigidBody->GetAngularVelocity(); }
    inline JPH::Vec3 GetPointVelocityCOM(JPH::Vec3Arg a_inPointRelativeToCOM) const { return m_rigidBody->GetPointVelocityCOM(a_inPointRelativeToCOM); }
    inline JPH::Vec3 GetPointVelocity(JPH::RVec3Arg a_inPoint) const { return m_rigidBody->GetPointVelocity(a_inPoint); }
    [[nodiscard]] inline const JPH::Shape* GetShape() const { return m_rigidBody->GetShape(); }
    [[nodiscard]] inline const JPH::AABox& GetWorldSpaceBounds() const { return m_rigidBody->GetWorldSpaceBounds(); }
    [[nodiscard]] inline const JPH::MotionProperties* GetMotionPropertiesUnchecked() const { return m_rigidBody->GetMotionPropertiesUnchecked(); }
    [[nodiscard]] inline const JPH::MotionProperties* GetMotionProperties() const { return m_rigidBody->GetMotionProperties(); }
    inline static JPH::Body& GetFixedToWorld() { return s_fixedToWorld; }

    inline void SetEnhancedInternalEdgeRemoval(const bool a_inApply) const { return m_rigidBody->SetEnhancedInternalEdgeRemoval(a_inApply); }
    inline void SetApplyGyroscopicForce(const bool a_inApply) const { m_rigidBody->SetApplyGyroscopicForce(a_inApply); }
    inline void SetUseManifoldReduction(const bool a_inUseReduction) const { m_rigidBody->SetUseManifoldReduction(a_inUseReduction); }
    inline void SetCollideKinematicVsNonDynamic(const bool a_inCollide) const { m_rigidBody->SetCollideKinematicVsNonDynamic(a_inCollide); }
    inline void SetIsSensor(const bool a_inIsSensor) { m_rigidBody->SetIsSensor(a_inIsSensor); }
    inline void SetRigidBody(JPH::Body* a_rigidBody) { m_rigidBody = a_rigidBody; }
    inline void SetIsSensor(const bool a_inIsSensor) const { m_rigidBody->SetIsSensor(a_inIsSensor); }
    inline void SetMotionType(const JPH::EMotionType a_inMotionType) const { m_rigidBody->SetMotionType(a_inMotionType); }
    inline void SetCollisionGroup(const JPH::CollisionGroup& a_inCollisionGroup) const { m_rigidBody->SetCollisionGroup(a_inCollisionGroup); }
    inline void SetAllowSleeping(const bool a_inAllow) const { m_rigidBody->SetAllowSleeping(a_inAllow); };
    inline void ResetSleepTimer() const { m_rigidBody->ResetSleepTimer(); }
    inline void SetFriction(const float a_inFriction) const { m_rigidBody->SetFriction(a_inFriction); }
    inline void SetRestitution(const float a_inRestitution) const { m_rigidBody->SetRestitution(a_inRestitution); }
    inline void SetLinearVelocity(JPH::Vec3Arg a_inLinearVelocity) const { m_rigidBody->SetLinearVelocity(a_inLinearVelocity); }
    inline void SetLinearVelocityClamped(JPH::Vec3Arg a_inLinearVelocity) const { m_rigidBody->SetLinearVelocityClamped(a_inLinearVelocity); }
    inline void SetAngularVelocity(JPH::Vec3Arg a_inAngularVelocity) const { m_rigidBody->SetAngularVelocity(a_inAngularVelocity); }
    inline void SetAngularVelocityClamped(JPH::Vec3Arg a_inAngularVelocity) const { m_rigidBody->SetAngularVelocityClamped(a_inAngularVelocity); }
    inline void AddForce(const JPH::Vec3Arg a_inForce) const { m_rigidBody->AddForce(a_inForce); }
    inline void AddForce(const JPH::Vec3Arg a_inForce, const JPH::RVec3Arg a_inPosition) const { m_rigidBody->AddForce(a_inForce, a_inPosition); }
    inline void AddTorque(const JPH::Vec3Arg a_inTorque) const { m_rigidBody->AddTorque(a_inTorque); }
    inline void ResetForce() const { m_rigidBody->ResetForce(); }
    inline void ResetTorque() const { m_rigidBody->ResetTorque(); }
    inline void ResetMotion() const { m_rigidBody->ResetMotion(); }
    inline void AddImpulse(const JPH::Vec3Arg a_inImpulse) const { m_rigidBody->AddImpulse(a_inImpulse); }
    inline void AddImpulse(const JPH::Vec3Arg a_inImpulse, const JPH::RVec3Arg a_inPosition) const { m_rigidBody->AddImpulse(a_inImpulse, a_inPosition); }
    inline void AddAngularImpulse(const JPH::Vec3Arg a_inImpulse) const { m_rigidBody->AddAngularImpulse(a_inImpulse); }
    inline void MoveKinematic(const JPH::RVec3Arg a_inTargetPosition, const JPH::QuatArg a_inTargetRotation, const float a_inDeltaTime) const { m_rigidBody->MoveKinematic(a_inTargetPosition, a_inTargetRotation, a_inDeltaTime); }
    [[nodiscard]] inline bool ApplyBuoyancyImpulse(const JPH::RVec3Arg a_inSurfacePosition, const JPH::Vec3Arg a_inSurfaceNormal, const float a_inBuoyancy, const float a_inLinearDrag, const float a_inAngularDrag, const JPH::Vec3Arg a_inFluidVelocity, const JPH::Vec3Arg a_inGravity, const float a_inDeltaTime) const { return m_rigidBody->ApplyBuoyancyImpulse(a_inSurfacePosition, a_inSurfaceNormal, a_inBuoyancy, a_inLinearDrag, a_inAngularDrag, a_inFluidVelocity, a_inGravity, a_inDeltaTime); }
    [[nodiscard]] inline bool ApplyBuoyancyImpulse(const float a_inTotalVolume, const float a_inSubmergedVolume, const JPH::Vec3Arg a_inRelativeCenterOfBuoyancy, const float a_inBuoyancy, const float a_inLinearDrag, const float a_inAngularDrag, const JPH::Vec3Arg a_inFluidVelocity, const JPH::Vec3Arg a_inGravity, const float a_inDeltaTime) const { return m_rigidBody->ApplyBuoyancyImpulse(a_inTotalVolume, a_inSubmergedVolume, a_inRelativeCenterOfBuoyancy, a_inBuoyancy, a_inLinearDrag, a_inAngularDrag, a_inFluidVelocity, a_inGravity, a_inDeltaTime); }
    inline void ValidateCachedBounds() const { m_rigidBody->ValidateCachedBounds(); }
    inline void SetUserData(const JPH::uint64 a_inUserData) const { m_rigidBody->SetUserData(a_inUserData); }


private:
    JPH::Body* m_rigidBody { nullptr };
    static JPH::Body s_fixedToWorld;
};
