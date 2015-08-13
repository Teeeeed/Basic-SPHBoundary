#include "BasicSPH.h"
#include "SPHParticleHoudiniIO.h"
#include "SPHParticleHoudiniIO.cpp"

#include <string>
#include <math.h>
#include <iostream>


//--------------------------------------------------------------------------------------------------
// initParticlesBox
void initParticlesBox(const Vec3d& 				boxMin,
                      const Vec3d& 				boxMax,
                      double 					spacing,
                      std::vector<SPHParticle>&	particles)
{
    int resX = static_cast<int>(floor((boxMax.x-boxMin.x) / spacing));
    int resY = static_cast<int>(floor((boxMax.y-boxMin.y) / spacing));
    int resZ = static_cast<int>(floor((boxMax.z-boxMin.z) / spacing));

    // Clear previous particles
    particles.clear();

    // Fill box with particles
    particles.reserve(resX*resY*resZ);
    for (int x=0; x<resX; ++x)
    {
        for (int y=0; y<resY; ++y)
        {
            for (int z=0; z<resZ; ++z)
            {
                SPHParticle particle;

                // Init position
                particle.pos.x = static_cast<double>(x) * spacing + boxMin.x;
                particle.pos.y = static_cast<double>(y) * spacing + boxMin.y;
                particle.pos.z = static_cast<double>(z) * spacing + boxMin.z;

                // Init other properties
                particle.vel = Vec3d(0,0,0);

                // Add particle
                particles.push_back(particle);
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------
// initBoundary
void initBoundary(const Vec3d&						boxMin,
				  const Vec3d&						boxMax,
				  double							spacing,
				  std::vector<SPHParticle>&			particles)
{
    int resX = static_cast<int>(floor((boxMax.x-boxMin.x) / spacing));
    int resY = static_cast<int>(floor((boxMax.y-boxMin.y) / spacing));
    int resZ = static_cast<int>(floor((boxMax.z-boxMin.z) / spacing));

    // Clear previous particles
    particles.clear();

    // Fill the surface of rigid body with particles
    particles.reserve(resY*resZ*2+resX*resY*2+resX*resZ*2);
    for (int x=0; x<=resX; x += resX)
    {
        for (int y=0; y<=resY; ++y)
        {
            for (int z=0; z<=resZ; ++z)
            {
                SPHParticle particle;

                // Init position
                particle.pos.x = static_cast<double>(x) * spacing + boxMin.x;
                particle.pos.y = static_cast<double>(y) * spacing + boxMin.y;
                particle.pos.z = static_cast<double>(z) * spacing + boxMin.z;

                 //Init other properties
                particle.vel = Vec3d(0,0,0);
				particle.accel = Vec3d(0,0,0);
				particle.density = 0.0;
				particle.oneOverDensity = 0.0;
				particle.pressure = 0.0;
				particle.sigma = 0.0;
				particle.Psi = 0.0;
                // Add particle
                particles.push_back(particle);
            }
        }
    }
	for (int z=0; z<=resZ; z += resZ)
    {
        for (int y=0; y<=resY; ++y)
        {
            for (int x=1; x<resX; ++x)
            {
                SPHParticle particle;

                // Init position
                particle.pos.x = static_cast<double>(x) * spacing + boxMin.x;
                particle.pos.y = static_cast<double>(y) * spacing + boxMin.y;
                particle.pos.z = static_cast<double>(z) * spacing + boxMin.z;

                // Init other properties
                particle.vel = Vec3d(0,0,0);
				particle.accel = Vec3d(0,0,0);
				particle.density = 0.0;
				particle.oneOverDensity = 0.0;
				particle.pressure = 0.0;
				particle.sigma = 0.0;
				particle.Psi = 0.0;
                // Add particle
                particles.push_back(particle);
            }
        }
    }
    for (int y=0; y<=resY; y += resY)	
    {
		for (int z=1; z<resZ; ++z)
        {
            for (int x=1; x<resX; ++x)
            {
                SPHParticle particle;

                // Init position
                particle.pos.x = static_cast<double>(x) * spacing + boxMin.x;
                particle.pos.y = static_cast<double>(y) * spacing + boxMin.y;
                particle.pos.z = static_cast<double>(z) * spacing + boxMin.z;

                // Init other properties
                particle.vel = Vec3d(0,0,0);
				particle.accel = Vec3d(0,0,0);
				particle.density = 0.0;
				particle.oneOverDensity = 0.0;
				particle.pressure = 0.0;
				particle.sigma = 0.0;
				particle.Psi = 0.0;
                // Add particle
                particles.push_back(particle);
            }
        }
    }
}
//------------------------------------------------------------------------------------------------
//init a static Cubic
void initCubic(const Vec3d& 				boxMin,
                      const Vec3d& 				boxMax,
                      double 					spacing,
                      std::vector<SPHParticle>&	particles)
{
    int resX = static_cast<int>(floor((boxMax.x-boxMin.x) / spacing));
    int resY = static_cast<int>(floor((boxMax.y-boxMin.y) / spacing));
    int resZ = static_cast<int>(floor((boxMax.z-boxMin.z) / spacing));

    // Clear previous particles
    particles.clear();

    // Fill box with particles
    particles.reserve(resX*resY*resZ);
    for (int x=0; x<resX; ++x)
    {
        for (int y=0; y<resY; ++y)
        {
            for (int z=0; z<resZ; ++z)
            {
                SPHParticle particle;

                // Init position
                particle.pos.x = static_cast<double>(x) * spacing + boxMin.x;
                particle.pos.y = static_cast<double>(y) * spacing + boxMin.y;
                particle.pos.z = static_cast<double>(z) * spacing + boxMin.z;

                // Init other properties
                particle.vel = Vec3d(0,0,0);
				particle.accel = Vec3d(0,0,0);
				particle.density = 0.0;
				particle.oneOverDensity = 0.0;
				particle.pressure = 0.0;
				particle.sigma = 0.0;
				particle.Psi = 0.0;
                // Add particle
                particles.push_back(particle);
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------
// MAIN
int main(int argc, char* argv[])
{
    // Validate arguments
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " OutputDirectory" << std::endl;
        return -1;
    }

    std::string outputPath(argv[1]);


    // Init simulator
    std::cout << "Initializing simulator..." << std::endl;
    const Vec3d volumeMin( -9, 0, -2);
    const Vec3d volumeMax( 9, 6, 2);
    const double mass = 2.0;
    const double restDensity = 998.23;
    const double h = 0.2;
    const double k = 100.0;
    const double dt = 0.001;
    BasicSPH sph(volumeMin, volumeMax, mass, restDensity, h, k, dt);
    sph.enableAdaptiveTimeStep();

    // Init particles
    std::cout << "Initializing particles" << std::endl;
    Vec3d boxMin(-9, 0, -2);
    Vec3d boxMax(-3, 4, 2);
    initParticlesBox(boxMin, boxMax, 0.1, sph.particles());

	// Init boundary particles
	std::cout << "Initializing boundary particles" << std::endl;
	std::vector<SPHParticle> cubicparticles;
    Vec3d cubicMin( 4, 0, -0.75);
    Vec3d cubicMax( 5.5, 1.5,  0.75);
    initCubic(cubicMin, cubicMax, 0.1, cubicparticles);
	std::vector<SPHParticle> faceparticles1;
	Vec3d boundaryMin1( -9.1, -0.1, -2.1);
	Vec3d boundaryMax1( 9.1, 6.1, 2.1);
	initBoundary(boundaryMin1, boundaryMax1, 0.1, faceparticles1);
	//std::vector<SPHParticle> faceparticles2;
	//Vec3d boundaryMin2( -3.2, -0.2, -1.2);
	//Vec3d boundaryMax2( 3.2, 3.2, 1.2);
	//initBoundary(boundaryMin2, boundaryMax2, 0.1, faceparticles2);
	//std::vector<SPHParticle> faceparticles3;
	//Vec3d boundaryMin3( -3.3, -0.3, -1.3);
	//Vec3d boundaryMax3( 3.3, 3.3, 1.3);
	//initBoundary(boundaryMin3, boundaryMax3, 0.1, faceparticles3);
	sph.boundaryparticles().clear();
	sph.boundaryparticles().insert(sph.boundaryparticles().begin(),faceparticles1.begin(),faceparticles1.end());
	//sph.boundaryparticles().insert(sph.boundaryparticles().begin(),faceparticles2.begin(),faceparticles2.end());
	//sph.boundaryparticles().insert(sph.boundaryparticles().begin(),faceparticles3.begin(),faceparticles3.end());
	sph.boundaryparticles().insert(sph.boundaryparticles().begin(),cubicparticles.begin(),cubicparticles.end());
    // Output first frame (initial frames)
    const std::string filePrefix("particles_");
	// Merge two vectors
	std::vector<SPHParticle> allparticles;
	allparticles.clear();
	allparticles.insert(allparticles.begin(),cubicparticles.begin(),cubicparticles.end());
	allparticles.insert(allparticles.begin(),sph.particles().begin(),sph.particles().end());
    //
	SPHParticleHoudiniIO::outputParticles(allparticles, outputPath, filePrefix, 1);
 
    // Run simulation and output a frame every 1/24 second
    std::cout << "Running simulation!" << std::endl;
    const double frameTime = 1.0/24.0;
    const double totalSimulationTime = 10.0;
    double time = 0.0;
    int currentFrame = 2;
    while (time < totalSimulationTime)
    {
        std::cout << "Simulating frame " << currentFrame << " (" << (frameTime+time) << "s)";
        std::cout << std::endl;
        // Run simulation
        sph.run(frameTime);
        // Output particles
		//merge two vectors
		allparticles.clear();
		allparticles.insert(allparticles.begin(),cubicparticles.begin(),cubicparticles.end());
		allparticles.insert(allparticles.begin(),sph.particles().begin(),sph.particles().end());
		//

		SPHParticleHoudiniIO::outputParticles(allparticles, outputPath, filePrefix, currentFrame);
        
		// Update simulation time
        time += frameTime;
        ++currentFrame;
    }

    std::cout << "Done!" << std::endl;

   return 0;
}
