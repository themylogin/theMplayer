#include <QApplication>
#include <QComboBox>
#include <QDesktopWidget>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <QPushButton>
#include <QSettings>
#include <QSize>

#include "main.h"
#include "SetupDialog.h"
#include "TestMovieGrid.h"

SetupDialog::SetupDialog(QWidget *parent, Qt::WindowFlags f)
        : QDialog(parent, f)
{
    QSettings settings;
    setWindowTitle(tr("theMplayer setup"));

    movieTestGrid = NULL; // bug #1

    // Create directoryGroupBox
    directoryLabel = new QLabel(tr("Directory:"));
    directoryEdit = new QLineEdit(settings.value("directory", QVariant(QDir::home().absolutePath())).toString());
    connect(directoryEdit, SIGNAL(textChanged(QString)), this, SLOT(directorySelected(QString)));
    directorySelectButton = new QPushButton(tr("Select"));
    connect(directorySelectButton, SIGNAL(clicked()), this, SLOT(selectDirectory()));

    directoryLayout = new QGridLayout();
    directoryLayout->addWidget(directoryLabel, 0, 0);
    directoryLayout->addWidget(directoryEdit, 0, 1);
    directoryLayout->addWidget(directorySelectButton, 0, 2);

    directoryGroupBox = new QGroupBox(tr("Movies Directory"));
    directoryGroupBox->setLayout(directoryLayout);

    // Create movieGroupBox    
    movieWidthLabel  = new QLabel(tr("Width:"));
    movieHeightLabel = new QLabel(tr("Height:"));

    movieWidthSpinBox = new QSpinBox();
    movieWidthSpinBox->setSingleStep(5);
    movieWidthSpinBox->setMinimum(60);
    movieWidthSpinBox->setMaximum(QApplication::desktop()->geometry().width());
    movieWidthSpinBox->setValue(settings.value("movieWidth", QVariant(400)).toInt());
    movieWidthSpinBox->setSuffix(tr(" px"));
    connect(movieWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieWidthChanged(int)));

    movieHeightSpinBox = new QSpinBox();
    movieHeightSpinBox->setSingleStep(5);
    movieHeightSpinBox->setReadOnly(true);
    movieHeightSpinBox->setMinimum(movieHeightValue(60));
    movieHeightSpinBox->setMaximum(QApplication::desktop()->geometry().height());
    movieHeightSpinBox->setValue(movieHeightValue(movieWidthSpinBox->value()));
    movieHeightSpinBox->setSuffix(tr(" px"));

    movieLayout = new QGridLayout();
    movieLayout->addWidget(new QLabel, 0, 0);
    movieLayout->addWidget(movieWidthLabel, 1, 0);
    movieLayout->addWidget(movieHeightLabel, 2, 0);
    movieLayout->addWidget(movieWidthSpinBox, 1, 1);
    movieLayout->addWidget(movieHeightSpinBox, 2, 1);

    movieGroupBox = new QGroupBox(tr("Movie"));
    movieGroupBox->setLayout(movieLayout);

    // Create movieFieldGroupBox
    movieFieldHLabel = new QLabel(tr("Horizontal"));
    movieFieldVLabel = new QLabel(tr("Vertical"));
    movieFieldMarginsLabel = new QLabel(tr("Margins:"));
    movieFieldPaddingsLabel = new QLabel(tr("Paddings:"));

    movieFieldHMarginSpinBox = new QSpinBox();
    movieFieldHMarginSpinBox->setMinimum(0);
    movieFieldHMarginSpinBox->setMaximum(QApplication::desktop()->geometry().width());
    movieFieldHMarginSpinBox->setValue(settings.value("movieFieldHMargin", QVariant(10)).toInt());
    movieFieldHMarginSpinBox->setSuffix(tr(" px"));
    connect(movieFieldHMarginSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieFieldHMarginChanged(int)));

    movieFieldVMarginSpinBox = new QSpinBox();
    movieFieldVMarginSpinBox->setMinimum(0);
    movieFieldVMarginSpinBox->setMaximum(QApplication::desktop()->geometry().height());
    movieFieldVMarginSpinBox->setValue(settings.value("movieFieldVMargin", QVariant(10)).toInt());
    movieFieldVMarginSpinBox->setSuffix(tr(" px"));
    connect(movieFieldVMarginSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieFieldVMarginChanged(int)));

    movieFieldHPaddingSpinBox = new QSpinBox();
    movieFieldHPaddingSpinBox->setMinimum(0);
    movieFieldHPaddingSpinBox->setMaximum(QApplication::desktop()->geometry().width());
    movieFieldHPaddingSpinBox->setValue(settings.value("movieFieldHPadding", QVariant(10)).toInt());
    movieFieldHPaddingSpinBox->setSuffix(tr(" px"));
    connect(movieFieldHPaddingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieFieldHPaddingChanged(int)));

    movieFieldVPaddingSpinBox = new QSpinBox();
    movieFieldVPaddingSpinBox->setMinimum(0);
    movieFieldVPaddingSpinBox->setMaximum(QApplication::desktop()->geometry().height());
    movieFieldVPaddingSpinBox->setValue(settings.value("movieFieldVPadding", QVariant(10)).toInt());
    movieFieldVPaddingSpinBox->setSuffix(tr(" px"));
    connect(movieFieldVPaddingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(movieFieldVPaddingChanged(int)));

    movieFieldLayout = new QGridLayout();
    movieFieldLayout->addWidget(movieFieldMarginsLabel, 1, 0);
    movieFieldLayout->addWidget(movieFieldPaddingsLabel, 2, 0);
    movieFieldLayout->addWidget(movieFieldHLabel, 0, 1);
    movieFieldLayout->addWidget(movieFieldHMarginSpinBox, 1, 1);
    movieFieldLayout->addWidget(movieFieldHPaddingSpinBox, 2, 1);
    movieFieldLayout->addWidget(movieFieldVLabel, 0, 2);
    movieFieldLayout->addWidget(movieFieldVMarginSpinBox, 1, 2);
    movieFieldLayout->addWidget(movieFieldVPaddingSpinBox, 2, 2);

    movieFieldGroupBox = new QGroupBox(tr("Movies Field"));
    movieFieldGroupBox->setLayout(movieFieldLayout);

    // Create movieMiscGroupBox
    miscAudioTrackLangLabel = new QLabel(tr("Audio track:"));
    miscSubtitleLangLabel = new QLabel(tr("Subtitle language:"));
    miscScrollLabel = new QLabel(tr("Scroll:"));

    miscAudioTrackLangComboBox = new QComboBox();
    miscAudioTrackLangComboBox->addItem(QString("English"), QVariant("eng"));
    miscAudioTrackLangComboBox->addItem(QString("Japanese"), QVariant("jap"));
    miscAudioTrackLangComboBox->addItem(QString("Russian"), QVariant("rus"));
    miscAudioTrackLangComboBox->setCurrentIndex(miscAudioTrackLangComboBox->findData(settings.value("audioLang", QVariant("jap"))));

    miscSubtitleLangComboBox = new QComboBox();
    miscSubtitleLangComboBox->addItem(QString("English"), QVariant("eng"));
    miscSubtitleLangComboBox->addItem(QString("Japanese"), QVariant("jap"));
    miscSubtitleLangComboBox->addItem(QString("Russian"), QVariant("rus"));
    miscSubtitleLangComboBox->setCurrentIndex(miscSubtitleLangComboBox->findData(settings.value("subLang", QVariant("rus"))));

    miscScrollComboBox = new QComboBox();
    miscScrollComboBox->addItem(QString("Vertical"), QVariant("V"));
    miscScrollComboBox->addItem(QString("Horizontal"), QVariant("H"));
    miscScrollComboBox->setCurrentIndex(miscScrollComboBox->findData(settings.value("scroll", QVariant("V"))));

    miscLayout = new QGridLayout();
    miscLayout->addWidget(miscAudioTrackLangLabel, 0, 0);
    miscLayout->addWidget(miscAudioTrackLangComboBox, 0, 1);
    miscLayout->addWidget(miscSubtitleLangLabel, 0, 2);
    miscLayout->addWidget(miscSubtitleLangComboBox, 0, 3);
    miscLayout->addWidget(miscScrollLabel, 0, 4);
    miscLayout->addWidget(miscScrollComboBox, 0, 5);

    miscGroupBox = new QGroupBox(tr("Misc"));
    miscGroupBox->setLayout(miscLayout);

    // Create movieTestGrid
    movieTestGrid = new TestMovieGrid(1920 / 2,
                                      1080 / 2,

                                      movieWidthSpinBox->value() / 2,
                                      movieHeightSpinBox->value() / 2,

                                      movieFieldHMarginSpinBox->value() / 2,
                                      movieFieldHPaddingSpinBox->value() / 2,

                                      movieFieldVMarginSpinBox->value() / 2,
                                      movieFieldVPaddingSpinBox->value() / 2);

    // Create buttonBox
    okButton = new QPushButton(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(ok()));

    okAndRunButton = new QPushButton(tr("OK and Run"));
    connect(okAndRunButton, SIGNAL(clicked()), this, SLOT(okAndRun()));

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(okButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(okAndRunButton, QDialogButtonBox::ActionRole);

    // Create main dialog layout
    dialogLayout = new QGridLayout();
    dialogLayout->addWidget(directoryGroupBox, 0, 0, 1, 2);
    dialogLayout->addWidget(movieGroupBox, 1, 0);
    dialogLayout->addWidget(movieFieldGroupBox, 1, 1);
    dialogLayout->addWidget(miscGroupBox, 2, 0, 1, 2);
    dialogLayout->addWidget(movieTestGrid, 3, 0, 1, 2);
    dialogLayout->addWidget(buttonBox, 4, 0, 1, 2);
    setLayout(dialogLayout);

    resize(1920 / 2,
           1080 / 2);

}

int SetupDialog::movieHeightValue(int movieWidthValue)
{
    return (int) (movieWidthValue / 4.0 * 3.0 + 0.5);
}

void SetupDialog::movieWidthChanged(int newValue)
{
    movieHeightSpinBox->setValue(movieHeightValue(newValue));
    updateTestGridValues();
}

void SetupDialog::movieFieldHMarginChanged(int newValue)
{
    updateTestGridValues();
}

void SetupDialog::movieFieldVMarginChanged(int newValue)
{
    updateTestGridValues();
}

void SetupDialog::movieFieldHPaddingChanged(int newValue)
{
    updateTestGridValues();
}

void SetupDialog::movieFieldVPaddingChanged(int newValue)
{
    updateTestGridValues();
}

void SetupDialog::updateTestGridValues()
{
    if (movieTestGrid != NULL)
    {
        movieTestGrid->setMovieWidth(movieWidthSpinBox->value() / 2);
        movieTestGrid->setMovieHeight(movieHeightSpinBox->value() / 2);
        movieTestGrid->setMovieFieldHorizontalMargin(movieFieldHMarginSpinBox->value() / 2);
        movieTestGrid->setMovieFieldHorizontalPadding(movieFieldHPaddingSpinBox->value() / 2);
        movieTestGrid->setMovieFieldVerticalMargin(movieFieldVMarginSpinBox->value() / 2);        
        movieTestGrid->setMovieFieldVerticalPadding(movieFieldVPaddingSpinBox->value() / 2);

        movieTestGrid->update();
    }
}

void SetupDialog::saveSettings()
{
    QSettings settings;
    settings.setValue("setupDone", QVariant(true));
    settings.setValue("directory", QVariant(directoryEdit->displayText()));
    settings.setValue("movieWidth", QVariant(movieWidthSpinBox->value()));
    settings.setValue("movieHeight", QVariant(movieHeightSpinBox->value()));
    settings.setValue("movieFieldHMargin", QVariant(movieFieldHMarginSpinBox->value()));
    settings.setValue("movieFieldVMargin", QVariant(movieFieldVMarginSpinBox->value()));
    settings.setValue("movieFieldHPadding", QVariant(movieFieldHPaddingSpinBox->value()));
    settings.setValue("movieFieldVPadding", QVariant(movieFieldVPaddingSpinBox->value()));

    settings.setValue("audioLang", QVariant(miscAudioTrackLangComboBox->itemData(miscAudioTrackLangComboBox->currentIndex())));
    settings.setValue("subLang", QVariant(miscSubtitleLangComboBox->itemData(miscSubtitleLangComboBox->currentIndex())));
    settings.setValue("scroll", QVariant(miscScrollComboBox->itemData(miscScrollComboBox->currentIndex())));
}

void SetupDialog::selectDirectory()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                          directoryEdit->displayText(),
                                                          QFileDialog::ShowDirsOnly);
    directoryEdit->setText(directory);
}

void SetupDialog::directorySelected(QString directory)
{
    QDir dir = QDir(directory);
    QPalette pal = directoryEdit->palette();

    if (!dir.exists(directory))
    {
        pal.setColor(QPalette::Text, Qt::red);
    } else {
        pal.setColor(QPalette::Text, Qt::black);
    }

    directoryEdit->setPalette(pal);
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

    saveSettings();
    accept();
}

void SetupDialog::okAndRun()
{
    ok();
    executeMovieList();
}
