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

		//1. 数组越界
// 		{ 
// // 			vec[1];  // 触发断言，程序崩溃 Expression: vector subscript out of range
// 
// 			/*
// 			 * 访问容器时，使用at()和[]的区别
// 			 * at()函数会检查索引是否越界，如果越界，会抛出异常std::out_of_range，而不是直接崩溃。因为有检查边界，故性能较慢
// 			 * []没有额外开销，速度较快，适用于高性能场景，越界会导致未定义行为。故使用[]访问容器时，应当先检查索引是否越界
// 			 * 
// 			 */
// 			try
// 			{
// 				vec.at(1); // 抛出异常 std::out_of_range
// // 				vec[1]; // 未定义行为，程序崩溃
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