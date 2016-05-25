#pragma once
#include "FEBioImport.h"

//-----------------------------------------------------------------------------
// MeshData Section (introduced in febio_spec 2.5)
class FEBioMeshDataSection : public FEBioFileSection
{
	struct ELEMENT_DATA
	{
		int		nval;	// number of values read
		double	val[FEElement::MAX_NODES];	// scalar value
	};

public:
	FEBioMeshDataSection(FEBioImport* pim) : FEBioFileSection(pim){}
	void Parse(XMLTag& tag);

protected:
	void ParseShellThickness(XMLTag& tag, FEElementSet& set);
	void ParseMaterialFibers(XMLTag& tag, FEElementSet& set);
	void ParseMaterialAxes  (XMLTag& tag, FEElementSet& set);
	void ParseMaterialData  (XMLTag& tag, FEElementSet& set, const string& name);

private:
	void ParseElementData(XMLTag& tag, FEElementSet& set, vector<ELEMENT_DATA>& values, int nvalues);

private:
	vector<FEElement*> m_pelem;
};
