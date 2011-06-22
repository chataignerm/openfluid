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
  \file RunDescriptor.h
  \brief Header of ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#ifndef __RUNDESCRIPTOR_H__
#define __RUNDESCRIPTOR_H__

#include "openfluid-core.h"

class RunDescriptor
{
  private:
    int m_DeltaT;

    std::string m_SimID;

    openfluid::core::DateTime m_BeginDate;
    openfluid::core::DateTime m_EndDate;

    unsigned int m_ProgOutPacket;
    unsigned int m_ProgOutKeep;


  public:

    RunDescriptor();

    RunDescriptor(int DeltaT,
                  openfluid::core::DateTime BeginDate,openfluid::core::DateTime EndDate);

    ~RunDescriptor();

    openfluid::core::DateTime getBeginDate() const {return m_BeginDate; };

    void setBeginDate(const openfluid::core::DateTime BeginDate) { m_BeginDate = BeginDate; };

    openfluid::core::DateTime getEndDate() const {return m_EndDate; };

    void setEndDate(const openfluid::core::DateTime EndDate) { m_EndDate = EndDate; };

    int getDeltaT() const {return m_DeltaT; };

    void setDeltaT(const int DeltaT) { m_DeltaT = DeltaT; };

    void setSimulationID(const std::string SimID) { m_SimID = SimID; };

    std::string getSimulationID() const { return m_SimID; };

    bool isSimulationID() const { return (m_SimID != ""); };

    void setProgressiveOutput(const unsigned int Packet, const unsigned int Keep);

    bool isProgressiveOutput() const;

    unsigned int getProgressiveOutputPacket() const { return m_ProgOutPacket; };

    unsigned int getProgressiveOutputKeep() const { return m_ProgOutKeep; };


};

#endif /* __RUNDESCRIPTOR_H__ */