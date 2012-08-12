#include "SetupDialog.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QPalette>
#include <QSettings>
#include <QSize>

#include "main.h"

SetupDialog::SetupDialog(QWidget* parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    // Determine biggest screen dimensions
    this->screenWidth = 0;
    for (int screen = 0; screen < QApplication::desktop()->screenCount(); screen++)
    {
        if (QApplication::desktop()->screenGeometry(screen).width() > screenWidth)
        {
            this->screenWidth = QApplication::desktop()->screenGeometry(screen).width();
            this->screenHeight = QApplication::desktop()->screenGeometry(screen).height();
        }
    }

    // Read settings
    QSettings settings;

    // Create directoryGroupBox
    this->directoryLabel = new QLabel(tr("Directory:"));
    this->directoryEdit = new QLineEdit(settings.value("directory", QVariant(QDir::home().absolutePath())).toString());
    connect(this->directoryEdit, SIGNAL(textChanged(QString)), this, SLOT(directorySelected(QString)));
    this->directorySelectButton = new QPushButton(tr("Select"));
    connect(this->directorySelectButton, SIGNAL(clicked()), this, SLOT(selectDirectory()));

    this->directoryLayout = new QGridLayout();
    this->directoryLayout->addWidget(this->directoryLabel, 0, 0);
    this->directoryLayout->addWidget(this->directoryEdit, 0, 1);
    this->directoryLayout->addWidget(this->directorySelectButton, 0, 2);

    this->directoryGroupBox = new QGroupBox(tr("Movies Directory"));
    this->directoryGroupBox->setLayout(this->directoryLayout);

    // Create movieGroupBox    
    this->movieWidthLabel  = new QLabel(tr("Width:"));
    this->movieHeightLabel = new QLabel(tr("Height:"));

    this->movieWidthSpinBox = new QSpinBox();
    this->movieWidthSpinBox->setSingleStep(5);
    this->movieWidthSpinBox->setMinimum(60);
    this->movieWidthSpinBox->setMaximum(this->screenWidth);
    this->movieWidthSpinBox->setValue(settings.value("movieWidth", QVariant(620)).toInt());
    this->movieWidthSpinBox->setSuffix(tr(" px"));
    connect(this->movieWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieWidthChanged(int)));

    movieHeightSpinBox = new QSpinBox();
    this->movieHeightSpinBox->setSingleStep(5);
    this->movieHeightSpinBox->setMinimum(this->movieHeightFor(60));
    this->movieHeightSpinBox->setMaximum(this->movieHeightFor(this->screenWidth));
    this->movieHeightSpinBox->setReadOnly(true);
    this->movieHeightSpinBox->setValue(this->movieHeightFor(this->movieWidthSpinBox->value()));
    this->movieHeightSpinBox->setSuffix(tr(" px"));

    this->movieLayout = new QGridLayout();
    this->movieLayout->addWidget(new QLabel, 0, 0);
    this->movieLayout->addWidget(this->movieWidthLabel, 1, 0);
    this->movieLayout->addWidget(this->movieHeightLabel, 2, 0);
    this->movieLayout->addWidget(this->movieWidthSpinBox, 1, 1);
    this->movieLayout->addWidget(this->movieHeightSpinBox, 2, 1);

    this->movieGroupBox = new QGroupBox(tr("Movie"));
    this->movieGroupBox->setLayout(this->movieLayout);

    // Create movieFieldGroupBox
    this->movieHPaddingMarginLabel = new QLabel(tr("Horizontal"));
    this->movieVPaddingMarginLabel = new QLabel(tr("Vertical"));
    this->moviePaddingLabel = new QLabel(tr("Grid padding:"));
    this->movieMarginLabel = new QLabel(tr("Movies margin:"));

    this->movieHPaddingSpinBox = new QSpinBox();
    this->movieHPaddingSpinBox->setMinimum(0);
    this->movieHPaddingSpinBox->setMaximum(this->screenWidth);
    this->movieHPaddingSpinBox->setValue(settings.value("movieHPadding", QVariant(5)).toInt());
    this->movieHPaddingSpinBox->setSuffix(tr(" px"));
    connect(this->movieHPaddingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieHPaddingChanged(int)));

    this->movieVPaddingSpinBox = new QSpinBox();
    this->movieVPaddingSpinBox->setMinimum(0);
    this->movieVPaddingSpinBox->setMaximum(this->screenHeight);
    this->movieVPaddingSpinBox->setValue(settings.value("movieVPadding", QVariant(5)).toInt());
    this->movieVPaddingSpinBox->setSuffix(tr(" px"));
    connect(this->movieVPaddingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieVPaddingChanged(int)));

    this->movieHMarginSpinBox = new QSpinBox();
    this->movieHMarginSpinBox->setMinimum(0);
    this->movieHMarginSpinBox->setMaximum(this->screenWidth);
    this->movieHMarginSpinBox->setValue(settings.value("movieHMargin", QVariant(5)).toInt());
    this->movieHMarginSpinBox->setSuffix(tr(" px"));
    connect(this->movieHMarginSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieHMarginChanged(int)));

    this->movieVMarginSpinBox = new QSpinBox();
    this->movieVMarginSpinBox->setMinimum(0);
    this->movieVMarginSpinBox->setMaximum(this->screenHeight);
    this->movieVMarginSpinBox->setValue(settings.value("movieVMargin", QVariant(5)).toInt());
    this->movieVMarginSpinBox->setSuffix(tr(" px"));
    connect(this->movieVMarginSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieVMarginChanged(int)));

    this->moviePaddingMarginLayout = new QGridLayout();
    this->moviePaddingMarginLayout->addWidget(this->moviePaddingLabel, 1, 0);
    this->moviePaddingMarginLayout->addWidget(this->movieMarginLabel, 2, 0);
    this->moviePaddingMarginLayout->addWidget(this->movieHPaddingMarginLabel, 0, 1);
    this->moviePaddingMarginLayout->addWidget(this->movieHPaddingSpinBox, 1, 1);
    this->moviePaddingMarginLayout->addWidget(this->movieHMarginSpinBox, 2, 1);
    this->moviePaddingMarginLayout->addWidget(this->movieVPaddingMarginLabel, 0, 2);
    this->moviePaddingMarginLayout->addWidget(this->movieVPaddingSpinBox, 1, 2);
    this->moviePaddingMarginLayout->addWidget(this->movieVMarginSpinBox, 2, 2);

    this->moviePaddingMarginGroupBox = new QGroupBox(tr("Padding & Margin"));
    this->moviePaddingMarginGroupBox->setLayout(this->moviePaddingMarginLayout);

    // Create movieMiscGroupBox
    this->miscScrollLabel = new QLabel(tr("Scroll:"));

    this->miscScrollComboBox = new QComboBox();
    this->miscScrollComboBox->addItem(QString("Vertical"), QVariant("V"));
    this->miscScrollComboBox->addItem(QString("Horizontal"), QVariant("H"));
    this->miscScrollComboBox->setCurrentIndex(this->miscScrollComboBox->findData(settings.value("scroll", QVariant("V"))));

    this->miscLayout = new QGridLayout();
    this->miscLayout->addWidget(this->miscScrollLabel, 0, 4);
    this->miscLayout->addWidget(this->miscScrollComboBox, 0, 5);

    this->miscGroupBox = new QGroupBox(tr("Misc"));
    this->miscGroupBox->setLayout(this->miscLayout);

    // Create testMovieWidget
    this->testMovieWidgetGridLayout = new GridLayout(this->screenWidth, this->screenHeight,
                                                     this->movieHPaddingSpinBox->value(), this->movieVPaddingSpinBox->value(),
                                                     this->movieWidthSpinBox->value(), this->movieHeightSpinBox->value(),
                                                     this->movieHMarginSpinBox->value(), this->movieVMarginSpinBox->value());
    this->testMovieWidget = new TestMovieWidget(this->testMovieWidgetGridLayout, this);

    // Create buttonBox
    this->okButton = new QPushButton(tr("OK"));
    connect(this->okButton, SIGNAL(clicked()), this, SLOT(ok()));

    this->okAndRunButton = new QPushButton(tr("OK and Run"));
    connect(this->okAndRunButton, SIGNAL(clicked()), this, SLOT(okAndRun()));

    this->buttonBox = new QDialogButtonBox();
    this->buttonBox->addButton(this->okButton, QDialogButtonBox::ActionRole);
    this->buttonBox->addButton(this->okAndRunButton, QDialogButtonBox::ActionRole);

    // Create main dialog layout
    this->dialogLayout = new QGridLayout();
    this->dialogLayout->addWidget(this->directoryGroupBox, 0, 0, 1, 2);
    this->dialogLayout->addWidget(this->movieGroupBox, 1, 0);
    this->dialogLayout->addWidget(this->moviePaddingMarginGroupBox, 1, 1);
    this->dialogLayout->addWidget(this->miscGroupBox, 2, 0, 1, 2);
    this->dialogLayout->addWidget(this->testMovieWidget, 3, 0, 1, 2);
    this->dialogLayout->addWidget(this->buttonBox, 4, 0, 1, 2);
    this->setLayout(dialogLayout);

    // Cosmetics
    setWindowTitle(tr("theMplayer setup"));
    this->testMovieWidget->setMinimumSize(this->screenWidth / 2, this->screenHeight / 2);
    this->testMovieWidget->setMaximumSize(this->screenWidth / 2, this->screenHeight / 2);
}

int SetupDialog::movieHeightFor(int movieWidthValue)
{
    return (int) ((float)movieWidthValue / this->screenWidth * this->screenHeight + 0.5);
}

void SetupDialog::movieWidthChanged(int newValue)
{
    this->movieHeightSpinBox->setValue(this->movieHeightFor(newValue));
    this->updateTestGridValues();
}

void SetupDialog::movieHPaddingChanged(int newValue)
{
    (void) newValue;
    this->updateTestGridValues();
}

void SetupDialog::movieVPaddingChanged(int newValue)
{
    (void) newValue;
    this->updateTestGridValues();
}

void SetupDialog::movieHMarginChanged(int newValue)
{
    (void) newValue;
    this->updateTestGridValues();
}

void SetupDialog::movieVMarginChanged(int newValue)
{
    (void) newValue;
    this->updateTestGridValues();
}

void SetupDialog::updateTestGridValues()
{
    if (this->testMovieWidgetGridLayout != NULL)
    {
        this->testMovieWidgetGridLayout->setGridHPadding(this->movieHPaddingSpinBox->value());
        this->testMovieWidgetGridLayout->setGridVPadding(this->movieVPaddingSpinBox->value());
        this->testMovieWidgetGridLayout->setElementWidth(this->movieWidthSpinBox->value());
        this->testMovieWidgetGridLayout->setElementHeight(this->movieHeightSpinBox->value());
        this->testMovieWidgetGridLayout->setElementHMargin(this->movieHMarginSpinBox->value());
        this->testMovieWidgetGridLayout->setElementVMargin(this->movieVMarginSpinBox->value());

        this->testMovieWidget->update();
    }
}

void SetupDialog::saveSettings()
{
    QSettings settings;
    settings.setValue("setupDone", QVariant(true));
    settings.setValue("directory", QVariant(this->directoryEdit->displayText()));
    settings.setValue("movieWidth", QVariant(this->movieWidthSpinBox->value()));
    settings.setValue("movieHeight", QVariant(this->movieHeightSpinBox->value()));
    settings.setValue("movieHPadding", QVariant(this->movieHPaddingSpinBox->value()));
    settings.setValue("movieVPadding", QVariant(this->movieVPaddingSpinBox->value()));
    settings.setValue("movieHMargin", QVariant(this->movieHMarginSpinBox->value()));
    settings.setValue("movieVMargin", QVariant(this->movieVMarginSpinBox->value()));

    settings.setValue("scroll", QVariant(this->miscScrollComboBox->itemData(this->miscScrollComboBox->currentIndex())));
}

void SetupDialog::selectDirectory()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                          this->directoryEdit->displayText(),
                                                          QFileDialog::ShowDirsOnly);
    this->directoryEdit->setText(directory);
}

void SetupDialog::directorySelected(QString directory)
{
    QDir dir = QDir(directory);
    QPalette pal = this->directoryEdit->palette();

    if (!dir.exists(directory))
    {
        pal.setColor(QPalette::Text, Qt::red);
    }
    else
    {
        pal.setColor(QPalette::Text, Qt::black);
    }

    this->directoryEdit->setPalette(pal);
}

void SetupDialog::ok()
{
    QDir dir = QDir(directoryEdit->displayText());
    if (!dir.exists())
    {
        QMessageBox messageBox(QMessageBox::Critical,
                               tr("Error"), tr("Selected movie directory does not exist"),
                               QMessageBox::Ok, this);
        messageBox.exec();
        return;
    }

    this->saveSettings();
    this->accept();
}

void SetupDialog::okAndRun()
{
    this->ok();
    executeMovieList();
}
