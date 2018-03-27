#pragma once
#include "FECoreBase.h"

//-----------------------------------------------------------------------------
// Forward declaration of the FEModel class.
class FEModel;

//-----------------------------------------------------------------------------
// This class implements a mechanism for defining callbacks from within plugins.
class FECallBack : public FECoreBase
{
public:
	// constructor requires the WHEN parameter (defined in FEModel.h)
	FECallBack(FEModel* pfem, int when);
	virtual ~FECallBack();

	// Override this function in the derived class.
	virtual bool Execute(FEModel& fem, int nwhen) = 0;
};
