#include "mainwindow.h"
#include "document.h"
#include "sortation.h"
#include "ui_mainwindow.h"
#include "data.h"

void Document::make_doc0() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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

void Document::make_doc1() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    boxLayout->setObjectName("groupBoxLayout");
    QLayout* layout = tab->boxArea;

    add_tool_option(box, boxLayout);
    AddItemText(boxLayout, Kor("이름"),"");
    AddItemText(boxLayout, Kor("나이"),"");
    AddItemText(boxLayout, Kor("주소"),"");

    box->setAlignment(Qt::AlignTop);
    box->setMinimumSize(800, 800);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    boxLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    boxLayout->setAlignment(Qt::AlignTop);

    layout->addWidget(box);
}

void Document::make_doc2() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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

void Document::make_doc3() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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

void Document::make_doc4() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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

void Document::make_doc5() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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

void Document::make_doc6() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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

void Document::make_doc7() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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

void Document::make_doc8() {
    QGroupBox* box = new QGroupBox("", tab);
    box->setObjectName("groupBox");
    QVBoxLayout* boxLayout = new QVBoxLayout(box);
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
