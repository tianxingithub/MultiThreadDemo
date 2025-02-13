#include "CalculateRunnable.h"
#include <QThread>

namespace ThreadDemo
{

	CalculateRunnable::CalculateRunnable(const int aVectorSize, QObject* parent /*= nullptr*/)
	{
		if (aVectorSize <= 0)
			m_VectorSize = 1;
		else 
			m_VectorSize = aVectorSize;
	}

	CalculateRunnable::~CalculateRunnable()
	{
		auto test_thread_id = QThread::currentThreadId();
		int i = 1;
	}

	void CalculateRunnable::out_of_range()
	{
		try
		{
			std::vector<int> vec;
			for (int i = 0; i < m_VectorSize; i++)
			{
				vec.push_back(i);
			}

			out_of_range_test_error_in_function(vec);
// 			vec.at(1);
		}
		catch (...)
		{
			int i = 1;
		}

		//1. ����Խ��
// 		{ 
// // 			vec[1];  // �������ԣ�������� Expression: vector subscript out of range
// 
// 			/*
// 			 * ��������ʱ��ʹ��at()��[]������
// 			 * at()�������������Ƿ�Խ�磬���Խ�磬���׳��쳣std::out_of_range��������ֱ�ӱ�������Ϊ�м��߽磬�����ܽ���
// 			 * []û�ж��⿪�����ٶȽϿ죬�����ڸ����ܳ�����Խ��ᵼ��δ������Ϊ����ʹ��[]��������ʱ��Ӧ���ȼ�������Ƿ�Խ��
// 			 * 
// 			 */
// 			try
// 			{
// 				vec.at(1); // �׳��쳣 std::out_of_range
// // 				vec[1]; // δ������Ϊ���������
// 			}
// 			catch (...)
// 			{
// 				int i = 1;
// 			}
// 		}
	}

	void CalculateRunnable::out_of_range_test_error_in_function(std::vector<int>& aVec)
	{
		aVec.at(1);
	}

	void CalculateRunnable::run()
	{
		QThread::msleep(500);
		out_of_range();

		emit runnableFinishedSignal();
	}

}