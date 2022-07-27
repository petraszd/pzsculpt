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
#ifndef PZSCULPTBRUSH_H
#define PZSCULPTBRUSH_H

#include <QPainter>
#include <QPoint>
#include <QList>
#include <QHash>
#include <QSet>
#include "config.h"
#include "mesh.h"
#include "camera.h"
#include "vertexdrawerelem.h"
#include "vertexdrawer.h"
#include "drawcommand.h"

namespace PZSculpt
{

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class Brush
{
   public:
      enum BrushAligment { BA_NEGATIVE = -1, BA_POSITIVE = 1 };

   protected:
      bool m_visible;
      int m_size;
      int m_strength;   //Must be in range 0..100]
      int m_intencity;  //Must be in range 0..100]
      BrushAligment m_aligment;
      int m_x;
      int m_y;

      //Requared for calculations
      Mesh * m_tempMesh;
      Camera * m_tempCamera;
      Vector3f m_tempBrush3DPos;
      Vector3f m_tempCamDir;
      Vector3f m_tempEyePos;
      GLfloat m_temp3DRadius;
      Face * m_tempCentral;
   public:
      Brush ( bool visible = true,
              int size = 100,
              int strength = 50,
              int intencity = 25,
              BrushAligment aligment = BA_POSITIVE );
      virtual ~Brush();

      virtual void drawCursor ( QPainter & painter );
      void drawOnMesh ( VertexDrawer *drawer,
                        Mesh * mesh,
                        Camera * camera,
                        DrawCommand * command );
      bool isNear ( int x, int y );

   protected:
      void parseFaces ( Face *face,
                        QSet<Face*> & faces,
                        QHash<int, VertexDrawerElem*> & hash );
      Face * findNearestFace ();
      int isPointInPoly ( int npol, double *xp, double *yp, double x, double y );
      void transformBrushTo3D();

      GLfloat calcIntensity ( GLfloat length );

   public:
      void setVisible ( bool visible ) {
         m_visible = visible;
      }


      bool getVisible () const {
         return m_visible;
      }


      void setSize ( int size ) {
         m_size = qAbs ( size );
      }


      void setStrength ( int strength ) {
         if ( strength > 0 && strength < 100 )
            m_strength = strength;
      }


      void setIntencity ( int intencity ) {
         if ( intencity > 0 && intencity < 100 )
            m_intencity = intencity;
      }


      int getX() const {
         return m_x;
      }


      void setX ( int x ) {
         m_x = x;
      }


      int getY() const {
         return m_y;
      }


      void setY ( int y ) {
         m_y = y;
      }


      void setPlace ( const QPoint & point ) {
         m_x = point.x();
         m_y = point.y();
      }


      void setAligment ( BrushAligment aligment ) {
         m_aligment = aligment;
      }


      int getAligment() const {
         return int ( m_aligment );
      }
};

}

#endif
