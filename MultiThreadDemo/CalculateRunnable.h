#pragma once
#include <QRunnable>
#include <QObject>

namespace ThreadDemo
{

	/*
	 *	QRunnable�̳�QObect��ʵ���źŲ�
	 */
	class CalculateRunnable : public QObject, public QRunnable
	{
		Q_OBJECT
	public:
		~CalculateRunnable();

	signals:
		void runnableFinishedSignal();

	protected:
		void run() override;
	};

}