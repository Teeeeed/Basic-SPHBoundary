#ifndef HOUDINIFILEDUMPHELPER_H
#define HOUDINIFILEDUMPHELPER_H

#include <string>
#include <vector>
#include <ostream>

class HoudiniFileDumpParticles
{
public:
	class ParticlesDataProvider;

public:
	HoudiniFileDumpParticles();
	HoudiniFileDumpParticles(ParticlesDataProvider* dataProvider);
	~HoudiniFileDumpParticles();

	void setDataProvider(ParticlesDataProvider* dataProvider);
	void dump(std::ostream& stream);

private:
	ParticlesDataProvider*	_dataProvider;
};

class HoudiniFileDumpParticles::ParticlesDataProvider
{
public:

	ParticlesDataProvider() {}
	virtual ~ParticlesDataProvider() {}

	virtual int getNbPoints() = 0;
	virtual int getNbAttributes() = 0;
	virtual void getAttributesInfo(std::vector<std::string>& names, std::vector<int>& nbValues) = 0;

	virtual void getPtPosition(int ptID, float& posX, float& posY, float& posZ, float& posW) = 0;
	virtual void getPtAttributes(int ptID, const std::string& attribDelim, const std::string& valueDelim, std::ostream& out) = 0;
};

#endif	// HOUDINIFILEDUMPHELPER_H
