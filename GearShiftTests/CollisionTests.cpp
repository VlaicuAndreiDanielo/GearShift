/**
 * \file CollisionTests.cpp
 * \brief Unit tests pentru CollisionManager și BoxCollider.
 *
 * Verifică:
 *  - crearea managerului și a colliderelor;
 *  - detecția de overlap și lipsa coliziunii;
 *  - rezolvarea coliziunilor pentru obiecte mobile / fixe / trigger;
 *  - ignorarea obiectelor inactive.
 */

#include <gtest/gtest.h>
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "GameObject.h"

 // manager
TEST(CollisionTest, CreateManager) {
    auto mgr = std::make_shared<CollisionManager>();
    ASSERT_NE(mgr, nullptr);
}

TEST(CollisionTest, AddCollider) {
    auto mgr = std::make_shared<CollisionManager>();
    auto obj = std::make_shared<GameObject>(0, 0, 50, 50, true);
    auto col = mgr->addCollider<BoxCollider>(obj, 50.0f, 50.0f);
    ASSERT_NE(col, nullptr);
}

// detection
TEST(CollisionTest, DetectOverlap) {
    auto mgr = std::make_shared<CollisionManager>();
    auto obj1 = std::make_shared<GameObject>(0, 0, 50, 50, true);
    auto obj2 = std::make_shared<GameObject>(25, 0, 50, 50, true);

    auto col1 = mgr->addCollider<BoxCollider>(obj1, 50.0f, 50.0f);
    auto col2 = mgr->addCollider<BoxCollider>(obj2, 50.0f, 50.0f);

    auto collision = col1->checkCollisionWith(*col2);
    EXPECT_TRUE(collision.has_value());
}

TEST(CollisionTest, NoOverlap) {
    auto mgr = std::make_shared<CollisionManager>();
    auto obj1 = std::make_shared<GameObject>(0, 0, 50, 50, true);
    auto obj2 = std::make_shared<GameObject>(200, 0, 50, 50, true);

    auto col1 = mgr->addCollider<BoxCollider>(obj1, 50.0f, 50.0f);
    auto col2 = mgr->addCollider<BoxCollider>(obj2, 50.0f, 50.0f);

    auto collision = col1->checkCollisionWith(*col2);
    EXPECT_FALSE(collision.has_value());
}

// resolution
TEST(CollisionTest, ResolveSeparates) {
    auto mgr = std::make_shared<CollisionManager>();
    auto obj1 = std::make_shared<GameObject>(0, 0, 50, 50, true);
    auto obj2 = std::make_shared<GameObject>(25, 0, 50, 50, true);

    mgr->addCollider<BoxCollider>(obj1, 50.0f, 50.0f);
    mgr->addCollider<BoxCollider>(obj2, 50.0f, 50.0f);

    Vec2 pos1 = obj1->getWorldTransform().getPos();
    Vec2 pos2 = obj2->getWorldTransform().getPos();

    mgr->update();

    bool moved = (obj1->getWorldTransform().getX() != pos1.x ||
        obj2->getWorldTransform().getX() != pos2.x);
    EXPECT_TRUE(moved);
}

TEST(CollisionTest, FixedNoResolve) {
    auto mgr = std::make_shared<CollisionManager>();
    auto obj1 = std::make_shared<GameObject>(0, 0, 50, 50, true);
    auto obj2 = std::make_shared<GameObject>(25, 0, 50, 50, true);

    obj1->getWorldTransform().setFixed(true);
    obj2->getWorldTransform().setFixed(true);

    mgr->addCollider<BoxCollider>(obj1, 50.0f, 50.0f);
    mgr->addCollider<BoxCollider>(obj2, 50.0f, 50.0f);

    Vec2 pos1 = obj1->getWorldTransform().getPos();
    Vec2 pos2 = obj2->getWorldTransform().getPos();

    mgr->update();

    EXPECT_FLOAT_EQ(obj1->getWorldTransform().getX(), pos1.x);
    EXPECT_FLOAT_EQ(obj2->getWorldTransform().getX(), pos2.x);
}

// trigger
TEST(CollisionTest, TriggerNoResolve) {
    auto mgr = std::make_shared<CollisionManager>();
    auto obj1 = std::make_shared<GameObject>(0, 0, 50, 50, true);
    auto obj2 = std::make_shared<GameObject>(25, 0, 50, 50, true);

    auto col1 = mgr->addCollider<BoxCollider>(obj1, 50.0f, 50.0f);
    mgr->addCollider<BoxCollider>(obj2, 50.0f, 50.0f);

    col1->setTrigger(true);

    Vec2 pos1 = obj1->getWorldTransform().getPos();
    Vec2 pos2 = obj2->getWorldTransform().getPos();

    mgr->update();

    EXPECT_FLOAT_EQ(obj1->getWorldTransform().getX(), pos1.x);
    EXPECT_FLOAT_EQ(obj2->getWorldTransform().getX(), pos2.x);
}

// inactive
TEST(CollisionTest, InactiveNoCollide) {
    auto mgr = std::make_shared<CollisionManager>();
    auto obj1 = std::make_shared<GameObject>(0, 0, 50, 50, false);
    auto obj2 = std::make_shared<GameObject>(25, 0, 50, 50, true);

    mgr->addCollider<BoxCollider>(obj1, 50.0f, 50.0f);
    mgr->addCollider<BoxCollider>(obj2, 50.0f, 50.0f);

    Vec2 pos2 = obj2->getWorldTransform().getPos();
    mgr->update();

    EXPECT_FLOAT_EQ(obj2->getWorldTransform().getX(), pos2.x);
}
