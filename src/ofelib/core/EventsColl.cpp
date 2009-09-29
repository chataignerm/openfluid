/***copyright>=========================================================

  OpenFLUID - Software environment for modelling Fluxes In Landscapes

  This file is a part of OpenFLUID software
  http://www.umr-lisah.fr/openfluid
  Copyright (c) INRA
  See the file "copyright" for the full license governing this code.

=========================================================<copyright***/


/**
  \file EventsColl.cpp
  \brief Implements distributed event collection management class

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/

#include "EventsColl.h"
#include <iostream>

namespace openfluid { namespace core
{



EventsCollection::EventsCollection()
{
}


// =====================================================================
// =====================================================================


EventsCollection::~EventsCollection()
{
}


// =====================================================================
// =====================================================================


bool EventsCollection::addEvent(Event* Ev)
{


  // empty list
  if (m_Events.size() == 0)
  {
    m_Events.push_back(Ev);
  }
  else
  {
    // event date is before first collection item
    if (m_Events.front()->getDateTime() >= Ev->getDateTime())
    {
      m_Events.push_front(Ev);
    }
    else
    {
      // event date is after last collection item
      if (m_Events.back()->getDateTime() <= Ev->getDateTime())
      {
        m_Events.push_back(Ev);
      }
      else
      {
        // event has to be inserted somewhere in the collection
        std::list<Event*>::iterator DEiter;

        for(DEiter=m_Events.begin(); DEiter != m_Events.end(); ++DEiter)
        {
          if ((*DEiter)->getDateTime() >= Ev->getDateTime())
          {
            m_Events.insert(--DEiter,Ev);
            return true;
          }
        }

      }
    }
  }

  return true;
}


// =====================================================================
// =====================================================================


bool EventsCollection::getEventsBetween(const DateTime BeginDate, const DateTime EndDate,
    EventsCollection *Events)
{

  std::list<Event*>::iterator DEiter;

  for(DEiter=m_Events.begin(); DEiter != m_Events.end(); ++DEiter)
  {
    if ((*DEiter)->getDateTime().isBetween(BeginDate,EndDate))
    {
      Events->addEvent(*DEiter);
    }
  }

  return true;
}


// =====================================================================
// =====================================================================


void EventsCollection::println()
{
  std::list<Event*>::iterator DEiter;

    for(DEiter=m_Events.begin(); DEiter != m_Events.end(); ++DEiter)
    {
      (*DEiter)->println();
    }
}


} }  // namespaces

