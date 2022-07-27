/***************************************************************************
 *   Copyright (C) 2008 by Petras Zdanavičius                              *
 *   petraszd@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef PZSCULPTDRAWCOMMAND_H
#define PZSCULPTDRAWCOMMAND_H

#include <QList>
#include "command.h"
#include "drawcommandelem.h"

namespace PZSculpt
{

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class DrawCommand : public Command
{

   protected:
      QList<DrawCommandElem* > m_elems;

   public:
      DrawCommand();
      virtual ~DrawCommand();

      void insert( Position * position, const Vector3f & delta );

      virtual void undo();
      virtual void redo();

      int effected(){
         return m_elems.size();
      }
};

}

#endif
