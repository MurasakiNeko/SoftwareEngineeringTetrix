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
#include <Windows.h>
#include "TetrixController.h"

TetrixController::TetrixController(QWidget *parent, TetrixBoard* pBoard)
	: QFrame(parent), m_pBoard(pBoard)
{
	srand(time(NULL));
	setFrameStyle(QFrame::Panel | QFrame::Sunken);
	setFocusPolicy(Qt::StrongFocus);
	m_bIsStarted = false;
	m_bIsPaused = false;
	m_bIsControllable = true;
	m_pBoard->clearBoard();
	generateNextPieces();
	m_pNextPiece = getNextPiece();
	//m_pBoard->nextPiece = nextPiece;
}

void TetrixController::start()
{
	if (m_bIsPaused)
		return;

	m_bIsStarted = true;
	m_bIsWaitingAfterLine = false;
	m_nLinesRemoved = 0;
	m_nPiecesDropped = 0;
	m_nScore = 0;
	m_nLevel = 1;
	m_pBoard->clearBoard();

	emit m_pBoard->linesRemovedChanged(m_nLinesRemoved);
	emit m_pBoard->scoreChanged(m_nScore);
	emit m_pBoard->levelChanged(m_nLevel);
	newPiece();
	//if (controllable)
	m_timer.start(timeoutTime(), this);
}

void TetrixController::pause()
{
	if (!m_bIsStarted)
		return;

	m_bIsPaused = !m_bIsPaused;
	if (m_bIsPaused) {
		m_timer.stop();
	}
	else {
		//if (controllable)
		m_timer.start(timeoutTime(), this);
	}
	update();
}

void TetrixController::dropDown()
{
	int dropHeight = 0;
	int newY = m_pCurPiece->curY;
	while (newY > 0) {
		if (!tryMove(m_pCurPiece, m_pCurPiece->curX, newY - 1))
			break;
		--newY;
		++dropHeight;
	}
	pieceDropped(dropHeight);
}

void TetrixController::oneLineDown()
{
	if (!tryMove(m_pCurPiece, m_pCurPiece->curX, m_pCurPiece->curY - 1))
		pieceDropped(0);
}

void TetrixController::pieceDropped(int dropHeight)
{
	for (int i = 0; i < 4; ++i) {
		int x = m_pCurPiece->curX + m_pCurPiece->x(i);
		int y = m_pCurPiece->curY - m_pCurPiece->y(i);
		shapeAt(x, y) = m_pCurPiece->shape();
	}

	++m_nPiecesDropped;
	if (m_nPiecesDropped % 25 == 0) {
		++m_nLevel;
		//if (controllable)
		m_timer.start(timeoutTime(), this);
		emit m_pBoard->levelChanged(m_nLevel);
	}

	m_nScore += dropHeight + 7;
	emit m_pBoard->scoreChanged(m_nScore);
	removeFullLines();

	if (!m_bIsWaitingAfterLine)
		newPiece();
}

void TetrixController::removeFullLines()
{
	int numFullLines = 0;

	for (int i = BoardHeight - 1; i >= 0; --i) {
		bool lineIsFull = true;

		for (int j = 0; j < BoardWidth; ++j) {
			if (shapeAt(j, i) == NoShape) {
				lineIsFull = false;
				break;
			}
		}

		if (lineIsFull) {
			++numFullLines;
			for (int k = i; k < BoardHeight - 1; ++k) {
				for (int j = 0; j < BoardWidth; ++j)
					shapeAt(j, k) = shapeAt(j, k + 1);
			}
			for (int j = 0; j < BoardWidth; ++j)
				shapeAt(j, BoardHeight - 1) = NoShape;
		}
	}

	if (numFullLines > 0) {
		m_nLinesRemoved += numFullLines;
		m_nScore += 10 * numFullLines;
		emit m_pBoard->linesRemovedChanged(m_nLinesRemoved);
		emit m_pBoard->scoreChanged(m_nScore);
		m_timer.start(500, this);
		m_bIsWaitingAfterLine = true;
		m_pCurPiece->setShape(NoShape);
		update();
	}
}

/*
2015-10-29 修改nextPiece取得方式 ( 藉由 getNextPiece 取得隨機組中的方塊 )
*/
void TetrixController::newPiece()
{
	m_bShiftPress = false;
	m_pCurPiece = m_pNextPiece;
	emit m_pBoard->sendBoardAction(QEvent::Type::ActionChanged, m_pCurPiece->shape(), 0);
	m_pNextPiece = getNextPiece(); // 改為間接由 TetrixController::getNextPiece() 取得
	showNextPiece();
	m_pCurPiece->curX = BoardWidth / 2 + 1;
	m_pCurPiece->curY = BoardHeight - 1 + m_pCurPiece->minY();

	if (!tryMove(m_pCurPiece, m_pCurPiece->curX, m_pCurPiece->curY)) {
		//MessageBox(nullptr, LPCSTR("Lose"), 0, 0);
		m_pCurPiece->setShape(NoShape);
		m_timer.stop();
		m_bIsStarted = false;
		QMessageBox::information(this, tr("Lose"), tr("Lose"));
	}
}

void TetrixController::showNextPiece()
{
	m_pBoard->m_pNextPiece = m_pNextPiece;
	m_pBoard->showNextPiece();
}

/*
2015-10-29
從隨機產生的群組中依序挑選下次要顯示的方塊，如果已經挑完全部，重新產生
*/
TetrixPiece* TetrixController::getNextPiece()
{
	if (m_nCurPieceIdx == MAX_SHAPES)
		generateNextPieces();
	return m_apNextPieceGroup[m_nCurPieceIdx++];
}


void TetrixController::paintEvent(QPaintEvent *event)
{
	m_pBoard->m_pCurPiece = m_pCurPiece;
	m_pBoard->paintEvent(event);
}

/*
2015-10-29 新增按下Shift保留/置換當前方塊
2015-10-30 修改 Down 為 oneLineDown   UP旋轉方向顛倒
*/
void TetrixController::keyPressEvent(QKeyEvent *event)
{
	if (event->type() != QEvent::Type::None)
	{
		if (m_bIsControllable == false)
			return;
		if (event->key() != Qt::Key::Key_Shift)
			emit m_pBoard->sendBoardAction(event->type(), event->key(), event->modifiers());
	}

	if (!m_bIsStarted || m_bIsPaused || m_pCurPiece->shape() == NoShape) {
		QFrame::keyPressEvent(event);
		return;
	}
	switch (event->key()) {
	case Qt::Key_Left:
		tryMove(m_pCurPiece, m_pCurPiece->curX - 1, m_pCurPiece->curY);
		break;
	case Qt::Key_Right:
		tryMove(m_pCurPiece, m_pCurPiece->curX + 1, m_pCurPiece->curY);
		break;
	case Qt::Key_Down:
		oneLineDown();
		//tryMove(curPiece.rotatedRight(), curX, curY);
		break;
	case Qt::Key_Up:
		tryMove(m_pCurPiece->rotatedRight(), m_pCurPiece->curX, m_pCurPiece->curY);
		//tryMove(curPiece.rotatedLeft(), curX, curY);
		break;
	case Qt::Key_Space:
		dropDown();
		emit m_pBoard->sendBoardAction(QEvent::Type::ActionChanged, m_pCurPiece->shape(), 0);
		break;
	case Qt::Key_D:
		//oneLineDown();
		break;
	case Qt::Key_Shift: // 10/29
		if (!m_bShiftPress) //如果換這次方塊時，尚未按下shift
		{
			if (m_pHoldPiece && m_pHoldPiece->shape() != NoShape) { //檢查方塊是不是無效
				TetrixPiece *tmp = m_pCurPiece; //暫存這次的方塊
				newPiece(); //產生新的
				m_pCurPiece->setShape(m_pHoldPiece->shape()); //替換保留方塊至當前方塊
				m_pHoldPiece = tmp; //將暫存的(原本的)保留
			}
			else { //基本上只有剛開始遊戲才會發生這種情況 ( shape() == NoShape )
				m_pHoldPiece = m_pCurPiece; //保留當前方塊
				newPiece(); //產生新方塊
			}
			m_pBoard->m_pHoldPiece = m_pHoldPiece;
			m_pBoard->showHoldPiece(); //將保留的方塊顯示出來
			emit m_pBoard->sendBoardAction(event->type(), event->key(), event->modifiers());
		}
		m_bShiftPress = true; //標記已經按下shift
		break;

	default:
		QFrame::keyPressEvent(event);
	}
}

void TetrixController::timerEvent(QTimerEvent *event)
{
	//MessageBox(nullptr, LPCWSTR("1234"), 0, 0);
	if (event->timerId() == m_timer.timerId()) {
		if (m_bIsWaitingAfterLine) {
			m_bIsWaitingAfterLine = false;
			newPiece();
			//emit sendBoardAction(QEvent::Type::ActionChanged, curPiece.shape(), 0);
			m_timer.start(timeoutTime(), this);
		}
		else {
			oneLineDown();
		}
	}
	else {
		QFrame::timerEvent(event);
	}
}

/*
2015-10-29
隨機產生 7 個方塊一組(不重複) 並放至 nextPieceGroup
*/
void TetrixController::generateNextPieces()
{
	int success = 0, rndValue = 0;
	m_nCurPieceIdx = 0;
	bool used[MAX_SHAPES] = { false };
	while (success != MAX_SHAPES)
	{
		rndValue = 1 + rand() % MAX_SHAPES; // 0表示 NoShape
		if (used[rndValue])
			continue;
		TetrixPiece *newPiece = new TetrixPiece;
		newPiece->setShape(static_cast<TetrixShape>(rndValue));
		m_apNextPieceGroup[success++] = newPiece;
		used[rndValue] = true;
	}
}

bool TetrixController::
tryMove(TetrixPiece *newPiece, int newX, int newY)
{
	for (int i = 0; i < 4; ++i) {
		int x = newX + newPiece->x(i);
		int y = newY - newPiece->y(i);
		if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
			return false;
		if (shapeAt(x, y) != NoShape)
			return false;
	}

	m_pCurPiece = newPiece;
	m_pCurPiece->curX = newX;
	m_pCurPiece->curY = newY;
	m_pBoard->m_pCurPiece = m_pCurPiece;
	update();
	m_pBoard->update();
	return true;
}
