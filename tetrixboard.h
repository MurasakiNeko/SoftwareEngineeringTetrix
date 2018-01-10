/****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
 **     the names of its contributors may be used to endorse or promote
 **     products derived from this software without specific prior written
 **     permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #ifndef TETRIXBOARD_H
 #define TETRIXBOARD_H

 #include <QBasicTimer>
 #include <QFrame>
 #include <QPointer>

 #include "tetrixpiece.h"
 #include "tetrixoperationcode.h"

 class QLabel;
 class TetrixController;

 class TetrixBoard : public QFrame
 {
     Q_OBJECT

 public:
     TetrixBoard(QWidget *parent = 0);
	 TetrixController* m_pController;

     void setNextPieceLabel(QLabel *label);
     void setHoldPieceLabel(QLabel *label);

 protected:
	 void keyPressEvent(QKeyEvent *event);

 signals:
     void scoreChanged(int score);
     void levelChanged(int level);
     void linesRemovedChanged(int numLines);
	 void sendBoardAction(int, int, int);

 public:
     const static int MAX_SHAPES = 7;
     enum { BoardWidth = 10, BoardHeight = 22 };

     TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
     int squareWidth() { return contentsRect().width() / BoardWidth; }
     int squareHeight() { return contentsRect().height() / BoardHeight; }

     void clearBoard();
     void showNextPiece();
     void showHoldPiece();// 10-29 顯示保留的方塊

     void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);
     void drawShader(QPainter &painter, int x, int y, int dx, int dy, TetrixShape shape); //10-30 沒什麼用，單純畫出虛線
	 void paintEvent(QPaintEvent *event);

     QPointer<QLabel> nextPieceLabel, holdPieceLabel;
     TetrixPiece* m_pCurPiece, * m_pNextPiece, * m_pHoldPiece; // 10-29 保留之方塊
     TetrixShape board[BoardWidth * BoardHeight];
 };

 #endif
