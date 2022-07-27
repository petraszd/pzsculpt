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
#ifndef PZSCULPTCATMULLCLARKSUBD_H
#define PZSCULPTCATMULLCLARKSUBD_H

#include <QHash>
#include <QList>
#include <QString>
#include <subdivider.h>
#include "face.h"
#include "config.h"

namespace PZSculpt
{


/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class CatmullClarkSubd : public Subdivider
{
   protected:
      enum consts { NO_VERTEX = -1};

   public:
      CatmullClarkSubd();
      ~CatmullClarkSubd();

      Mesh* subdivide ( Mesh & oldMesh );

   protected:
      Mesh * m_newMesh;
      Mesh * m_oldMesh;
      int m_level;

      QList<int> * m_facePoints;
      QHash<uint, int> * m_edgesPoints;
      QHash<int, bool> * m_cornerVertexes;
      QHash<int, int> * m_neighbourVertexes;
      QHash<int, int> * m_nearFaces;

   protected:
      void initContainers();
      void zeroContainers();

      void copyVertexes ();
      void generateFacePoints ();
      void generateEdgePoints ();
      void createFaces ();
      void repositionOldVertex();

      inline int getEdgeKey ( int one, int two );
      void fillEdgesHash ( QHash<uint, int*> & hash,
                           int face,
                           int edgeOne,
                           int edgeTwo );

      int makeFaceTexture ( Face * face );
      int makeEdgeTexture ( Face * face, int edgePoint0, int edgePoint1 );
};


}

#endif
