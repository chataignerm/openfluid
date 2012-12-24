/*
  This file is part of OpenFLUID software
  Copyright (c) 2007-2010 INRA-Montpellier SupAgro


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
  along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, INRA gives You the additional right
  to dynamically link the code of OpenFLUID with code not covered
  under the GNU General Public License ("Non-GPL Code") and to distribute
  linked combinations including the two, subject to the limitations in this
  paragraph. Non-GPL Code permitted under this exception must only link to
  the code of OpenFLUID dynamically through the OpenFLUID libraries
  interfaces, and only for building OpenFLUID plugins. The files of
  Non-GPL Code may be link to the OpenFLUID libraries without causing the
  resulting work to be covered by the GNU General Public License. You must
  obey the GNU General Public License in all respects for all of the
  OpenFLUID code and other code used in conjunction with OpenFLUID
  except the Non-GPL Code covered by this exception. If you modify
  this OpenFLUID, you may extend this exception to your version of the file,
  but you are not obligated to do so. If you do not wish to provide this
  exception without modification, you must delete this exception statement
  from your version and license this OpenFLUID solely under the GPL without
  exception.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
*/


/**
  \file PluggableFunction.cpp
  \brief Implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */



#include <openfluid/config.hpp>
#include <openfluid/base/OFException.hpp>
#include <openfluid/core/BooleanValue.hpp>
#include <openfluid/core/MatrixValue.hpp>
#include <openfluid/tools/SwissTools.hpp>
#include <openfluid/ware/PluggableFunction.hpp>


// =====================================================================
// =====================================================================


namespace openfluid { namespace ware {



PluggableFunction::PluggableFunction()
  : SimulationContributorWare(),
    m_MaxThreads(openfluid::config::FUNCTIONS_MAXNUMTHREADS),
    m_Initialized(false)
{

}


// =====================================================================
// =====================================================================


PluggableFunction::~PluggableFunction()
{
  finalizeWare();
}


// =====================================================================
// =====================================================================


void PluggableFunction::initializeWare(const WareID_t& ID,const unsigned int& MaxThreads)
{
  if (m_Initialized) return;

  SimulationContributorWare::initializeWare(ID);

  m_MaxThreads = MaxThreads;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::IsUnitIDInPtrList(const openfluid::core::UnitsPtrList_t* UnitsList,
                                          const openfluid::core::UnitID_t& ID)
{
  if (UnitsList == NULL) return false;

  bool Found = false;
  openfluid::core::UnitsPtrList_t::const_iterator UnitsIt = UnitsList->begin();

  while (!Found && UnitsIt != UnitsList->end())
  {
    if ((*UnitsIt)->getID() == ID) Found = true;
    UnitsIt++;
  }

  return Found;
}


// =====================================================================
// =====================================================================


std::string PluggableFunction::generateDotEdge(std::string SrcClass, std::string SrcID,
                                               std::string DestClass, std::string DestID,
                                               std::string Options)
{
  return "\""+SrcClass+" #"+SrcID+"\" -> \""+DestClass+" #"+DestID+"\"" + Options;
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AppendVariable(openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::Value& Val)
{
  OPENFLUID_AppendVariable(*UnitPtr,VarName,Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AppendVariable(openfluid::core::Unit& aUnit,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::Value& Val)
{
  if (&aUnit != NULL)
  {
    if (!aUnit.getVariables()->appendValue(VarName,OPENFLUID_GetCurrentTimeIndex(),Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Error appending value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Unit is NULL");
}

// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AppendVariable(openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const double Val)
{
  /* Do not call OPENFLUID_AppendVariable(UnitPtr,VarName,openfluid::core::DoubleValue(Value))
   * because of cast operator, this function is called (recursively)
   */
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->appendValue(VarName,OPENFLUID_GetCurrentTimeIndex(),openfluid::core::DoubleValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Error appending double value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AppendVariable(openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const long Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->appendValue(VarName,OPENFLUID_GetCurrentTimeIndex(),openfluid::core::IntegerValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Error appending long value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AppendVariable(openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const bool Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->appendValue(VarName,OPENFLUID_GetCurrentTimeIndex(),openfluid::core::BooleanValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Error appending boolean value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AppendVariable(openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const std::string& Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->appendValue(VarName,OPENFLUID_GetCurrentTimeIndex(),openfluid::core::StringValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Error appending string value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetVariable(openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::TimeStep_t Step,
                                        const openfluid::core::Value& Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->modifyValue(VarName,Step,Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Error setting value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetVariable(openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::TimeStep_t Step,
                                        const double Val)
{
  /* Do not call OPENFLUID_SetVariable(UnitPtr,VarName,openfluid::core::DoubleValue(Value))
   * because of cast operator, THIS function is called (recursively)
   */
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->modifyValue(VarName,Step,openfluid::core::DoubleValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Error setting double value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetVariable(openfluid::core::Unit *UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       const long Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->modifyValue(VarName,Step,openfluid::core::IntegerValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Error setting long value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetVariable(openfluid::core::Unit *UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       const bool Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->modifyValue(VarName,Step,openfluid::core::BooleanValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Error setting boolean value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetVariable(openfluid::core::Unit *UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       const std::string Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->modifyValue(VarName,Step,openfluid::core::StringValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Error setting string value for variable "+ VarName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::TimeStep_t Step,
                                        openfluid::core::Value* Val) const
{
  OPENFLUID_GetVariable(UnitPtr, VarName,Step,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::TimeStep_t Step,
                                        openfluid::core::Value& Val) const
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getVariables()->getValue(VarName,Step,&Val))
    {
      std::string TimeStr;
      openfluid::tools::ConvertValue(Step,&TimeStr);
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetVariable","Value for variable "+ VarName +" does not exist or is not right type at time step "+ TimeStr);
    }
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       double* Val) const
{
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       double& Val) const
{
  openfluid::core::DoubleValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,&TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       long* Val) const
{
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       long& Val) const
{
  openfluid::core::IntegerValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,&TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       bool* Val) const
{
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       bool& Val) const
{
  openfluid::core::BooleanValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,&TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       std::string* Val) const
{
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetVariable(const openfluid::core::Unit* UnitPtr,
                                       const openfluid::core::VariableName_t VarName,
                                       const openfluid::core::TimeStep_t Step,
                                       std::string& Val) const
{
  openfluid::core::StringValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Step,&TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsVariableExist(const openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName) const
{
  return (UnitPtr != NULL && UnitPtr->getVariables()->isVariableExist(VarName));
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsVariableExist(const openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::TimeStep_t Step) const
{
   return (UnitPtr != NULL && UnitPtr->getVariables()->isVariableExist(VarName,Step));
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsVariableExist(const openfluid::core::Unit *UnitPtr,
                               const openfluid::core::VariableName_t VarName,
                               const openfluid::core::TimeStep_t Step,
                               const openfluid::core::Value::Type ValueType) const
{
  return (UnitPtr != NULL && UnitPtr->getVariables()->isVariableExist(VarName,Step,ValueType));
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsTypedVariableExist(const openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::Value::Type VarType) const
{
  return (UnitPtr != NULL && UnitPtr->getVariables()->isTypedVariableExist(VarName,VarType));
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsTypedVariableExist(const openfluid::core::Unit *UnitPtr,
                                        const openfluid::core::VariableName_t VarName,
                                        const openfluid::core::TimeStep_t Step,
                                        const openfluid::core::Value::Type VarType) const
{
  return (UnitPtr != NULL && UnitPtr->getVariables()->isTypedVariableExist(VarName,Step,VarType));
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetInputData(openfluid::core::Unit *UnitPtr,
                                const openfluid::core::InputDataName_t& InputName,
                                const openfluid::core::Value& Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->setValue(InputName,Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unable to set value for input data "+ InputName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetInputData(openfluid::core::Unit *UnitPtr,
                                               const openfluid::core::InputDataName_t& InputName,
                                               const double& Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->setValue(InputName,openfluid::core::DoubleValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unable to set double value for input data "+ InputName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetInputData(openfluid::core::Unit *UnitPtr,
                                               const openfluid::core::InputDataName_t& InputName,
                                               const long& Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->setValue(InputName,openfluid::core::IntegerValue(Val)))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unable to set long value for input data "+ InputName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetInputData(openfluid::core::Unit *UnitPtr,
                                               const openfluid::core::InputDataName_t& InputName,
                                               const std::string& Val)
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->setValue(InputName,Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unable to set string value for input data "+ InputName);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_SetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                            const openfluid::core::InputDataName_t InputName,
                            openfluid::core::StringValue& Val) const
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->getValue(InputName,Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","StringValue for input data "+ InputName +" does not exist");
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    openfluid::core::DoubleValue* Val) const
{
  OPENFLUID_GetInputData(UnitPtr,InputName,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    openfluid::core::DoubleValue& Val) const
{
  double TmpVal;
  OPENFLUID_GetInputData(UnitPtr,InputName,TmpVal);
  Val.set(TmpVal);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    openfluid::core::VectorValue* Val) const
{
  OPENFLUID_GetInputData(UnitPtr,InputName,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    openfluid::core::VectorValue& Val) const
{
  openfluid::core::StringValue TmpVal;
  OPENFLUID_GetInputData(UnitPtr,InputName,TmpVal);
  TmpVal.toVectorValue(Val.getStreamSeparator(1),Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                            const openfluid::core::InputDataName_t InputName,
                            openfluid::core::MatrixValue& Val) const
{
  openfluid::core::StringValue TmpVal;
  OPENFLUID_GetInputData(UnitPtr,InputName,TmpVal);
  TmpVal.toMatrixValue(Val.getStreamSeparator(1),Val.getStreamSeparator(2),Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    double *Val) const
{
  OPENFLUID_GetInputData(UnitPtr,InputName,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    double& Val) const
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->getValueAsDouble(InputName,Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","Double value for input data "+ InputName +" does not exist");
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    long *Val) const
{
  OPENFLUID_GetInputData(UnitPtr,InputName,*Val);
}



// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    long& Val) const
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->getValueAsLong(InputName,Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","Long integer for input data "+ InputName +" does not exist");
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    std::string *Val) const
{
  OPENFLUID_GetInputData(UnitPtr,InputName,*Val);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetInputData(const openfluid::core::Unit *UnitPtr,
                                    const openfluid::core::InputDataName_t InputName,
                                    std::string& Val) const
{
  if (UnitPtr != NULL)
  {
    if (!UnitPtr->getInputData()->getValue(InputName,Val))
      throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","String value for input data "+ InputName +" does not exist");
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetInputData","Unit is NULL");
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsInputDataExist(const openfluid::core::Unit *UnitPtr,
                               const openfluid::core::InputDataName_t InputName) const
{
  if (UnitPtr != NULL)
    return UnitPtr->getInputData()->isDataExist(InputName);

  throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_IsInputDataExist","Unit is NULL");
  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      openfluid::core::StringValue& Val) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
  {
    Val = it->second;

    return true;
  }

  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      openfluid::core::DoubleValue& Val) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
    return it->second.toDoubleValue(Val);

  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      openfluid::core::VectorValue& Val) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
    return it->second.toVectorValue(Val.getStreamSeparator(1),Val);

  return false;
}



// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                    const openfluid::core::FuncParamKey_t ParamName,
                                    openfluid::core::MatrixValue& Val) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
    return it->second.toMatrixValue(Val.getStreamSeparator(1),Val.getStreamSeparator(2),Val);

  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      double *Val) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Val);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      double& Val) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
    return it->second.toDouble(Val);

  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      long *Val) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Val);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      long& Val) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
    return it->second.toInteger(Val);

  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      float *Val) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Val);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      float& Val) const
{
  bool IsOk = false;

  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
  {
    double TmpDbl;

    IsOk = it->second.toDouble(TmpDbl);

    if(IsOk)
      Val = static_cast<float>(TmpDbl);
  }

  return IsOk;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      int *Val) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Val);
}



// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      int& Val) const
{
  bool IsOk = false;

  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
  {
    long TmpLong;

    IsOk = it->second.toInteger(TmpLong);

    if(IsOk)
      Val = static_cast<int>(TmpLong);
  }

  return IsOk;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::string *Val) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Val);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::string& Value) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
  {
    Value = it->second.get();

    return true;
  }

  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::vector<std::string> *Vals) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Vals);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::vector<std::string>& Vals) const
{
  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
  {
    std::vector<std::string> Tokens;

    openfluid::tools::TokenizeString(it->second.get(),Tokens,";");

    Vals.clear();

    for (unsigned int i=0;i<Tokens.size();i++)
      Vals.push_back(Tokens[i]);

    return true;
  }

  return false;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::vector<double> *Vals) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Vals);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::vector<double>& Vals) const
{
  bool IsOK = false;

  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
  {
    openfluid::core::VectorValue Vect;

    IsOK = it->second.toVectorValue(";",Vect);

    if(IsOK)
    {
      Vals.clear();

      for (unsigned long i=0;i<Vect.size();i++)
        Vals.push_back(Vect[i]);
    }
  }

  return IsOK;
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::vector<long> *Vals) const
{
  return OPENFLUID_GetFunctionParameter(Params,ParamName,*Vals);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetFunctionParameter(const openfluid::core::FuncParamsMap_t Params,
                                      const openfluid::core::FuncParamKey_t ParamName,
                                      std::vector<long>& Vals) const
{
  bool IsOK = false;

  openfluid::core::FuncParamsMap_t::const_iterator it = Params.find(ParamName);

  if (it != Params.end())
  {
    openfluid::core::VectorValue Vect;

    IsOK = it->second.toVectorValue(";",Vect);

    if(IsOK)
    {
      Vals.clear();

      for (unsigned long i=0;i<Vect.size();i++)
        Vals.push_back(static_cast<long>(Vect[i]));
    }
  }

  return IsOK;
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AppendEvent(openfluid::core::Unit *UnitPtr,
                                              openfluid::core::Event& Ev)
{
  if (UnitPtr != NULL)
  {
    Ev.setInstantiationType(openfluid::core::InstantiationInfo::SIMULATION);
    UnitPtr->getEvents()->addEvent(Ev);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AppendEvent","Unit is NULL");
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetEvents(const openfluid::core::Unit *UnitPtr,
                                            const openfluid::core::DateTime BeginDate,
                                            const openfluid::core::DateTime EndDate,
                                            openfluid::core::EventsCollection* Events) const
{
  OPENFLUID_GetEvents(UnitPtr,BeginDate,EndDate,*Events);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetEvents(const openfluid::core::Unit *UnitPtr,
                                            const openfluid::core::DateTime BeginDate,
                                            const openfluid::core::DateTime EndDate,
                                            openfluid::core::EventsCollection& Events) const
{
  if (UnitPtr != NULL)
    UnitPtr->getEvents()->getEventsBetween(BeginDate,EndDate,Events);

  else throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_GetEvents","Unit is NULL");
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsUnitExist(openfluid::core::UnitClass_t ClassName,
                                              openfluid::core::UnitID_t ID)
{
  return (mp_CoreData->getUnit(ClassName,ID) != NULL);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsUnitClassExist(openfluid::core::UnitClass_t ClassName)
{
  return mp_CoreData->isUnitsClassExist(ClassName);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetUnitsCount(const openfluid::core::UnitClass_t ClassName,
                                                unsigned int& UnitsCount)
{
  UnitsCount = 0;
  if (mp_CoreData->isUnitsClassExist(ClassName))
  {
    UnitsCount = mp_CoreData->getUnits(ClassName)->getList()->size();
    return true;
  }
  else return false;
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_GetUnitsCount(unsigned int& UnitsCount)
{
  UnitsCount = 0;
  openfluid::core::UnitsListByClassMap_t::const_iterator UnitsIt;

  for (UnitsIt = mp_CoreData->getUnitsByClass()->begin(); UnitsIt != mp_CoreData->getUnitsByClass()->end();++UnitsIt )
  {
    UnitsCount = UnitsCount + (*UnitsIt).second.getList()->size();
  }
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_GetUnit(const openfluid::core::UnitClass_t& ClassName,
                                          const openfluid::core::UnitID_t& ID,
                                          openfluid::core::Unit* aUnit)
{
  aUnit =  const_cast<openfluid::core::Unit*>(mp_CoreData->getUnit(ClassName,ID));
  return (aUnit != NULL);
}


// =====================================================================
// =====================================================================


openfluid::core::Unit* PluggableFunction::OPENFLUID_GetUnit(const openfluid::core::UnitClass_t& ClassName,
                                                            const openfluid::core::UnitID_t& ID)
{
  return mp_CoreData->getUnit(ClassName,ID);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_AddUnit(openfluid::core::UnitClass_t ClassName,
                                          openfluid::core::UnitID_t ID,
                                          openfluid::core::PcsOrd_t PcsOrder)
{
  if (!mp_CoreData->addUnit(openfluid::core::Unit(ClassName,ID,PcsOrder, openfluid::core::InstantiationInfo::SIMULATION)))
   throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AddUnit","Error adding unit");

  mp_CoreData->sortUnitsByProcessOrder();
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_DeleteUnit(openfluid::core::UnitClass_t ClassName,
                                             openfluid::core::UnitID_t ID)
{

  openfluid::core::Unit* TheUnit = mp_CoreData->getUnit(ClassName,ID);

  if (TheUnit == NULL)
    openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_DeleteUnit","error deleting unit");

  mp_CoreData->deleteUnit(TheUnit);

  mp_CoreData->sortUnitsByProcessOrder();
}

// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_AddFromToConnection(openfluid::core::UnitClass_t ClassNameFrom,
                                                      openfluid::core::UnitID_t IDFrom,
                                                      openfluid::core::UnitClass_t ClassNameTo,
                                                      openfluid::core::UnitID_t IDTo)
{
  openfluid::core::Unit* FromUnit = mp_CoreData->getUnit(ClassNameFrom, IDFrom);
  openfluid::core::Unit* ToUnit = mp_CoreData->getUnit(ClassNameTo, IDTo);

  return OPENFLUID_AddFromToConnection(FromUnit, ToUnit);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_AddFromToConnection(openfluid::core::Unit* FromUnit,
                                                      openfluid::core::Unit* ToUnit)
{
  if (FromUnit != NULL || ToUnit != NULL)
  {
    return (FromUnit->addToUnit(ToUnit) && ToUnit->addFromUnit(FromUnit));
  }
  else
    throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AddFromToConnection","Error adding from-to connection");
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_RemoveFromToConnection(openfluid::core::UnitClass_t ClassNameFrom,
                                                         openfluid::core::UnitID_t IDFrom,
                                                         openfluid::core::UnitClass_t ClassNameTo,
                                                         openfluid::core::UnitID_t IDTo)
{
  openfluid::core::Unit* FromUnit = mp_CoreData->getUnit(ClassNameFrom, IDFrom);
  openfluid::core::Unit* ToUnit = mp_CoreData->getUnit(ClassNameTo, IDTo);

  return OPENFLUID_RemoveFromToConnection(FromUnit, ToUnit);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_RemoveFromToConnection(openfluid::core::Unit* FromUnit,
                                                         openfluid::core::Unit* ToUnit)
{
  if (FromUnit == NULL || ToUnit == NULL)
    throw openfluid::base::OFException("OpenFLUID framework","CoreRepository::removeFromToConnection","Error removing from-to connection");
  else
    return mp_CoreData->removeFromToConnection(FromUnit,ToUnit);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_AddChildParentConnection(openfluid::core::UnitClass_t ClassNameChild,
                                                           openfluid::core::UnitID_t IDChild,
                                                           openfluid::core::UnitClass_t ClassNameParent,
                                                           openfluid::core::UnitID_t IDParent)
{
  openfluid::core::Unit* ChildUnit = mp_CoreData->getUnit(ClassNameChild, IDChild);
  openfluid::core::Unit* ParentUnit = mp_CoreData->getUnit(ClassNameParent, IDParent);

  return OPENFLUID_AddChildParentConnection(ChildUnit, ParentUnit);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_AddChildParentConnection(openfluid::core::Unit* ChildUnit,
                                                           openfluid::core::Unit* ParentUnit)
{
  if (ChildUnit != NULL || ParentUnit != NULL)
  {
    return (ChildUnit->addParentUnit(ParentUnit) && ParentUnit->addChildUnit(ChildUnit));
  }
  else
    throw openfluid::base::OFException("OpenFLUID framework","PluggableFunction::OPENFLUID_AddChildParentConnection","Error adding child-parent connection");
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_RemoveChildParentConnection(openfluid::core::UnitClass_t ClassNameChild,
                                                           openfluid::core::UnitID_t IDChild,
                                                           openfluid::core::UnitClass_t ClassNameParent,
                                                           openfluid::core::UnitID_t IDParent)
{
  openfluid::core::Unit* ChildUnit = mp_CoreData->getUnit(ClassNameChild, IDChild);
  openfluid::core::Unit* ParentUnit = mp_CoreData->getUnit(ClassNameParent, IDParent);

  return OPENFLUID_RemoveChildParentConnection(ChildUnit, ParentUnit);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_RemoveChildParentConnection(openfluid::core::Unit* ChildUnit,
                                                           openfluid::core::Unit* ParentUnit)
{
  if (ChildUnit == NULL || ParentUnit == NULL)
    throw openfluid::base::OFException("OpenFLUID framework","CoreRepository::removeChildParentConnection","Error removing child-parent connection");
  else
    return mp_CoreData->removeChildParentConnection(ChildUnit,ParentUnit);
}


// =====================================================================
// =====================================================================

bool PluggableFunction::OPENFLUID_IsUnitConnectedTo(openfluid::core::Unit* aUnit,
                                                    const openfluid::core::UnitClass_t& ClassNameTo,
                                                    const openfluid::core::UnitID_t& IDTo)
{
  if (aUnit == NULL || !mp_CoreData->isUnitsClassExist(ClassNameTo)) return false;
  return IsUnitIDInPtrList(aUnit->getToUnits(ClassNameTo),IDTo);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsUnitConnectedFrom(openfluid::core::Unit* aUnit,
                                                      const openfluid::core::UnitClass_t& ClassNameFrom,
                                                      const openfluid::core::UnitID_t& IDFrom)
{
  if (aUnit == NULL || !mp_CoreData->isUnitsClassExist(ClassNameFrom)) return false;
  return IsUnitIDInPtrList(aUnit->getFromUnits(ClassNameFrom),IDFrom);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsUnitChildOf(openfluid::core::Unit* aUnit,
                                                const openfluid::core::UnitClass_t& ClassNameParent,
                                                const openfluid::core::UnitID_t& IDParent)
{
  if (aUnit == NULL || !mp_CoreData->isUnitsClassExist(ClassNameParent)) return false;
  return IsUnitIDInPtrList(aUnit->getParentUnits(ClassNameParent),IDParent);
}


// =====================================================================
// =====================================================================


bool PluggableFunction::OPENFLUID_IsUnitParentOf(openfluid::core::Unit* aUnit,
                                                 const openfluid::core::UnitClass_t& ClassNameChild,
                                                 const openfluid::core::UnitID_t& IDChild)
{
  if (aUnit == NULL || !mp_CoreData->isUnitsClassExist(ClassNameChild)) return false;
  return IsUnitIDInPtrList(aUnit->getChildrenUnits(ClassNameChild),IDChild);
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_BuildUnitsMatrix(const openfluid::core::UnitClass_t& UnitsClass,
                                                   const unsigned int& ColsNbr,
                                                   const unsigned int& RowsNbr)
{
  openfluid::core::UnitID_t CurrID = 0;
  openfluid::core::UnitID_t ToID = 0;

  for (unsigned int i=0; i<RowsNbr;i++)
  {
    for (unsigned int j=0; j<ColsNbr;j++)
    {
      CurrID = 1+((ColsNbr*i)+j);
      OPENFLUID_AddUnit(UnitsClass,CurrID,1);
    }
  }

  for (unsigned int i=0; i<RowsNbr;i++)
  {
    for (unsigned int j=0; j<ColsNbr;j++)
    {
      CurrID = 1+((ColsNbr*i)+j);

      if (i == 0)
      {
        // top

        if (j == 0)
        {
          // top-left
          ToID = CurrID+1;
          OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

          ToID = CurrID+ColsNbr;
          OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

        }
        else
        {
          if (j == ColsNbr-1)
          {
            // top-right
            ToID = CurrID-1;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            ToID = CurrID+ColsNbr;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

          }
          else
          {
            // top-center
            ToID = CurrID-1;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            ToID = CurrID+1;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            ToID = CurrID+ColsNbr;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

          }
        }

      }
      else
      {
        if (i == RowsNbr-1)
        {
          // bottom

          if (j == 0)
          {
            // bottom-left
            ToID = CurrID+1;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            ToID = CurrID-ColsNbr;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);
          }
          else
          {
            if (j == ColsNbr-1)
            {
              // bottom-right
              ToID = CurrID-1;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID-ColsNbr;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            }
            else
            {
              // bottom-center
              ToID = CurrID-1;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID+1;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID-ColsNbr;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);
            }
          }

        }
        else
        {
          // middle

          if (j == 0)
          {
            // middle-left
            ToID = CurrID+1;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            ToID = CurrID-ColsNbr;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            ToID = CurrID+ColsNbr;
            OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

          }
          else
          {
            if (j == ColsNbr-1)
            {
              // middle-right
              ToID = CurrID-1;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID-ColsNbr;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID+ColsNbr;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            }
            else
            {
              // middle-center
              ToID = CurrID-1;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID+1;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID-ColsNbr;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

              ToID = CurrID+ColsNbr;
              OPENFLUID_AddFromToConnection(UnitsClass,CurrID,UnitsClass,ToID);

            }
          }


        }
      }
    }
  }

//  throw openfluid::base::OFException("PluggableFunction::OPENFLUID_BuildUnitsMatrix : under construction");

}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_ExportUnitsGraphAsDotFile(const std::string& Filename)
{

  std::ofstream DotFile;
  std::string OutputDir;
  const openfluid::core::UnitsListByClassMap_t* UnitsByClass = mp_CoreData->getUnitsByClass();
  const openfluid::core::UnitsList_t* UnitsList = NULL;
  std::vector<openfluid::core::UnitClass_t> ClassVector;
  openfluid::core::Unit* TheUnit;

  openfluid::core::UnitsListByClassMap_t::const_iterator itUnitsClass;
  openfluid::core::UnitsList_t::const_iterator itUnitsList;

  OPENFLUID_GetRunEnvironment("dir.output",&OutputDir);

  DotFile.open(std::string(OutputDir+"/"+Filename).c_str());

  DotFile << "digraph landscape {" << "\n";
  DotFile << std::endl;
  DotFile << "label = \"Graph representation of the landscape\";" << "\n";
  DotFile << "fontsize = 24;" << "\n";
  DotFile << "\n";


  for (itUnitsClass=UnitsByClass->begin();itUnitsClass!=UnitsByClass->end();++itUnitsClass)
  {
    ClassVector.push_back((*itUnitsClass).first);

    UnitsList=((*itUnitsClass).second).getList();

    for (itUnitsList=UnitsList->begin();itUnitsList!=UnitsList->end();++itUnitsList)
    {
      TheUnit = const_cast<openfluid::core::Unit*>(&(*itUnitsList));
      std::string SrcClassStr = TheUnit->getClass();
      std::string SrcIDStr = "";
      openfluid::tools::ConvertValue(TheUnit->getID(),&SrcIDStr);
      DotFile << "\""+SrcClassStr+" #"+SrcIDStr+"\";" << "\n";
    }

  }

  DotFile << "\n";

  for (itUnitsClass=UnitsByClass->begin();itUnitsClass!=UnitsByClass->end();++itUnitsClass)
  {

    UnitsList=((*itUnitsClass).second).getList();

    for (itUnitsList=UnitsList->begin();itUnitsList!=UnitsList->end();++itUnitsList)
    {
      TheUnit = const_cast<openfluid::core::Unit*>(&(*itUnitsList));
      std::string SrcClassStr = TheUnit->getClass();
      std::string SrcIDStr = "";
      openfluid::tools::ConvertValue(TheUnit->getID(),&SrcIDStr);

      for (unsigned int i=0;i<ClassVector.size();i++)
      {
        const openfluid::core::UnitsPtrList_t* ToUnits = const_cast<openfluid::core::UnitsPtrList_t*>(TheUnit->getToUnits(ClassVector[i]));

        if (ToUnits != NULL)
        {
          std::string DestClassStr = ClassVector[i];
          openfluid::core::UnitsPtrList_t::const_iterator itToUnits;

          for (itToUnits=ToUnits->begin();itToUnits!=ToUnits->end();++itToUnits)
          {
            std::string DestIDStr = "";
            openfluid::tools::ConvertValue((*itToUnits)->getID(),&DestIDStr);

            DotFile << generateDotEdge(SrcClassStr,SrcIDStr,DestClassStr,DestIDStr,"") << "\n";

          }
        }

        const openfluid::core::UnitsPtrList_t* ParentUnits = const_cast<openfluid::core::UnitsPtrList_t*>(TheUnit->getParentUnits(ClassVector[i]));

        if (ParentUnits != NULL)
        {
          std::string DestClassStr = ClassVector[i];
          openfluid::core::UnitsPtrList_t::const_iterator itParentUnits;

          for (itParentUnits=ParentUnits->begin();itParentUnits!=ParentUnits->end();++itParentUnits)
          {
            std::string DestIDStr = "";
            openfluid::tools::ConvertValue((*itParentUnits)->getID(),&DestIDStr);

            DotFile << generateDotEdge(SrcClassStr,SrcIDStr,DestClassStr,DestIDStr,"[arrowhead=odiamond,color=grey,style=dashed]") << "\n";

          }
        }

      }

    }

  }

  DotFile << "\n";
  DotFile << "}" << "\n";

  DotFile.close();
}


// =====================================================================
// =====================================================================


void PluggableFunction::OPENFLUID_SetFunctionMaxThreads(const unsigned int& MaxNumThreads)
{
  if (MaxNumThreads > 0) m_MaxThreads = MaxNumThreads;
}


} } // namespaces
