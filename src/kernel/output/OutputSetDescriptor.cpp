/***copyright>=========================================================

  OpenFLUID - Software environment for modelling Fluxes In Landscapes

  This file is a part of OpenFLUID software
  http://www.umr-lisah.fr/openfluid
  Copyright (c) INRA
  See the file "copyright" for the full license governing this code.

=========================================================<copyright***/


/**
  \file OutputSetDescriptor.cpp
  \brief Implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */

#include "OutputSetDescriptor.h"

// =====================================================================
// =====================================================================


OutputSetDescriptor::OutputSetDescriptor(std::string SetName, std::string UnitsClass)
{
  m_Name = SetName;
  m_UnitsClass = UnitsClass;

  m_AllUnits = false;
  m_UnitsID.clear();
  m_AllScalars = false;
  m_ScalarVariables.clear();
  m_AllVectors = false;
  m_VectorVariables.clear();
}


// =====================================================================
// =====================================================================


OutputSetDescriptor::~OutputSetDescriptor()
{

}


// =====================================================================
// =====================================================================

