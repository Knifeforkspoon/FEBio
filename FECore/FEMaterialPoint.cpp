#include "stdafx.h"
#include "FEMaterialPoint.h"

double FEMaterialPoint::time = 0;
double FEMaterialPoint::dt   = 0;

FEMaterialPoint::FEMaterialPoint(FEMaterialPoint* ppt)
{
	m_pPrev = 0;
	m_pNext = ppt;
	if (ppt) ppt->m_pPrev = this;
}

FEMaterialPoint::~FEMaterialPoint()
{ 
	if (m_pNext) delete m_pNext;
	m_pNext = m_pPrev = 0;
}

void FEMaterialPoint::SetPrev(FEMaterialPoint* pt)
{
	m_pPrev = pt;
}

void FEMaterialPoint::Init(bool bflag)
{
	if (m_pNext) m_pNext->Init(bflag);
}

void FEMaterialPoint::Serialize(DumpStream& ar)
{
	FEParamContainer::Serialize(ar);
	if (m_pNext) m_pNext->Serialize(ar);
}
