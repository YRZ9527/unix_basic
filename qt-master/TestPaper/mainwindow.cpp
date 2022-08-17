#include "mainwindow.h"

#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QUrl>
#include "numitem.h"
#include <QList>
#include <QDebug>
#include "mainwindow_p.h"
#include <QIntValidator>
#include <QRandomGenerator>
MainWindowPrivate::MainWindowPrivate(MainWindow *parent)
    : q_ptr(parent)
    , m_wdgMain(new QWidget())
    , m_sliderIntegerChance(new QSlider())
    , m_labIntegerChance(new QLabel(tr("分整数概率：")))
    , m_labIntegerChanceValue(new QLabel("50%"))
    , m_layoutIntegerChance(new QHBoxLayout)
    , m_sliderPositiveChance(new QSlider())
    , m_labPositiveChance(new QLabel(tr("正负数概率：")))
    , m_labPositiveChanceValue(new QLabel(tr("50%")))
    , m_layoutPositiveChance(new QHBoxLayout)
    , m_lineEditMoleculeRange(new QLineEdit("10"))
    , m_labMoleculeRange(new QLabel(tr("分子值范围：")))
    , m_layoutMoleculeRange(new QHBoxLayout)
    , m_lineEditDenominatorRange(new QLineEdit("10"))
    , m_labDenominatorRange(new QLabel(tr("分母值范围：")))
    , m_layoutDenominatorRange(new QHBoxLayout)
    , m_btnSavePath(new QPushButton(tr("保存路径")))
    , m_lineEditSavePath(new QLineEdit())
    , m_hlayoutSavePath(new QHBoxLayout)
    , m_btnWritePDF(new QPushButton(tr("生成试卷")))
    , m_vlayoutMain(new QVBoxLayout)
{
    initUI();
    initConnect();
}

void MainWindowPrivate::initUI()
{
    //
    m_layoutIntegerChance->addWidget(m_labIntegerChance);
    m_layoutIntegerChance->addWidget(m_sliderIntegerChance);
    m_sliderIntegerChance->setValue(50);
    m_sliderIntegerChance->setMaximum(100);
    m_layoutIntegerChance->addWidget(m_labIntegerChanceValue);
    m_sliderIntegerChance->setOrientation(Qt::Orientation::Horizontal);
    m_vlayoutMain->addLayout(m_layoutIntegerChance);
    //
    m_layoutPositiveChance->addWidget(m_labPositiveChance);
    m_layoutPositiveChance->addWidget(m_sliderPositiveChance);
    m_sliderPositiveChance->setValue(50);
    m_sliderPositiveChance->setMaximum(100);
    m_layoutPositiveChance->addWidget(m_labPositiveChanceValue);
    m_sliderPositiveChance->setOrientation(Qt::Orientation::Horizontal);
    m_vlayoutMain->addLayout(m_layoutPositiveChance);
    //
    m_layoutMoleculeRange->addWidget(m_labMoleculeRange);
    m_layoutMoleculeRange->addWidget(m_lineEditMoleculeRange);
    m_lineEditMoleculeRange->setValidator(new QIntValidator(1, 1000, this));
    m_vlayoutMain->addLayout(m_layoutMoleculeRange);
    //
    m_layoutDenominatorRange->addWidget(m_labDenominatorRange);
    m_layoutDenominatorRange->addWidget(m_lineEditDenominatorRange);
    m_lineEditDenominatorRange->setValidator(new QIntValidator(1, 1000, this));
    m_vlayoutMain->addLayout(m_layoutDenominatorRange);
    //
    m_hlayoutSavePath->addWidget(m_lineEditSavePath);
    m_hlayoutSavePath->addWidget(m_btnSavePath);
    m_vlayoutMain->addLayout(m_hlayoutSavePath);

    m_vlayoutMain->addWidget(m_btnWritePDF);
    m_vlayoutMain->addStretch();
    m_wdgMain->setLayout(m_vlayoutMain);
}
void MainWindowPrivate::initConnect()
{
    connect(m_sliderIntegerChance, &QSlider::valueChanged, this,
            &MainWindowPrivate::slotIntegerChance);
    connect(m_sliderPositiveChance, &QSlider::valueChanged, this,
            &MainWindowPrivate::slotPositiveChance);

    connect(m_btnWritePDF, &QPushButton::clicked, q_ptr,
            &MainWindow::slotDoWrite);
    connect(m_btnSavePath, &QPushButton::clicked, q_ptr,
            &MainWindow::slotPickPath);
}

Numrule MainWindowPrivate::getNumRule()
{
    Numrule item;
    item.IntegerChance = m_sliderIntegerChance->value();
    item.PositiveChance = m_sliderPositiveChance->value();
    item.MoleculeRange = m_lineEditMoleculeRange->text().toInt();
    item.DenominatorRange = m_lineEditDenominatorRange->text().toInt();
    return item;
}

QList<QList<NumItem>> MainWindowPrivate::initALLNumList()
{
    QList<QList<NumItem>> list;
    for (int i = 0 ; i < 10;i ++) {
        QList<NumItem> lineList = initLineNumList(getNumRule());
        list.append(lineList);
    }
    return list;
}

QList<NumItem> MainWindowPrivate::initLineNumList(Numrule rule)
{
    QList<NumItem> list;
   int num = QRandomGenerator::global()->bounded(3)+2;
   for (int i = 0; i <= num; i++) {
       NumItem numItem(rule);
       list.append(numItem);
   }
   return list;
}



void MainWindowPrivate::slotIntegerChance(int value)
{
    QString str = QString::number(value) + "%";
    m_labIntegerChanceValue->setText(str);
}

void MainWindowPrivate::slotPositiveChance(int value)
{
    QString str = QString::number(value) + "%";
    m_labPositiveChanceValue->setText(str);
}

//=====================================================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , d_ptr(new MainWindowPrivate(this))
{
    Q_D(MainWindow);
    setCentralWidget(d->m_wdgMain);
    setMinimumWidth(800);
}

MainWindow::~MainWindow()
{
    Q_D(MainWindow);
    delete d;
}

void MainWindow::slotDoWrite()
{
    Q_D(MainWindow);

    QString file_path = QApplication::applicationDirPath() + "/text.pdf";
    QList<QList<NumItem>> list = d->initALLNumList();
    pdfManager.writePDF(file_path,list);

}

void MainWindow::slotPickPath() { qInfo() << "slotPickPath"; }
