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
//TODO: no magic number would be nice.
#include <QFile>
#include <QList>
#include "glwidget.h"
#include "objmeshimporter.h"
#include "objmeshexporter.h"
#include "catmullclarksubd.h"
#include "vertexpusher.h"
#include "vertexpincher.h"
#include "vertexsmoother.h"

namespace PZSculpt
{


GLWidget::GLWidget ( QWidget * parent )
      : QGLWidget ( parent )
{
   m_camera = new Camera ( 35.0f, 1.0f, 1.0f, 1000.0f, 1.0f );
   m_multiMesh = new MultiMesh ( new CatmullClarkSubd() );

   m_mousePoint = QPoint ( 0, 0 );
   m_mousePressed = false;
   m_mouseAction = MA_PAINT;
   m_mouseTransform = MT_NONE;

   m_glInited = false;

   m_brush = new Brush ( false,
                         STARTING_BRUSH_SIZE,
                         STARTING_BRUSH_STRENGTH,
                         STARTING_BRUSH_INTENCITY );

   m_pusher = new VertexPusher();
   m_pincher = new VertexPincher();
   m_smoother = new VertexSmoother();

   m_drawer = m_pusher;

   m_commandStack = new CommandStack ( 15 ); //TODO: MAGIC NUMBER
   m_drawCommand = 0;

   setFocus();
   setAutoFillBackground ( false );
   setMouseTracking ( true );
}


GLWidget::~GLWidget()
{
   delete m_camera;
   delete m_multiMesh;
   delete m_brush;
   delete m_pusher;
   delete m_pincher;
   delete m_smoother;
   clearDrawCommnad();
   delete m_commandStack;
}


void GLWidget::initMesh ( const QString & fileName )
{
   QFile file ( fileName );
   file.open ( QIODevice::ReadOnly );

   ObjMeshImporter importer;
   QTextStream stream ( &file );
   Mesh * mesh = importer.import ( stream );

   m_multiMesh->putMesh ( mesh );

   file.close();
}


void GLWidget::sceneInitGLCalls()
{
   //TODO: No. No. Mommy, help me. Magic numbers all around me...
   if ( m_glInited )
      return;

   qglClearColor ( QColor ( 100, 100, 100 ) );
   qglColor ( QColor ( 200, 170, 100 ) );

   glShadeModel ( GL_SMOOTH );

   glEnable ( GL_CULL_FACE );
   glCullFace ( GL_BACK );

   glEnable ( GL_DEPTH_TEST );
   glEnable ( GL_BLEND );

   glEnable ( GL_COLOR_MATERIAL );
   glColorMaterial ( GL_FRONT, GL_DIFFUSE );
   glEnable ( GL_BLEND );
   glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

   glEnable ( GL_LIGHTING );

   GLfloat light0Diffuse[] = { 0.4, 0.4, 0.4, 0.0 };
   GLfloat light0Position[] = { 0.0, 0.0, 1.0, 0.0 };

   glLightfv ( GL_LIGHT0, GL_DIFFUSE, light0Diffuse );
   glLightfv ( GL_LIGHT0, GL_POSITION, light0Position );

   glEnable ( GL_LIGHT0 );

   GLfloat light1Diffuse[] = { 0.6, 0.6, 0.6, 0.0 };
   GLfloat light1Position[] = { 1.0, 0.0, 1.0, 0.0 };

   glLightfv ( GL_LIGHT1, GL_DIFFUSE, light1Diffuse );
   glLightfv ( GL_LIGHT1, GL_POSITION, light1Position );

   glEnable ( GL_LIGHT1 );

   m_glInited = true;
}


void GLWidget::initDrawCommand()
{
   m_drawCommand = new DrawCommand();
}


void GLWidget::clearDrawCommnad()
{
   if ( m_drawCommand == 0 )
      return;

   if ( m_drawCommand->effected() > 0 ) {
      m_commandStack->push ( m_drawCommand );
      m_drawCommand = 0;
      emitUndoRedoSignals();
   }

   delete m_drawCommand;
   m_drawCommand = 0;
}


void GLWidget::sceneDrawGLCalls()
{
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   m_multiMesh->draw();
}


void GLWidget::initializeGL()
{
}


void GLWidget::paintEvent ( QPaintEvent *event )
{
   Q_UNUSED ( event );

   sceneInitGLCalls();
   sceneDrawGLCalls();

   QPainter painter;
   painter.begin ( this );
   painter.setRenderHint ( QPainter::Antialiasing, true );
   painter.scale ( 1.0, -1.0 );
   painter.translate ( 0, -height() );

   m_brush->drawCursor ( painter );
   painter.end();
}


void GLWidget::resizeGL ( int width, int height )
{
   m_camera->resizeEvent ( width, height );
   m_camera->apply();
}


void GLWidget::mousePressEvent ( QMouseEvent * event )
{
   switch ( event->button() ) {
      case Qt::LeftButton:
         m_mouseTransform = MT_ROTATE;
         break;
      case Qt::MidButton:
         m_mouseTransform = MT_MOVE;
         break;
      case Qt::RightButton:
         m_mouseTransform = MT_SCALE;
      default:
         break;
   }

   initDrawCommand();

   m_mousePressed = true;
   m_mousePoint = event->pos();
}


void GLWidget::mouseReleaseEvent ( QMouseEvent * event )
{
   Q_UNUSED ( event );
   clearDrawCommnad();
   m_mousePressed = false;
}


void GLWidget::mouseMoveEvent ( QMouseEvent * event )
{
//   if ( !m_mousePressed )
//      return;

   if ( m_mousePressed && m_multiMesh->isMesh() ) {
      GLfloat deltaX = event->x() - m_mousePoint.x();
      GLfloat deltaY = event->y() - m_mousePoint.y() ;

      switch ( m_mouseAction ) {
         case MA_TRANSFORM:
            switch ( m_mouseTransform ) {
               case MT_MOVE:
                  m_camera->move ( deltaX / GLfloat ( width() ),
                                   deltaY / GLfloat ( height() ) );
                  break;
               case MT_ROTATE:
                  m_camera->rotateHorizontal ( deltaX );
                  m_camera->rotateVertical ( deltaY );
                  break;
               case MT_SCALE:
                  m_camera->zoom ( ( deltaX + deltaY ) / 2000.0f ); //TODO: MAGIC NUMBER
                  break;
               default:
                  break;
            }
            break;
         case MA_NEGATIVE_PAINT:
            m_brush->setAligment ( Brush::BA_NEGATIVE );
            paint();
            break;
         case MA_PAINT:
            m_brush->setAligment ( Brush::BA_POSITIVE );
            paint();
            break;
         default:
            break;
      }
   }

   m_mousePoint = event->pos();
   m_brush->setX ( m_mousePoint.x() );
   m_brush->setY ( height() - m_mousePoint.y() );
   event->ignore();
   repaint();
}


void GLWidget::paint()
{
   if ( !m_multiMesh->isMesh() )
      return;

   Mesh * mesh = m_multiMesh->getCurrentMesh();
   m_brush->drawOnMesh ( m_drawer, mesh, m_camera, m_drawCommand );
}


void GLWidget::keyPressEvent ( QKeyEvent * event )
{
   switch ( event->key() ) {
      case Qt::Key_Shift:
         m_mouseAction = MA_TRANSFORM;
         break;
      case Qt::Key_Control:
         m_mouseAction = MA_NEGATIVE_PAINT;
         break;
      default:
         m_mouseAction = MA_PAINT;
         event->ignore();
   }
}


void GLWidget::keyReleaseEvent ( QKeyEvent * event )
{
   m_mouseAction = MA_PAINT;
   event->ignore();
}


void GLWidget::wheelEvent ( QWheelEvent * event )
{
   m_camera->zoom ( -event->delta() / 1000.0f );//TODO: MAGIC NUMBER
   repaint();
}


void GLWidget::enterEvent ( QEvent * event )
{
   Q_UNUSED ( event );
   grabKeyboard ();
   m_brush->setVisible ( true );
   repaint();
}


void GLWidget::leaveEvent ( QEvent * event )
{
   Q_UNUSED ( event );
   releaseKeyboard ();
   m_brush->setVisible ( false );
   repaint();
}


void GLWidget::openFile()
{
   QString fileName = QFileDialog::getOpenFileName (
                         this,
                         "Open 3D object",
                         "",
                         tr ( "Image Files (*.obj *.OBJ)" ) );

   if ( fileName == "" )
      return;

   m_commandStack->clear();
   emitUndoRedoSignals();

   initMesh ( fileName );

   GLfloat radius;
   Vector3f stareAt;

   m_multiMesh->getCurrentMesh()->getMetrics ( stareAt, radius );
   m_pusher->setScale ( radius / 100.0 );
   m_pincher->setScale ( radius / 100.0 );
   m_smoother->setScale ( radius / 100.0 );

   m_camera->setRadius ( 6.0f * radius );
   m_camera->setVerticalRotate ( 0.0f );
   m_camera->setHorizontalRotate ( 0.0f );
   m_camera->setStarePoint ( stareAt );
   m_camera->apply();

   emit meshTextChanged ( m_multiMesh->toString() );
   repaint();
}


void GLWidget::saveFile()
{
   if ( ! m_multiMesh->isMesh() )
      return;

   QFileDialog dialog ( this, tr ( "Save File As..." ), "", "( *.obj *.OBJ )" );
   dialog.setFileMode ( QFileDialog::AnyFile );
   dialog.setAcceptMode ( QFileDialog::AcceptSave );

   QStringList fileNames;
   if ( dialog.exec() )
      fileNames = dialog.selectedFiles();

   Mesh * mesh = m_multiMesh->getCurrentMesh();

   for ( int i = 0; i < fileNames.size(); ++i ) {
      QFile file ( fileNames[i] );
      file.open ( QIODevice::WriteOnly );

      ObjMeshExporter exporter;
      QTextStream stream ( &file );
      exporter.save ( stream, *mesh );

      file.close();
   }
}


void GLWidget::undo()
{
   m_commandStack->undo();
   emitUndoRedoSignals();
   m_multiMesh->getCurrentMesh()->recalculateNormalAll();
   repaint();
}


void GLWidget::redo()
{
   m_commandStack->redo();
   emitUndoRedoSignals();
   m_multiMesh->getCurrentMesh()->recalculateNormalAll();
   repaint();
}


void GLWidget::subdivide()
{
   m_multiMesh->addLevel();
   m_commandStack->clear();
   emitUndoRedoSignals();
   emit meshTextChanged ( m_multiMesh->toString() );
   repaint();
}


void GLWidget::stepUp()
{
   m_multiMesh->stepUp();
   m_commandStack->clear();
   emitUndoRedoSignals();
   emit meshTextChanged ( m_multiMesh->toString() );
   repaint();
}


void GLWidget::stepDown()
{
   m_multiMesh->stepDown();
   m_commandStack->clear();
   emitUndoRedoSignals();
   emit meshTextChanged ( m_multiMesh->toString() );
   repaint();
}


void GLWidget::setBrushSize ( int size )
{
   m_brush->setSize ( size );
}


void GLWidget::setBrushStrength ( int strength )
{
   m_brush->setStrength ( strength );
}


void GLWidget::setBrushIntencity ( int intencity )
{
   m_brush->setIntencity ( intencity );
}


void GLWidget::setDrawToPusher()
{
   m_drawer = m_pusher;
}


void GLWidget::setDrawToSmoother()
{
   m_drawer = m_smoother;
}


void GLWidget::setDrawToPincher()
{
   m_drawer = m_pincher;
}


}
