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
 \file AdvancedModelDescriptor.hpp
 \brief Header of ...

 \author Aline LIBRES <aline.libres@gmail.com>
 */

#ifndef ADVANCEDMODELDESCRIPTOR_HPP_
#define ADVANCEDMODELDESCRIPTOR_HPP_

#include <openfluid/fluidx/CoupledModelDescriptor.hpp>
#include <openfluid/dllexport.hpp>


namespace openfluid {
namespace fluidx {

class DLLEXPORT AdvancedModelDescriptor
{
  protected:

    openfluid::fluidx::CoupledModelDescriptor* mp_ModelDesc;

    AdvancedModelDescriptor()
    {
    }

  public:

    AdvancedModelDescriptor(
        openfluid::fluidx::CoupledModelDescriptor& ModelDesc);

    ~AdvancedModelDescriptor();

    void checkModel() const;

    const std::list<openfluid::fluidx::ModelItemDescriptor*>& getItems() const;

    /**
     * @throw openfluid::base::OFException if Index is out of range
     * @param Index
     * @return
     */
    openfluid::fluidx::ModelItemDescriptor* getItemAt(unsigned int Index) const;

    /**
     * Return the position of the firts Item with ItemID found in the list, or -1 if not found
     * @param ItemID
     * @return
     */
    int getFirstItemIndex(std::string ItemID) const;

    int getFirstItemIndex(openfluid::fluidx::ModelItemDescriptor* Item) const;

    std::vector<std::string> getOrderedIDs() const;

    std::string getID(openfluid::fluidx::ModelItemDescriptor* Item) const;

    void appendItem(openfluid::fluidx::ModelItemDescriptor* Item);

    /**
     Insert an Item before the given position (positions starts at index 0)
     @param[in] Item the ModelItemDescriptor to insert
     @param[in] Position the position, should be between zero and list size - 1.
     To insert an Item at the end of the list, use appendItem instead.
     @throw openfluid::base::OFException if Position is out of range
     */
    void insertItem(openfluid::fluidx::ModelItemDescriptor* Item,
                    unsigned int Position);

    /**
     * @brief Replace existing simulators with SimulatorsList
     */
    void setItems(
        std::list<openfluid::fluidx::ModelItemDescriptor*> SimulatorsList);

    /**
     Remove from the list the Item located at the given Position (positions starts at index 0).
     This doesn't delete the ModelItemDescriptor pointer.
     @param[in] Position the position
     @throw openfluid::base::OFException if Position is out of range
     */
    void removeItem(unsigned int Position);

    /**
     * Move the Item located at the given From position to the To position (positions starts at index 0)
     * @param From
     * @param To
     * @throw openfluid::base::OFException a position is out of range
     */
    void moveItem(unsigned int From, unsigned int To);

    unsigned int getItemsCount() const;

    void getItemsCount(unsigned int& SimCount, unsigned int& GenCount) const;

    void setGlobalParameter(const openfluid::ware::WareParamKey_t& Key,
                            const openfluid::ware::WareParamValue_t& Value);

    void setGlobalParameters(const openfluid::ware::WareParams_t& Params);

    openfluid::ware::WareParams_t getGlobalParameters() const;

    void eraseGlobalParameter(const openfluid::ware::WareParamKey_t& Key);
};

}
} // namespaces
#endif /* ADVANCEDMODELDESCRIPTOR_HPP_ */
