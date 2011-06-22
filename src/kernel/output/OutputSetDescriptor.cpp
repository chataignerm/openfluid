/*
  This file is part of OpenFLUID-engine software
  Copyright (c) 2007-2010 INRA-Montpellier SupAgro

 == GNU General Public License Usage ==

  OpenFLUID-engine is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID-engine is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID-engine.  If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, INRA gives You the additional right
  to dynamically link the code of OpenFLUID-engine with code not covered 
  under the GNU General Public License ("Non-GPL Code") and to distribute
  linked combinations including the two, subject to the limitations in this
  paragraph. Non-GPL Code permitted under this exception must only link to
  the code of OpenFLUID-engine dynamically through the ofelib library
  interface, and only for building OpenFLUID-engine plugins. The files of
  Non-GPL Code may be link to the ofelib library without causing the
  resulting work to be covered by the GNU General Public License. You must
  obey the GNU General Public License in all respects for all of the
  OpenFLUID-engine code and other code used in conjunction with
  OpenFLUID-engine except the Non-GPL Code covered by this exception. If
  you modify this OpenFLUID-engine, you may extend this exception to your
  version of the file, but you are not obligated to do so. If you do not
  wish to provide this exception without modification, you must delete this
  exception statement from your version and license this OpenFLUID-engine
  solely under the GPL without exception.


 == Other Usage ==

  Other Usage means a use of OpenFLUID-Engine that is inconsistent with
  the GPL license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID-engine may use this file in
  accordance with the terms contained in the written agreement between
  You and INRA.
*/


/**
  \file OutputSetDescriptor.cpp
  \brief Implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */

#include "OutputSetDescriptor.h"
#include "openfluid-tools.h"

// =====================================================================
// =====================================================================


OutputSetDescriptor::OutputSetDescriptor()
{
  m_Name = "";
  m_UnitsClass = "";
  m_AllUnits = false;
  m_UnitsIDs.clear();
  m_UnitsPtr.clear();
  m_AllScalars = false;
  m_ScalarVariables.clear();
  m_AllVectors = false;
  m_VectorVariables.clear();
  m_Precision = 5;
}


// =====================================================================
// =====================================================================


OutputSetDescriptor::~OutputSetDescriptor()
{

}


// =====================================================================
// =====================================================================


void OutputSetDescriptor::fillUnitsPtr()
{
  openfluid::core::Unit* UPtr;

  m_UnitsPtr.resize(m_UnitsIDs.size(), NULL);

  for (unsigned int i = 0; i < m_UnitsIDs.size() ; i++)
  {
    UPtr = openfluid::core::CoreRepository::getInstance()->getUnit(m_UnitsClass,m_UnitsIDs[i]);

    if (UPtr == NULL)
    {
      std::string UnitIDStr;
      openfluid::tools::ConvertValue(m_UnitsIDs[i],&UnitIDStr);
      throw openfluid::base::OFException("kernel","OutputSetDescriptor::fillUnitsPtr()","unit #" + UnitIDStr + " not found in class " + m_UnitsClass);
    }
    else
      m_UnitsPtr[i] = UPtr;

  }

}