#pragma once
#include "FECore/FENewtonSolver.h"
#include "FECore/LinearSolver.h"

class FEGlobalMatrix;

//-----------------------------------------------------------------------------
//! The FELinearSolidSolver class solves linear (quasi-static) elasticity 
//! problems.
//!
class FELinearSolidSolver : public FENewtonSolver
{
public:
	//! constructor
	FELinearSolidSolver(FEModel* pfem);

	//! destructor
	~FELinearSolidSolver();

	//! Solve the analysis step
	bool Quasin(double time);

	//! Data serialization
	void Serialize(DumpStream& ar);

protected:
	//! calculate the residual
	void Residual();

	//! calculate the stiffness matrix
	bool StiffnessMatrix(const FETimePoint& tp);

	//! update solution
	void Update(vector<double>& u);

public:
	//! assemble element stiffness matrix
	void AssembleStiffness(vector<int>& en, vector<int>& elm, matrix& ke);

public:
	double	m_Dtol;			//!< displacement tolerance

protected:
	vector<double>	m_u;	//!< nodal displacements
	vector<double>	m_R;	//!< right hand side
	vector<double>	m_d;	//!< prescribed displacements

	int	m_dofX;
	int	m_dofY;
	int	m_dofZ;

public:
	// declare the parameter list
	DECLARE_PARAMETER_LIST();
};
