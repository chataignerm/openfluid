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
  \file PluggableModelessExtension.hpp
  \brief Header of ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#ifndef __PLUGGABLEMODELESSEXTENSION_HPP__
#define __PLUGGABLEMODELESSEXTENSION_HPP__

#include <QDialog>
#include <QCloseEvent>

#include <openfluid/builderext/PluggableBuilderExtension.hpp>
#include <openfluid/dllexport.hpp>


namespace openfluid { namespace builderext {

class DLLEXPORT PluggableModelessExtension : public QDialog, public PluggableBuilderExtension
{
  Q_OBJECT;

  signals:

    void fluidxChanged(openfluid::builderext::FluidXUpdateFlags::Flags UpdateFlags =
                         FluidXUpdateFlags::FLUIDX_ALL);


  public slots:

    virtual void update(openfluid::builderext::FluidXUpdateFlags::Flags UpdateFlags);

    virtual void manageSimulationStart();

    virtual void manageSimulationFinish();


  public:

    PluggableModelessExtension():
      QDialog(NULL), PluggableBuilderExtension()
    { }


    ~PluggableModelessExtension()
    { }


    virtual bool initialize()
    { return true; };


    virtual void closeEvent(QCloseEvent *E)
    {
      E->accept();
      done(0);
    }

};

} } // namespaces





#endif /* __PLUGGABLEMODELESSEXTENSION_HPP__ */
