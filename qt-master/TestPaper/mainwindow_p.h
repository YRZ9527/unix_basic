#ifndef MAINWINDOW_P_H
#define MAINWINDOW_P_H
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "numitem.h"
#include <QSlider>
#include <QLabel>
#include "mainwindow.h"
#include "common.h"
QT_BEGIN_NAMESPACE
class MainWindowPrivate : public QObject {
   public:
    MainWindowPrivate(MainWindow *parent);
    void initUI();
    void initConnect();
    MainWindow *const q_ptr;
    QWidget *m_wdgMain;
    // 整数分数概率控件
    QSlider *m_sliderIntegerChance;
    QLabel *m_labIntegerChance;
    QLabel *m_labIntegerChanceValue;
    QHBoxLayout *m_layoutIntegerChance;
    // 正负数概率控件
    QSlider *m_sliderPositiveChance;
    QLabel *m_labPositiveChance;
    QLabel *m_labPositiveChanceValue;
    QHBoxLayout *m_layoutPositiveChance;
    // 分子范围 1 - X
    QLineEdit *m_lineEditMoleculeRange;
    QLabel *m_labMoleculeRange;
    QHBoxLayout *m_layoutMoleculeRange;
    // 分母范围 1 - X
    QLineEdit *m_lineEditDenominatorRange;
    QLabel *m_labDenominatorRange;
    QHBoxLayout *m_layoutDenominatorRange;
    // 保存路径
    QPushButton *m_btnSavePath;
    QLineEdit *m_lineEditSavePath;
    QHBoxLayout *m_hlayoutSavePath;

    QPushButton *m_btnWritePDF;

    QVBoxLayout *m_vlayoutMain;

    Q_DECLARE_PUBLIC(MainWindow)
   private:
    Numrule getNumRule();
    // 初始化所以需要绘制的数据。
    QList<QList<NumItem>> initALLNumList();
    // 初始化某一行的数据。
    QList<NumItem> initLineNumList(Numrule rule);
    // 绘制一条线上的1
   public slots:

    void slotIntegerChance(int value);
    void slotPositiveChance(int value);
};
QT_END_NAMESPACE
#endif  // MAINWINDOW_P_H
