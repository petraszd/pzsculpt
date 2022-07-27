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
//TODO: pasalinti magic numbers
#ifndef PZSCULPTCAMERA_H
#define PZSCULPTCAMERA_H

#include "vector3.h"

namespace PZSculpt
{

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
class Camera
{
   protected:
      GLfloat m_fov;
      GLfloat m_ratio;
      GLfloat m_nearClippingPlane;
      GLfloat m_farClippingPlane;
      Vector3f m_starePoint;
      GLfloat m_radius;

      GLfloat m_horizontalRotate;
      GLfloat m_verticalRotate;
      GLfloat m_upY;

      GLint m_viewport[4];
      GLdouble m_projectionMatrix[16];
      GLdouble m_modelviewMatrix[16];

   public:
      Camera ( GLfloat fov = 45.0f,
               GLfloat ratio = 1.0f,
               GLfloat nearPlane = 1.0f,
               GLfloat farPlane = 1000.0f,
               GLfloat radius = 1.0f );

      virtual ~Camera();

      void rotateVertical ( GLfloat degree );
      void rotateHorizontal ( GLfloat degree );
      void move ( GLfloat horizontal, GLfloat vertical );
      void zoom ( GLfloat percent );
      void apply();
      void resizeEvent ( uint width, uint height );
      Vector3f projectOnScreen ( const Vector3f & vector ) const;
      Vector3f projectOnScreen ( Vector3f * vectorPtr ) const;
      void projectOnScreen ( const Vector3f & vector,
                             GLdouble & x, GLdouble & y ) const;
      void projectOnScreen ( Vector3f * vectorPtr,
                             GLdouble & x, GLdouble & y ) const;

      Vector3f projectInSpace ( const Vector3f & vector ) const;

      Vector3f getLookFrom() const {
         return m_starePoint + facingVector() * m_radius;
      }


      Vector3f getLookAt() const {
         return getStarePoint();
      }

   public:
      GLfloat getFov() const {
         return m_fov;
      }

      void setFov ( GLfloat fov ) {
         if ( fov > 0.0f && fov < 90.0f )
            m_fov = fov;
      }

      GLfloat getRatio() const {
         return m_ratio;
      }

      void setRatio ( GLfloat ratio ) {
         if ( ratio > 0.0f )
            m_ratio = ratio;
      }

      GLfloat getNearClippingPlane() const {
         return m_nearClippingPlane;
      }

      void setNearClippingPlane ( GLfloat nearPlane ) {
         if ( nearPlane > 0.0f && nearPlane < m_farClippingPlane )
            m_nearClippingPlane = nearPlane;
      }

      GLfloat getFarClippingPlane() const {
         return m_farClippingPlane;
      }

      void setFarClippingPlane ( GLfloat farPlane ) {
         if ( farPlane > 0.0f && farPlane > m_farClippingPlane )
            m_farClippingPlane = farPlane;
      }

      void setClippingPlanes ( GLfloat nearPlane, GLfloat farPlane ) {
         if ( nearPlane > 0.0f && farPlane > nearPlane ) {
            m_nearClippingPlane = nearPlane;
            m_farClippingPlane = farPlane;
         }
      }

      GLfloat getRadius() const {
         return m_radius;
      }

      void setRadius ( GLfloat radius ) {
         if ( radius > 0.0f )
            m_radius = radius;
      }

      GLfloat getHorizontalRotate() const {
         return m_horizontalRotate;
      }

      void setHorizontalRotate ( GLfloat horizontalRotate ) {
         m_horizontalRotate = horizontalRotate;
      }

      GLfloat getVerticalRotate() const {
         return m_verticalRotate;
      }

      void setVerticalRotate ( GLfloat verticalRotate ) {
         m_verticalRotate = verticalRotate;
      }

      Vector3f getStarePoint() const {
         return m_starePoint;
      }

      void setStarePoint ( const Vector3f & starePoint ) {
         m_starePoint = starePoint;
      }

   protected:
      Vector3f facingVector() const;
      void fillGLMatrixes();
};

}

#endif
