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
  \file QtHelpers.hpp
  \brief Header of ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#ifndef __QTHELPERS_HPP__
#define __QTHELPERS_HPP__


#include <openfluid/tools/GDALHelpers.hpp>

#include <list>

#include <QVariant>
#include <QString>
#include <QStringList>

#include <openfluid/dllexport.hpp>

namespace openfluid { namespace tools {

QString DLLEXPORT toIniCompatible(const std::string& Str);

std::string DLLEXPORT fromIniCompatible(const QVariant& Var);

std::list<std::string> DLLEXPORT toStdStringList(const QStringList& StrList);

/**
  Returns the available GDAL/OGR formats as a QFileDialog formats string.
  The string is built according to GDAL/OGR available drivers.
  The OGRRegisterAll() and/or GDALAllRegister() instruction must be called before using this function.
  @param[in] AllFormatsLabel the label displayed for all formats
  @return the format string (e.g. "All vector files (*.shp *.mif *.tab);;ESRI Shapefiles (*.shp);;Mapinfo (*.mif *.tab)")
*/
QString DLLEXPORT getOGRGDALFormatsForQFileDialogs(const GDALDriversFilesExts_t& Drivers,
                                                   const QString& AllFormatsLabel);

} } // namespaces


#endif /* __QTHELPERS_HPP__ */
