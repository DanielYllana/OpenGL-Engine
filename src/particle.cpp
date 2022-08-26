#include <assert.h>
#include <cyclone/particle.h>

using namespace cyclone;


void Particle::integrate(real duration)
{
	// We don�t integrate things with infinite mass.
	if (inverseMass <= 0.0f) return;

	assert(duration > 0.0);

	// Update linear position. p' = p + v*t
	// dont use acceleration to simplify
	position.addScaledVector(velocity, duration);

	// Work out the acceleration from the force.
	// (We�ll add to this vector when we come to generate forces.)
	Vector3 resultingAcc = acceleration;

	// Update linear velocity from the acceleration. v' = v + a*t
	velocity.addScaledVector(resultingAcc, duration);

	// Impose drag.
	velocity *= real_pow(damping, duration);

	// Clear the forces.
	clearAccumulator();
}



void Particle::clearAccumulator()
{
	forceAccum.clear();
}

