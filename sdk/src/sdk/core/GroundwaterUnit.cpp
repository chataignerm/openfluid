/**
  \file GroundwaterUnit.cpp
  \brief

  \author Jean-Christophe FABRE <fabrejc@ensam.inra.fr>
*/


#include "GroundwaterUnit.h"



namespace mhydasdk { namespace core {


GroundwaterUnit::GroundwaterUnit()
           : HydroObject()
{
  m_UsrArea = -1;
  m_GUExchangeID = -1;
	m_SubstratumLevel = -1;

  mp_GUExchange = NULL;
}


GroundwaterUnit::GroundwaterUnit(hoid_t ID,int ProcessOrder,
                                hoid_t GUExchangeID, double SubstratumLevel)
           : HydroObject(ID, ProcessOrder)
{

  m_GUExchangeID = GUExchangeID;
	m_SubstratumLevel = SubstratumLevel;

  mp_GUExchange = NULL;
}

GroundwaterUnit::~GroundwaterUnit()
{

}


// =====================================================================
// =====================================================================


double GroundwaterUnit::getUsrArea() const
{
  return m_UsrArea;
}


// =====================================================================
// =====================================================================



hoid_t GroundwaterUnit::getGUExchangeID() const
{
  return m_GUExchangeID;
}


// =====================================================================
// =====================================================================


double GroundwaterUnit::getSubstratumLevel() const
{
  return m_SubstratumLevel;
}


// =====================================================================
// =====================================================================


void GroundwaterUnit::setGUExchange(GroundwaterUnit *GU)
{
  mp_GUExchange = GU;
}


// =====================================================================
// =====================================================================



void GroundwaterUnit::setSubstratumLevel(double Level)
{
  m_SubstratumLevel = Level;
}


} } // namespace mhydasdk::core
