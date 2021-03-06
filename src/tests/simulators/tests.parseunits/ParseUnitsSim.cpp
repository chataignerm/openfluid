/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
  
*/



/**
  \file ParseUnitsSim.cpp
  \brief Implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#include <openfluid/ware/PluggableSimulator.hpp>


// =====================================================================
// =====================================================================


DECLARE_SIMULATOR_PLUGIN

// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("tests.parseunits")

  DECLARE_NAME("test simulator for parsing units");
  DECLARE_DESCRIPTION("");

  DECLARE_VERSION("1.0");
  DECLARE_SDKVERSION;
  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);

  DECLARE_DOMAIN("");
  DECLARE_PROCESS("");
  DECLARE_METHOD("");
  DECLARE_AUTHOR("","");


END_SIMULATOR_SIGNATURE

/**

*/
class ParseUnitsSimulator : public openfluid::ware::PluggableSimulator
{
  private:

  public:


  ParseUnitsSimulator() : PluggableSimulator()
  {


  }


  // =====================================================================
  // =====================================================================


  ~ParseUnitsSimulator()
  {


  }


  // =====================================================================
  // =====================================================================


  void initParams(const openfluid::ware::WareParams_t& /*Params*/)
  {  }

  // =====================================================================
  // =====================================================================


  void prepareData()
  {  }


  // =====================================================================
  // =====================================================================


  void checkConsistency()
  {  }


  // =====================================================================
  // =====================================================================


  openfluid::base::SchedulingRequest initializeRun()
  {
    return DefaultDeltaT();
  }

  // =====================================================================
  // =====================================================================


  openfluid::base::SchedulingRequest runStep()
  {

    openfluid::core::Unit* CurrentUnit;
    const openfluid::core::UnitsListByClassMap_t* UnitsByClass;
    const openfluid::core::UnitsList_t* UnitsList;
    const openfluid::core::UnitsPtrList_t* ToUnitsPtrList;
    const openfluid::core::UnitsPtrList_t* FromUnitsPtrList;
    std::vector<openfluid::core::UnitClass_t> ClassVector;

    openfluid::core::UnitsListByClassMap_t::const_iterator itUnitsClass;
    openfluid::core::UnitsList_t::const_iterator itUnitsList;
    openfluid::core::UnitsPtrList_t::const_iterator itToUnitsPtrList;
    openfluid::core::UnitsPtrList_t::const_iterator itFromUnitsPtrList;



    UnitsByClass = const_cast<openfluid::core::UnitsListByClassMap_t*>(mp_CoreData->getUnitsByClass());
/*
    std::cout << std::endl;
    std::cout.flush();
*/
    for (itUnitsClass=UnitsByClass->begin();itUnitsClass!=UnitsByClass->end();++itUnitsClass)
    {
      ClassVector.push_back((*itUnitsClass).first);
    }

    // To List
/*    std::cout << " -------  To  ------- " << std::endl;
    std::cout.flush();*/

    for (itUnitsClass=UnitsByClass->begin();itUnitsClass!=UnitsByClass->end();++itUnitsClass)
    {

      UnitsList = const_cast<openfluid::core::UnitsList_t*>(((*itUnitsClass).second).getList());

      for (itUnitsList=UnitsList->begin();itUnitsList!=UnitsList->end();++itUnitsList)
      {
        CurrentUnit = const_cast<openfluid::core::Unit*>(&(*itUnitsList));

        std::string SrcClassStr = CurrentUnit->getClass();
        std::string SrcIDStr = "";
        openfluid::tools::ConvertValue(CurrentUnit->getID(),&SrcIDStr);

        for (unsigned int i=0;i<ClassVector.size();i++)
        {
          ToUnitsPtrList = const_cast<openfluid::core::UnitsPtrList_t*>(CurrentUnit->getToUnits(ClassVector[i]));

          if (ToUnitsPtrList != NULL)
          {
            std::string DestClassStr = ClassVector[i];

            for (itToUnitsPtrList=ToUnitsPtrList->begin();itToUnitsPtrList!=ToUnitsPtrList->end();++itToUnitsPtrList)
            {
              std::string DestIDStr = "";
              openfluid::tools::ConvertValue((*itToUnitsPtrList)->getID(),&DestIDStr);
/*              std::cout << SrcClassStr << "#" << SrcIDStr << " --> "<< DestClassStr << "#" << DestIDStr << std::endl;
              std::cout.flush();*/
            }
          }
        }
      }
    }

    // From List
/*    std::cout << " -------  From  ------- " << std::endl;
    std::cout.flush();*/

    for (itUnitsClass=UnitsByClass->begin();itUnitsClass!=UnitsByClass->end();++itUnitsClass)
    {

      UnitsList = const_cast<openfluid::core::UnitsList_t*>(((*itUnitsClass).second).getList());

      for (itUnitsList=UnitsList->begin();itUnitsList!=UnitsList->end();++itUnitsList)
      {
        CurrentUnit = const_cast<openfluid::core::Unit*>(&(*itUnitsList));

        std::string SrcClassStr = CurrentUnit->getClass();
        std::string SrcIDStr = "";
        openfluid::tools::ConvertValue(CurrentUnit->getID(),&SrcIDStr);

        for (unsigned int i=0;i<ClassVector.size();i++)
        {
          FromUnitsPtrList = const_cast<openfluid::core::UnitsPtrList_t*>(CurrentUnit->getFromUnits(ClassVector[i]));

          if (FromUnitsPtrList != NULL)
          {
            std::string DestClassStr = ClassVector[i];

            for (itFromUnitsPtrList=FromUnitsPtrList->begin();itFromUnitsPtrList!=FromUnitsPtrList->end();++itFromUnitsPtrList)
            {
              std::string DestIDStr = "";
              openfluid::tools::ConvertValue((*itFromUnitsPtrList)->getID(),&DestIDStr);
/*              std::cout << SrcClassStr << "#" << SrcIDStr << " <-- "<< DestClassStr << "#" << DestIDStr << std::endl;
              std::cout.flush();*/
            }
          }
        }
      }


    }


    return DefaultDeltaT();
  }

  // =====================================================================
  // =====================================================================


  void finalizeRun()
  {  }

};

// =====================================================================
// =====================================================================

DEFINE_SIMULATOR_CLASS(ParseUnitsSimulator)

