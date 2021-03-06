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
  @file
  @brief Implements the "new simulator" buddy

  @author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */

#include <openfluid/buddies/NewSimBuddy.hpp>

#include <sstream>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <openfluid/base/FrameworkException.hpp>


namespace openfluid { namespace buddies {


NewSimulatorBuddy::NewSimulatorBuddy(openfluid::buddies::BuddiesListener* Listener) :
                  OpenFLUIDBuddy(Listener)
{
  m_RequiredOptionsHelp["simid"] = "ID of the simulator";
  m_RequiredOptionsHelp["cppclass"] = "C++ class name of the simulator";

  m_OtherOptionsHelp["outputdir"] = "path for generated files";
  m_OtherOptionsHelp["authoremail"] = "email(s) of the author(s) of the simulator";
  m_OtherOptionsHelp["authorname"] = "name(s) of the author(s) of the simulator";
}


// =====================================================================
// =====================================================================


NewSimulatorBuddy::~NewSimulatorBuddy()
{

}


// =====================================================================
// =====================================================================

void NewSimulatorBuddy::writeSimulatorCPP()
{
  std::ostringstream CPPContent;
  std::ostringstream SimVersionStr;


  unsigned short Year = (boost::posix_time::second_clock::local_time().date().year() % 100);
  unsigned short Month = (unsigned short)(boost::posix_time::second_clock::local_time().date().month());


  SimVersionStr << Year << ".";
  if (Month < 10) SimVersionStr << "0";
  SimVersionStr << Month;


  CPPContent << "/**" << std::endl;
  CPPContent << "  @file" << std::endl;
  CPPContent << "  @brief Implements " << m_Options["cppclass"] << std::endl;
  CPPContent << "" << std::endl;
  CPPContent << "  @author " << m_Options["authorname"] << " <" << m_Options["authoremail"] << ">" << std::endl;
  CPPContent << " */" << std::endl;
  CPPContent << std::endl;
  CPPContent << "/*" << std::endl;
  CPPContent << "<sim2doc>" << std::endl;
  CPPContent << std::endl;
  CPPContent << "</sim2doc>" << std::endl;
  CPPContent << "*/" << std::endl;
  CPPContent << std::endl;
  CPPContent << "#include <openfluid/ware/PluggableSimulator.hpp>" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "// =====================================================================" << std::endl;
  CPPContent << "// =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "DECLARE_SIMULATOR_PLUGIN" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "BEGIN_SIMULATOR_SIGNATURE(\"" << m_Options["simid"] << "\")" << std::endl;
  CPPContent << std::endl;
  CPPContent << "  DECLARE_NAME(\"\");" << std::endl;
  CPPContent << "  DECLARE_DESCRIPTION(\"\");" << std::endl;
  CPPContent << "" << std::endl;
  CPPContent << "  DECLARE_VERSION(\""+SimVersionStr.str()+"\");" << std::endl;
  CPPContent << "  DECLARE_STATUS(openfluid::ware::EXPERIMENTAL);" << std::endl;
  CPPContent << "" << std::endl;
  CPPContent << "  DECLARE_DOMAIN(\"\");" << std::endl;
  CPPContent << "  DECLARE_PROCESS(\"\");" << std::endl;
  CPPContent << "  DECLARE_METHOD(\"\");" << std::endl;
  CPPContent << "  DECLARE_AUTHOR(\"" << m_Options["authorname"] << "\",\"" << m_Options["authoremail"] << "\");" << std::endl;
  CPPContent << "" << std::endl;
  CPPContent << "END_SIMULATOR_SIGNATURE" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "// =====================================================================" << std::endl;
  CPPContent << "// =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "class " << m_Options["cppclass"] << " : public openfluid::ware::PluggableSimulator" << std::endl;
  CPPContent << "{" << std::endl;
  CPPContent << "  private:" << std::endl;
  CPPContent << std::endl;
  CPPContent << "  public:" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    " << m_Options["cppclass"] << "() : PluggableSimulator()" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    ~" << m_Options["cppclass"] << "()" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    void initParams(const openfluid::ware::WareParams_t& /*Params*/)" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << "" << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    void prepareData()" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    void checkConsistency()" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    openfluid::base::SchedulingRequest initializeRun()" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << std::endl;
  CPPContent << "      return Never();" << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    openfluid::base::SchedulingRequest runStep()" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << std::endl;
  CPPContent << "      return Never();" << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << "    // =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << std::endl;
  CPPContent << "    void finalizeRun()" << std::endl;
  CPPContent << "    {" << std::endl;
  CPPContent << std::endl;
  CPPContent << "    }" << std::endl;
  CPPContent << std::endl;
  CPPContent << "};" << std::endl;
  CPPContent << "" << std::endl;
  CPPContent << "// =====================================================================" << std::endl;
  CPPContent << "// =====================================================================" << std::endl;
  CPPContent << std::endl;
  CPPContent << "DEFINE_SIMULATOR_CLASS(" << m_Options["cppclass"] << ")" << std::endl;
  CPPContent << std::endl;

  std::ofstream OutFile;
  boost::filesystem::path OutFilePath;

  OutFilePath = boost::filesystem::path(m_Options["outputdir"]+"/"+m_Options["cppclass"]+".cpp");
  OutFile.open(OutFilePath.string().c_str(),std::ios::out);
  OutFile << CPPContent.str();
  OutFile.close();

}

// =====================================================================
// =====================================================================


bool NewSimulatorBuddy::run()
{

  setOptionIfNotSet("outputdir",boost::filesystem::current_path().string());

  mp_Listener->onInfo("Simulator ID: " + m_Options["simid"]);
  mp_Listener->onInfo("Simulator  C++ class: " + m_Options["cppclass"]);
  mp_Listener->onInfo("Output directory: " + m_Options["outputdir"]);
  mp_Listener->onInfo("Simulator  filename: " + m_Options["simid"] + ".cpp");
  mp_Listener->onInfo("Author name: " + m_Options["authorname"]);
  mp_Listener->onInfo("Author email: " + m_Options["authoremail"]);

  boost::filesystem::path OutputDirPath(m_Options["outputdir"]);

  if (m_Options["simid"] == "")
      throw openfluid::base::FrameworkException("NewSimulatorBuddy::run()","No simulator ID");

  if (m_Options["cppclass"] == "")
      throw openfluid::base::FrameworkException("NewSimulatorBuddy::run()","No simulator C++ class");


  if (!boost::filesystem::exists(OutputDirPath))
    throw openfluid::base::FrameworkException("NewSimulatorBuddy::run()","Output directory does not exist");



  writeSimulatorCPP();

  return true;
}


} } //namespaces

