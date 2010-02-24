/***copyright>=========================================================

  OpenFLUID - Software environment for modelling Fluxes In Landscapes

  This file is a part of OpenFLUID software
  http://www.umr-lisah.fr/openfluid
  Copyright (c) INRA
  See the file "copyright" for the full license governing this code.

=========================================================<copyright***/


/**
  \if DOCFORDEV
  \file ExecMsgs.h
  \brief Header of class managing execution messages

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
  \endif
*/


#ifndef __EXECMSGS_H__
#define __EXECMSGS_H__

#include <string>
#include <vector>

#include "core/TypeDefs.h"
#include "tools/SwissTools.h"

namespace openfluid { namespace base {

/**
  \if DOCFORDEV
  Class for managin messages during execution

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
  \endif
*/
class ExecutionMessages
{

  private:

    static ExecutionMessages* mp_Singleton;

    bool m_WarningFlag;
    bool m_ErrorFlag;

    std::vector<std::string> m_WarningMsgs;
    std::string m_ErrorMsg;

    unsigned int m_RealWarningsCount;

    void addWarning(std::string Sender, bool IsTimeStep, openfluid::core::TimeStep_t TimeStep, std::string WarningMsg);


    /**
      Constructor
     */
    ExecutionMessages();

  public:

    static ExecutionMessages* getInstance();

    /**
      Destructor
    */
    ~ExecutionMessages();

    void addWarning(std::string Sender, std::string Source, openfluid::core::TimeStep_t TimeStep, std::string WarningMsg) { addWarning(Sender + "," + Source, 1, TimeStep, WarningMsg); };

    void addWarning(std::string Sender, openfluid::core::TimeStep_t TimeStep, std::string WarningMsg) { addWarning(Sender,1,TimeStep,WarningMsg); };

    void addWarning(std::string Sender, std::string Source, std::string WarningMsg) { addWarning(Sender + "," + Source,0,-1,WarningMsg); };

    void addWarning(std::string Sender, std::string WarningMsg) { addWarning(Sender,0,-1,WarningMsg); };

    void resetWarningFlag() { m_WarningFlag = false; };

    bool isWarningFlag() const { return m_WarningFlag; };

    std::vector<std::string> getWarningMsgs() const { return m_WarningMsgs; };

    void doMemRelease() { m_WarningMsgs.clear(); };

    unsigned int getWarningsCount() { return m_RealWarningsCount; };

    static std::string FormatMessage(std::string Message);


};


} } // namespace openfluid::base


#endif /*__EXECMSGS_H__*/

