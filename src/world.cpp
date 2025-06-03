#include "world.h"
#include "body.h"
#include "gravitation.h"
#include "raymath.h"
#include "gui.h"
#include "collision.h"
#include "contact.h"

float World::bodyGScale{ 1.0f };
float World::bodyDamping{ 0.3f };
float World::bodyMass{ 1.0f };
int World::bodyType{ 1 };


World::~World()
{
}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
    World::gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color)
{
    Body* body = new Body(type, position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping)
{
    Spring* spring = new Spring(bodyA, bodyB, restLength, stiffness, damping);
    m_springs.push_back(spring);
    return spring;
}

void World::Step(float timestep)
{
    if (!simulate) return;

    if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);

    for (auto spring : m_springs)
    {
        spring->ApplyForce(springStiffnessMultiplier);
    }

    for (auto body : m_bodies)
    {
        body->Step(timestep);
        body->ClearForce();
    }

    m_contacts.clear();
    CreateContacts(m_bodies, m_contacts);
    SeparateContacts(m_contacts);
}

void World::Draw(const Scene& scene)
{
    for (auto body : m_bodies)
    {
        body->Draw(scene);
    }
}

void World::DestroyAll()
{
    for (auto body : m_bodies)
    {
        delete body;
    }
}

void World::ApplyGravitation(bodies_t& bodies, float strength)
{
    // Loop through each body in the list (call it bodyA)
    for (int i = 0; i < bodies.size(); i++)
    {
        // Loop through each body after bodyA (call it bodyB)
        for (int j = i + 1; j < bodies.size(); j++)
        {
            // STEP 1: Find the direction vector from bodyB to bodyA
            Vector2 direction = bodies[i]->position - bodies[j]->position;

            // STEP 2: Get the distance between the two bodies
            float distance = Vector2Length(direction);

            // STEP 3: Clamp the distance to a minimum value to avoid extreme forces
            distance = std::max(distance, 1.0f);

            // STEP 4: Calculate gravitational force magnitude using:
            float forceMagnitude = (bodies[i]->mass * bodies[j]->mass / (distance * distance)) * strength;

            // STEP 5: Normalize the direction vector and scale it by the force magnitude
            Vector2 forceVector = Vector2Normalize(direction) * forceMagnitude;

            // STEP 6: Apply the force to both bodies (equal and opposite)
            bodies[i]->ApplyForce(forceVector * -1);
            bodies[j]->ApplyForce(forceVector);
        }
    }
}
