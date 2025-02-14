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
		void startCalculateSignal(const CalculateInputStruct aInput);      //!< 让计算类开始计算
		void cancleCalculateSignal();                                      //!< 取消计算
		void doSomeThingSignal();                                          //!< 做一些事情
		void directDoSomeThingSignal();                                    //!< 做一些事情

// 		void testMultiDataSignal(const QVector<double>& aXDatas, const QVector<double>& aYDatas); //!< 测试多数据信号
		void testMultiDataSignal(const QVector<QStringList>& aDatas); //!< 测试多数据信号

	private slots:
		void btn_calculate_slot();
		void btn_cancel_calculate_slot();
		void btn_test_multi_data_slot();
		void calculate_finished_slot();

		void update_prossorbar_slot();

	private:
		Ui::MultiThreadDemoClass* ui;

		QThread*   m_Thread;          //!< 计算类执行的线程
		Calculate* m_Calculate;       //!< 计算类，放在mThread线程里面执行，避免界面卡死
		QString    m_StartTime;       //!< 记录开始计算时间
		bool       m_CalculateStatus; //!< 计算状态
	};
}
