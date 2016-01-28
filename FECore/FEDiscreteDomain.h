#pragma once
#include "FEDomain.h"

//-----------------------------------------------------------------------------
//! domain for discrete elements
class FEDiscreteDomain : public FEDomain
{
public:
	FEDiscreteDomain(FEMesh* pm) : FEDomain(FE_DOMAIN_DISCRETE, pm) {}

	void create(int n) { m_Elem.resize(n); }
	int Elements() { return (int) m_Elem.size(); }
	FEElement& ElementRef(int n) { return m_Elem[n]; }

	FEDiscreteElement& Element(int n) { return m_Elem[n]; }

	bool Initialize(FEModel& fem);

	//! Serialize data to archive
	void Serialize(DumpStream& ar);

public:
	void AddElement(int eid, int n[2]);

protected:
	vector<FEDiscreteElement>	m_Elem;
};
