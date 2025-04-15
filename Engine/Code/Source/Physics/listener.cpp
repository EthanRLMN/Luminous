#include "Physics/listener.hpp"


virtual ValidateResult MyContactListener::ContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult) override
{
    std::cout << "Contact validate callback" << std::endl;

    return ValidateResult::AcceptAllContactsForThisBodyPair;
}

virtual void MyContactListener::OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
{
    std::cout << "A contact was added" << std::endl;
}

virtual void MyContactListener::OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
{
    std::cout << "A contact was persisted" << std::endl;
}

virtual void MyContactListener::OnContactRemoved(const SubShapeIDPair& inSubShapePair) override
{
    std::cout << "A contact was removed" << std::endl;
}


virtual void MyBodyActivationListener::OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) override
{
    std::cout << "A body got activated" << std::endl;
}

virtual void MyBodyActivationListener::OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) override
{
    std::cout << "A body went to sleep" << std::endl;
}
