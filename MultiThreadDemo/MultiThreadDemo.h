#pragma once

#include <QtWidgets/QMainWindow>
#include "CalculateInputStruct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MultiThreadDemoClass; };
QT_END_NAMESPACE

class QThread;

namespace ThreadDemo
{
	class Calculate;

	class MultiThreadDemo : public QMainWindow
	{
		Q_OBJECT

	public:
		MultiThreadDemo(QWidget* parent = nullptr);
		~MultiThreadDemo();

	signals:
		void startCalculateSignal(const CalculateInputStruct aInput);      //!< �ü����࿪ʼ����
		void cancleCalculateSignal();                                      //!< ȡ������
		void doSomeThingSignal();                                          //!< ��һЩ����
		void directDoSomeThingSignal();                                    //!< ��һЩ����

// 		void testMultiDataSignal(const QVector<double>& aXDatas, const QVector<double>& aYDatas); //!< ���Զ������ź�
		void testMultiDataSignal(const QVector<QStringList>& aDatas); //!< ���Զ������ź�

	private slots:
		void btn_calculate_slot();
		void btn_cancel_calculate_slot();
		void btn_test_multi_data_slot();
		void calculate_finished_slot();

		void update_prossorbar_slot();

	private:
		Ui::MultiThreadDemoClass* ui;

		QThread*   m_Thread;          //!< ������ִ�е��߳�
		Calculate* m_Calculate;       //!< �����࣬����mThread�߳�����ִ�У�������濨��
		QString    m_StartTime;       //!< ��¼��ʼ����ʱ��
		bool       m_CalculateStatus; //!< ����״̬
	};
}
