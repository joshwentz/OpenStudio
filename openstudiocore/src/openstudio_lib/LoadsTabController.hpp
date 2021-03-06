/**********************************************************************
 *  Copyright (c) 2008-2013, Alliance for Sustainable Energy.  
 *  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef OPENSTUDIO_LOADSTABCONTROLLER_H
#define OPENSTUDIO_LOADSTABCONTROLLER_H

#include <openstudio_lib/MainTabController.hpp>

#include <boost/shared_ptr.hpp>

namespace openstudio {

class LoadsController;

class LoadsTabController : public MainTabController
{
  Q_OBJECT

  public:

    LoadsTabController(bool isIP, const openstudio::model::Model& model);

    virtual ~LoadsTabController();

  private:

    boost::shared_ptr<LoadsController> m_LoadsController;

  public slots:

    void toggleUnits(bool displayIP);
};

} // openstudio

#endif // OPENSTUDIO_LOADSTABCONTROLLER_H
