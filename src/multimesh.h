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
#ifndef PZSCULPTMULTIMESH_H
#define PZSCULPTMULTIMESH_H

#include <QVector>
#include "mesh.h"
#include "subdivider.h"
#include "config.h"

namespace PZSculpt
{

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class MultiMesh : public Drawable
{
   protected:
      Subdivider * m_subdivider;
      int m_current;
      bool m_isMesh;
      QVector<Mesh*> m_meshes;

   public:
      MultiMesh ( Subdivider * subdivider );
      ~MultiMesh();

      void putMesh ( Mesh * mesh );
      void stepUp();
      void stepDown();
      void addLevel();
      void draw();
      QString toString() const;

   public:
      int getCurrent() const {
         return m_current;
      }

      bool isMesh() const {
         return m_isMesh;
      }

      Mesh* getCurrentMesh() {
         if ( ! m_isMesh )
            return 0;
         return m_meshes[m_current];
      }

   protected:
      void deleteAllMeshes();

      void stepUpPassInitDeltas ( Mesh *currentMesh, Mesh *fowardMesh,
                                  QList<Vector3f> & deltas );
      void stepUpPassFacePoints ( Mesh *fowardMesh, QList<Vector3f> & deltas );
      void stepUpPassEdgePoints ( Mesh *fowardMesh, QList<Vector3f> & deltas );
      void stepUpPassOldPoints ( Mesh *fowardMesh, QList<Vector3f> & deltas );
      void stepUpPassDeform ( Mesh *fowardMesh, QList<Vector3f> & deltas );

      QList<Position*> getDiagonals ( Position *pos );

};

}

#endif
