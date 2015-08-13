#ifndef SPHPARTICLE_H
#define SPHPARTICLE_H

#include "Vec3.h"

struct SPHParticle
{
    Vec3d	pos;
    Vec3d	vel;
    Vec3d	accel;
    double	density;
    double	oneOverDensity;
    double	pressure;
	//boundary particle's parameter
	double	sigma;
	double	Psi;
};

#endif // SPHPARTICLE_H
