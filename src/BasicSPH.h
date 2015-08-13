#ifndef BASICSPH_H
#define BASICSPH_H

#include "SPHParticle.h"
#include "Vec3.h"

#include <vector>

class BasicSPH
{
public:
    BasicSPH(Vec3d volumeMin, Vec3d volumeMax, double mass, double restDensity, double h, double k, double dt);
    ~BasicSPH();

    std::vector<SPHParticle>& particles() { return _particles; }
	std::vector<SPHParticle>& boundaryparticles() { return _boundaryparticles; }

    void enableAdaptiveTimeStep(double tolerance = 0.25, double min = 1E-7, double max = 1.0 );
    void disableAdaptativeTimeStep() { _useAdaptiveTimeStep = false; }
    void run(double time);

private:
	// Simulation steps
	void searchBoundaryNeighbors();
	void computePsi();
    void buildFluidNeighbors();
	void buildBoundaryNeighbors();
    void computeDensityAndPressure();
    void addExternalForces();
    void computeArtificialViscosityForces();
    void computePressureForces();
    void integrate();

    // Adaptative time step
    void computeTimeStep();

    // Kernel (M4 - Cubic spline)
    void precomputeKernelCoefficients();
    double getKernelValue(double dist) const;
    Vec3d getKernelGradient(double dist, const Vec3d& xij) const;
    double getKernelLaplacian(double dist) const;

private:
    // Private structures
    struct Neighbor
    {
        Neighbor(long id, const Vec3d& xij, double dist) : id(id), dist(dist), xij(xij) {}
        long	id;
        double	dist;
        Vec3d	xij;
    };

    // Particles
	std::vector<SPHParticle>			_boundaryparticles;
    std::vector<SPHParticle>			_particles;
    std::vector<std::vector<Neighbor> >	_neighbors;
	std::vector<std::vector<Neighbor> > _boundaryneighbors;
	//Boundary neighbors particles

	std::vector<std::vector<Neighbor> >	_rigidneighbors;

    // Simulation properties
    Vec3d	_volumeMin;		// Simulation volume min
    Vec3d	_volumeMax;		// Simulation volume max
    double	_mass;			// Mass of a single particle
    double	_restDensity;	// Rest density of the fluid
    double	_k;				// Pressure constant (gaz constant)
    double	_dt;			// Timestep size (in seconds)
    double	_h;				// Smoothing radius
    double	_bulkViscosity;	// Bulk viscosity
    double	_shearViscosity;// Shear viscosity

    // Adaptative time stepping
    bool	_useAdaptiveTimeStep;
    double	_tolerance;
    double	_minDT;
    double	_maxDT;
    double	_maxuij;

    // Kernel precomputed values & coefficients
    double	_halfH;
    double	_kernelValueCoeff;
    double	_kernelGradientCoeffA;
    double	_kernelGradientCoeffB;
    double	_kernelLaplacianCoeffA;
    double	_kernelLaplacianCoeffB;
};


#endif // BASICSPH_H
