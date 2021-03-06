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
  \file AppTools.hpp
  \brief Header of ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#ifndef __APPTOOLS_HPP__
#define __APPTOOLS_HPP__

#include <QDateTime>
#include <QColor>

#include <openfluid/core/DateTime.hpp>

#include <QStringList>
#include <string>
#include <vector>
#include <set>


QDateTime convertToQDateTime(openfluid::core::DateTime DT);

QStringList StringVectorToQStringList(const std::vector<std::string>& StrVect);

QStringList StringSetToQStringList(const std::set<std::string>& StrSet);

QStringList StringListToQStringList(const std::list<std::string>& StrSet);

QStringList IntSetToQStringList(const std::set<int>& IntSet);

QString getProjectInfosAsHTML(const QString& ProjectPath, bool IncludeFullPath = false);

QColor getRandomColor();

#endif /* __APPTOOLS_HPP__ */
