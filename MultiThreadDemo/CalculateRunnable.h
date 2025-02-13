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
		explicit CalculateRunnable(const int aVectorSize, QObject *parent = nullptr);
		~CalculateRunnable();

	private:
		void out_of_range();
		void out_of_range_test_error_in_function(std::vector<int>& aVec);

	signals:
		void runnableFinishedSignal();

	protected:
		void run() override;

	private:
		int m_VectorSize; 
	};

}