#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"
#include <QFile>

void Document::add_table_box() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QHBoxLayout* boxLayout = new QHBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}
