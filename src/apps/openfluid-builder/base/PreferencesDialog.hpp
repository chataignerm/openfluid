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
  \file PreferencesDialog.hpp
  \brief Header of ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#ifndef __PREFERENCESDIALOG_HPP__
#define __PREFERENCESDIALOG_HPP__

#include "OpenFLUIDDialog.hpp"

#include <QDateTime>


namespace Ui
{
  class PreferencesDialog;
}


class QTreeWidgetItem;
class WaresSearchPathsWidget;


class PreferencesDialog : public OpenFLUIDDialog
{
  Q_OBJECT;

  private slots:

    void changePage(QTreeWidgetItem* Current, QTreeWidgetItem* Previous);

    void updateLanguage(const QString& Lang);

    void clearRecentsList();

    void updateRecentsMax(int Val);

    void confirmItemRemoval(bool Confirm);

    void confirmParamRemoval(bool Confirm);

    void confirmUnitsRemoval(bool Confirm);

    void confirmConnectionsRemoval(bool Confirm);

    void confirmAttributesRemoval(bool Confirm);

    void enableWatchers(bool Active);

    void enableAutoSaveBeforeRun(bool AutoSave);

    void updateWorkspacePath();

    void updateDeltaT(int Val);

    void updatePeriodBegin(const QDateTime& DT);

    void updatePeriodEnd(const QDateTime& DT);

    void addMarketPlace();

    void editMarketPlace();

    void removeMarketPlace();

    void addSimSearchPath();

    void removeSimSearchPath();

    void moveupSimSearchPath();

    void movedownSimSearchPath();

    void addObsSearchPath();

    void removeObsSearchPath();

    void moveupObsSearchPath();

    void movedownObsSearchPath();

    void addBExtSearchPath();

    void removeBExtSearchPath();

    void moveupBExtSearchPath();

    void movedownBExtSearchPath();


  private:

    Ui::PreferencesDialog *ui;

    WaresSearchPathsWidget* mp_SimSearchPaths;
    WaresSearchPathsWidget* mp_ObsSearchPaths;
    WaresSearchPathsWidget* mp_BExtSearchPaths;

    bool m_RecentsChanged;

    bool m_SimPathsChanged;

    bool m_ObsPathsChanged;

    bool m_WaresWatchingChanged;

    void initialize();

    void updateMarketplacesList();

    QStringList extractSearchPath(WaresSearchPathsWidget* W);

    bool addSearchPath(WaresSearchPathsWidget* W);

    bool removeSearchPath(WaresSearchPathsWidget* W);

    bool moveupSearchPath(WaresSearchPathsWidget* W);

    bool movedownSearchPath(WaresSearchPathsWidget* W);

  public:

    PreferencesDialog(QWidget *Parent);

    virtual ~PreferencesDialog();

    bool isRecentsChanged() const { return m_RecentsChanged; }

    bool isSimPathsChanged() const { return m_SimPathsChanged; }

    bool isObsPathsChanged() const { return m_ObsPathsChanged; }

    bool isWaresWatchingChanged() const { return m_WaresWatchingChanged; }


};


#endif /* __PREFERENCESDIALOG_HPP__ */
