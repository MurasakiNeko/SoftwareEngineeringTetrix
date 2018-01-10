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

 #include <QtWidgets>
 #include <random>
 #include <ctime>
 #include "tetrixboard.h"
#include "tetrixcontroller.h"

 TetrixBoard::TetrixBoard(QWidget *parent)
     : QFrame(parent)
 {
	 srand(time(NULL));
     setFrameStyle(QFrame::Panel | QFrame::Sunken);
     setFocusPolicy(Qt::StrongFocus);
	 
     clearBoard();
     //generateNextPieces();
	 m_pCurPiece = nullptr;
     //nextPiece = getNextPiece();
 }

 void TetrixBoard::setNextPieceLabel(QLabel *label)
 {
     nextPieceLabel = label;
 }

 /*
 2015-10-29 新增，用於設定保留方塊的顯示區域
 */
 void TetrixBoard::setHoldPieceLabel(QLabel *label)
 {
     holdPieceLabel = label;
 }

 void TetrixBoard::clearBoard()
 {
     for (int i = 0; i < BoardHeight * BoardWidth; ++i)
         board[i] = NoShape;
 }

 void TetrixBoard::showNextPiece()
 {
     if (!nextPieceLabel)
         return;

     int dx = m_pNextPiece->maxX() - m_pNextPiece->minX() + 1;
     int dy = m_pNextPiece->maxY() - m_pNextPiece->minY() + 1;

     QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
     QPainter painter(&pixmap);
     painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

     for (int i = 0; i < 4; ++i) {
         int x = m_pNextPiece->x(i) - m_pNextPiece->minX();
         int y = m_pNextPiece->y(i) - m_pNextPiece->minY();
         drawSquare(painter, x * squareWidth(), y * squareHeight(),
                    m_pNextPiece->shape());
     }
     nextPieceLabel->setPixmap(pixmap);
 }

 /*
 2015-10-29 顯示保留的方塊
 ( 直接copy TetrixBoard::showNextPiece() 並加以修改 )
 */
 void TetrixBoard::showHoldPiece()
 {
     if(!holdPieceLabel)
         return;
     int dx = m_pHoldPiece->maxX() - m_pHoldPiece->minX() + 1;
     int dy = m_pHoldPiece->maxY() - m_pHoldPiece->minY() + 1;

     QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
     QPainter painter(&pixmap);
     painter.fillRect(pixmap.rect(), holdPieceLabel->palette().background());

     for (int i = 0; i < 4; ++i) {
         int x = m_pHoldPiece->x(i) - m_pHoldPiece->minX();
         int y = m_pHoldPiece->y(i) - m_pHoldPiece->minY();
         drawSquare(painter, x * squareWidth(), y * squareHeight(),
                    m_pHoldPiece->shape());
     }
     holdPieceLabel->setPixmap(pixmap);
 }

 void TetrixBoard::keyPressEvent(QKeyEvent *event)
 {
	 //MessageBox(nullptr, LPCWSTR("1234xxx"), 0, 0);
	 m_pController->keyPressEvent(event);
 }

 void TetrixBoard::paintEvent(QPaintEvent *event)
 {
	 QFrame::paintEvent(event);
	 if (!m_pCurPiece)
		 return;
	 QPainter painter(this);
	 QRect rect = contentsRect();

	/* if (isPaused) {
		 painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
		 return;
	 }*/

	 int boardTop = rect.bottom() - BoardHeight * squareHeight();

	 for (int i = 0; i < BoardHeight; ++i) {
		 for (int j = 0; j < BoardWidth; ++j) {
			 TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
			 if (shape != NoShape)
				 drawSquare(painter, rect.left() + j * squareWidth(),
					 boardTop + i * squareHeight(), shape);
		 }
	 }

	 if (m_pCurPiece->shape() != NoShape) {
		 int minDstY = 200; // 4個點中，能畫的Y長度之最小值
		 for (int i = 0; i < 4; ++i) {
			 int x = m_pCurPiece->curX + m_pCurPiece->x(i);
			 int y = m_pCurPiece->curY - m_pCurPiece->y(i);
			 if (y - 1 >= 0 && shapeAt(x, y - 1) != NoShape) //下一個位置跟自身重疊
				 continue;
			 while (y >= 0 && shapeAt(x, y) == NoShape) //持續尋找不重疊之位置
				 --y;
			 minDstY = qMin(minDstY, (m_pCurPiece->curY - m_pCurPiece->y(i) - y)); //紀錄 (注意 y 越小表示越低，但是繪圖時y值越大表示越低)
		 }

		 for (int i = 0; i < 4; ++i) {
			 int x = m_pCurPiece->curX + m_pCurPiece->x(i);
			 int y = m_pCurPiece->curY - m_pCurPiece->y(i);
			 drawSquare(painter, rect.left() + x * squareWidth(),
				 boardTop + (BoardHeight - y - 1) * squareHeight(),
				 m_pCurPiece->shape());
			 if (minDstY <= 4)
				 continue;
			 /*在可能的最低點繪出影子*/
			 drawSquare(painter, rect.left() + x * squareWidth(),
				 boardTop + (BoardHeight - (y + 2 - minDstY)) * squareHeight(),
				 m_pCurPiece->shape());
		 }
	 }
 }

 void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
 {
     static const QRgb colorTable[8] = {
         0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
         0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
     };

     QColor color = colorTable[int(shape)];
     painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                      color);

     painter.setPen(color.light());
     painter.drawLine(x, y + squareHeight() - 1, x, y);
     painter.drawLine(x, y, x + squareWidth() - 1, y);

     painter.setPen(color.dark());
     painter.drawLine(x + 1, y + squareHeight() - 1,
                      x + squareWidth() - 1, y + squareHeight() - 1);
     painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                      x + squareWidth() - 1, y + 1);
 }

 /*
 2015-10-30 畫出掉落虛線 -- 覺得不太需要
 */
 void TetrixBoard::drawShader(QPainter &painter, int x, int y, int dx, int dy, TetrixShape shape)
 {
     shape = NoShape;
     static const QRgb colorTable[8] = {
         0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
         0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
     };
     QColor color = colorTable[int(shape)];

     painter.setPen(color.black());
     painter.drawLine(x, y + squareHeight() - 1, dx, dy);
     painter.drawLine(x + squareWidth() - 1, y, dx + squareWidth() - 1, dy);
     painter.drawLine(x, dy, x + squareWidth() - 1, dy);
 }
