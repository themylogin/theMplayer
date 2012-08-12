#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

#include "GridLayout.h"
#include "SetupDialogPreview.h"

class SetupDialog : public QDialog
{
    Q_OBJECT

    public:
        SetupDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);

    private:
        int screenWidth;
        int screenHeight;

        QLabel* directoryLabel;
        QLineEdit* directoryEdit;
        QPushButton* directorySelectButton;
        QGridLayout* directoryLayout;
        QGroupBox* directoryGroupBox;

        QLabel* movieWidthLabel;
        QLabel* movieHeightLabel;
        QSpinBox* movieWidthSpinBox;
        QSpinBox* movieHeightSpinBox;
        QGridLayout* movieLayout;
        QGroupBox* movieGroupBox;

        QLabel* movieHPaddingMarginLabel;
        QLabel* movieVPaddingMarginLabel;
        QLabel* moviePaddingLabel;
        QLabel* movieMarginLabel;
        QSpinBox* movieHPaddingSpinBox;
        QSpinBox* movieVPaddingSpinBox;
        QSpinBox* movieHMarginSpinBox;
        QSpinBox* movieVMarginSpinBox;
        QGridLayout* moviePaddingMarginLayout;
        QGroupBox* moviePaddingMarginGroupBox;

        QLabel* miscScrollLabel;
        QComboBox* miscScrollComboBox;
        QGridLayout* miscLayout;
        QGroupBox* miscGroupBox;

        GridLayout* testMovieWidgetGridLayout;
        SetupDialogPreview* testMovieWidget;

        QDialogButtonBox* buttonBox;
        QPushButton* okButton;
        QPushButton* okAndRunButton;

        QGridLayout* dialogLayout;

        int movieHeightFor(int movieWidthValue);
        void updateTestGridValues();
        void saveSettings();

    public slots:
        void selectDirectory();
        void directorySelected(QString directory);

        void movieWidthChanged(int newValue);
        void movieHPaddingChanged(int newValue);
        void movieVPaddingChanged(int newValue);
        void movieHMarginChanged(int newValue);
        void movieVMarginChanged(int newValue);

        void ok();
        void okAndRun();
};

#endif // SETUPDIALOG_H
