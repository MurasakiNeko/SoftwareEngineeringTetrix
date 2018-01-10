#pragma once
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include "tetrixboard.h"
#include "tetrixpiece.h"
#include "tetrixoperationcode.h"

class QLabel;
class TetrixController : public QFrame
{
	friend class TetrixBoard;

	Q_OBJECT
private:
	TetrixBoard* m_pBoard;

public:
	TetrixController(QWidget *parent, TetrixBoard* pBoard);

protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void timerEvent(QTimerEvent *event);

public slots:
	void start();
	void pause();

public:
	TetrixShape &shapeAt(int x, int y) { return m_pBoard->shapeAt(x, y); }
	int timeoutTime() { return 1000 / (m_nLevel); }

	void dropDown();
	void oneLineDown();
	void pieceDropped(int dropHeight);
	void removeFullLines();
	void newPiece();
	void showNextPiece();
	TetrixPiece* getNextPiece(); // 10-29 ���o�s�դ����U�@�Ӥ��
	void generateNextPieces(); // 10-29 �H������ 7 �Ӥ��P����ܸs�դ�
	bool tryMove(TetrixPiece *newPiece, int newX, int newY);

private:
	const static int MAX_SHAPES = 7;
	enum { 
		BoardWidth = 10, 
		BoardHeight = 22 
	};

	QBasicTimer m_timer;
	bool m_bShiftPress,  // 10-29 ���shift���U?
		     m_bIsStarted, m_bIsPaused, m_bIsWaitingAfterLine, m_bIsControllable;

	TetrixPiece* m_pCurPiece, * m_pNextPiece, *m_pHoldPiece = nullptr; // 10-29 �O�d�����
	TetrixPiece* m_apNextPieceGroup[MAX_SHAPES]; // 10-29 ����s��
	int m_nCurPieceIdx, m_nLinesRemoved, m_nPiecesDropped, m_nScore, m_nLevel;

};