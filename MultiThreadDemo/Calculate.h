#pragma once

#include <QObject>
#include "CalculateInputStruct.h"

class QThreadPool;

namespace ThreadDemo
{

	/**
	 * ���̼߳�����
	 * 1. �����ⲿ�����������������
	 * 2. ����������ഫ���������
	 * 3. ���½�����ʾ������
	 */
	class Calculate : public QObject
	{
		Q_OBJECT

	public:
		Calculate(QObject* parent = nullptr);
		void directDoSomeThing(); //!< ֱ�ӵ��û��������߳���ִ�У�ͨ���źŲ۵����������߳���ִ��
		~Calculate();

	public slots:
		void startCalculate(const CalculateInputStruct aInput);
		void cancelCalculate();
		void doSomeThingSlot();

		//!@ ������
// 		void testtMultiDataSlot(const QVector<double>& aXDatas, const QVector<double>& aYDatas);
		void testtMultiDataSlot(const QVector<QStringList>& aDatas);

	signals:
		void calculateFinishedSignal();
		void updateProssorbarSignal();

	private:
		QThreadPool* m_ThreadPool; //!< ���������ϼ����ʱ��ʹ��
	};

}