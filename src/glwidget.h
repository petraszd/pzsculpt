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
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLFormat>
#include "multimesh.h"
#include "camera.h"
#include "brush.h"
#include "config.h"
#include "vertexpusher.h"
#include "commandstack.h"
#include "drawcommand.h"

/**
 @author Petras Zdanavičius <petraszd@gmail.com>
*/
namespace PZSculpt
{


class GLWidget : public QGLWidget
{
      Q_OBJECT

   protected:
      enum MouseAction { MA_NONE, MA_TRANSFORM, MA_PAINT, MA_NEGATIVE_PAINT };
      enum MouseTransform { MT_NONE, MT_MOVE, MT_ROTATE, MT_SCALE };

   public:
      GLWidget ( QWidget * parent = 0 );
      ~GLWidget();

   protected:
      Camera * m_camera;
      MultiMesh * m_multiMesh;
      bool m_glInited;

      bool m_mousePressed;
      QPoint m_mousePoint;
      MouseAction m_mouseAction;
      MouseTransform m_mouseTransform;

      Brush * m_brush;
      CommandStack * m_commandStack;
      DrawCommand * m_drawCommand;
      VertexDrawer * m_drawer;
      VertexDrawer * m_pusher;
      VertexDrawer * m_pincher;
      VertexDrawer * m_smoother;

      void paint();
      void paintNegative();

   protected:
      virtual void resizeGL ( int width, int height );
      virtual void initializeGL();
      virtual void paintEvent ( QPaintEvent *event );

      virtual void mouseMoveEvent ( QMouseEvent * event );
      virtual void mousePressEvent ( QMouseEvent * event );
      virtual void mouseReleaseEvent ( QMouseEvent * event );

      virtual void keyPressEvent ( QKeyEvent * event );
      virtual void keyReleaseEvent ( QKeyEvent * event );

      virtual void wheelEvent ( QWheelEvent * event );

      virtual void enterEvent ( QEvent * event );
      virtual void leaveEvent ( QEvent * event );

   private:
      void initDrawCommand();
      void clearDrawCommnad();

      void initMesh ( const QString & fileName );

      void sceneInitGLCalls();
      void sceneDrawGLCalls();

      void emitUndoRedoSignals(){
         emit canUndo( m_commandStack->canUndo() );
         emit canRedo( m_commandStack->canRedo() );
      }

   public slots:
      void openFile();
      void saveFile();
      void undo();
      void redo();
      void subdivide();
      void stepUp();
      void stepDown();
      void setBrushSize ( int size );
      void setBrushStrength ( int strength );
      void setBrushIntencity ( int intencity );
      void setDrawToPusher();
      void setDrawToSmoother();
      void setDrawToPincher();

   signals:
      void canRedo( bool can );
      void canUndo( bool can );
      void meshTextChanged ( const QString & text );

};


}

#endif
