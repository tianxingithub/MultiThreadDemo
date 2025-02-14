#pragma once

#include <QObject>
#include "CalculateInputStruct.h"

class QThreadPool;

namespace ThreadDemo
{

	/**
	 * 多线程计算类
	 * 1. 解析外部参数，遍历计算情况
	 * 2. 负责给任务类传递输入参数
	 * 3. 更新界面显示进度条
	 */
	class Calculate : public QObject
	{
		Q_OBJECT

	public:
		Calculate(QObject* parent = nullptr);
		void directDoSomeThing(); //!< 直接调用还是在主线程中执行，通过信号槽调用则在子线程中执行
		~Calculate();

	public slots:
		void startCalculate(const CalculateInputStruct aInput);
		void cancelCalculate();
		void doSomeThingSlot();

		//!@ 测试用
// 		void testtMultiDataSlot(const QVector<double>& aXDatas, const QVector<double>& aYDatas);
		void testtMultiDataSlot(const QVector<QStringList>& aDatas);

	signals:
		void calculateFinishedSignal();
		void updateProssorbarSignal();

	private:
		QThreadPool* m_ThreadPool; //!< 用于在中上计算的时候使用
	};

}