#pragma once
#include <QRunnable>
#include <QObject>

/*
 *	QRunnable继承QObect可实现信号槽
 */
class CalculateRunnable : public QObject, public QRunnable
{
	Q_OBJECT
public:
	~CalculateRunnable();
signals:
	void RunnableFinished();
protected:
	void run() override;
};

