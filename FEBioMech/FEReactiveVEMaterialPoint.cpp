/*This file is part of the FEBio source code and is licensed under the MIT license
listed below.

See Copyright-FEBio.txt for details.

Copyright (c) 2020 University of Utah, The Trustees of Columbia University in 
the City of New York, and others.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/



#include "stdafx.h"
#include "FEReactiveVEMaterialPoint.h"
#include "FEElasticMaterial.h"

///////////////////////////////////////////////////////////////////////////////
//
// FEReactiveVEMaterialPoint
//
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//! Create a shallow copy of the material point data
FEMaterialPoint* FEReactiveVEMaterialPoint::Copy()
{
    FEReactiveVEMaterialPoint* pt = new FEReactiveVEMaterialPoint(*this);
    if (m_pNext) pt->m_pNext = m_pNext->Copy();
    return pt;
}

//-----------------------------------------------------------------------------
//! Initializes material point data.
void FEReactiveVEMaterialPoint::Init()
{
	// initialize data to zero
	m_Fv.clear();
	m_Jv.clear();
	m_v.clear();
	m_f.clear();
    
    // don't forget to initialize the base class
    FEMaterialPoint::Init();
}

//-----------------------------------------------------------------------------
//! Update material point data.
void FEReactiveVEMaterialPoint::UpdateGenerations(const FETimeInfo& timeInfo)
{
    FEElasticMaterialPoint& pt = *m_pNext->ExtractData<FEElasticMaterialPoint>();

	// check if the current deformation gradient is different from that of
	// the last generation, in which case store the current state
	if (m_pRve) {
	    if (m_pRve->NewGeneration(*this)) {
            m_v.push_back(timeInfo.currentTime);
            m_Fv.push_back(pt.m_F);
            m_Jv.push_back(pt.m_J);
            double f = (!m_v.empty()) ? m_pRve->ReformingBondMassFraction(*this) : 1;
			m_f.push_back(f);
            m_pRve->CullGenerations(*this);
		}
	}
	else {
		if (m_pRuc->NewGeneration(*this)) {
            m_v.push_back(timeInfo.currentTime);
            m_Fv.push_back(pt.m_F);
            m_Jv.push_back(pt.m_J);
            double f = (!m_v.empty()) ? m_pRuc->ReformingBondMassFraction(*this) : 1;
            m_f.push_back(f);
            m_pRuc->CullGenerations(*this);
		}
	}
}

//-----------------------------------------------------------------------------
//! Serialize data to the archive
void FEReactiveVEMaterialPoint::Serialize(DumpStream& ar)
{
    FEMaterialPoint::Serialize(ar);
    
    if (ar.IsSaving())
    {
        int n = (int)m_Fv.size();
        ar << n;
        for (int i=0; i<n; ++i) ar << m_Fv[i] << m_Jv[i] << m_v[i] << m_f[i];
    }
    else
    {
        int n;
        ar >> n;
		m_Fv.resize(n);
		m_Jv.resize(n);
		m_v.resize(n);
		m_f.resize(n);
        for (int i=0; i<n; ++i) ar >> m_Fv[i] >> m_Jv[i] >> m_v[i] >> m_f[i];
    }
}
