#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
class QComboBox;
class QDialogButtonBox;
class QGridLayout;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;

class TestMovieWidget;

class SetupDialog : public QDialog
{
    Q_OBJECT

    public:
        SetupDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

    private:
        int screenWidth;
        int screenHeight;

        QLabel *directoryLabel;
        QLineEdit *directoryEdit;
        QPushButton *directorySelectButton;
        QGridLayout *directoryLayout;
        QGroupBox *directoryGroupBox;

        QLabel *movieWidthLabel;
        QLabel *movieHeightLabel;
        QSpinBox *movieWidthSpinBox;
        QSpinBox *movieHeightSpinBox;
        QGridLayout *movieLayout;
        QGroupBox *movieGroupBox;

        QLabel *movieFieldHLabel;
        QLabel *movieFieldVLabel;
        QLabel *movieFieldMarginsLabel;
        QLabel *movieFieldPaddingsLabel;
        QSpinBox *movieFieldHMarginSpinBox;
        QSpinBox *movieFieldVMarginSpinBox;
        QSpinBox *movieFieldHPaddingSpinBox;
        QSpinBox *movieFieldVPaddingSpinBox;
        QGridLayout *movieFieldLayout;
        QGroupBox *movieFieldGroupBox;

        QLabel *miscAudioTrackLangLabel;
        QComboBox *miscAudioTrackLangComboBox;
        QLabel *miscSubtitleLangLabel;
        QComboBox *miscSubtitleLangComboBox;
        QLabel *miscScrollLabel;
        QComboBox *miscScrollComboBox;
        QGridLayout *miscLayout;
        QGroupBox *miscGroupBox;

        TestMovieWidget *movieTestGrid;

        QDialogButtonBox *buttonBox;
        QPushButton *okButton;
        QPushButton *okAndRunButton;

        QGridLayout *dialogLayout;

        int movieHeightValue(int movieWidthValue);
        void updateTestGridValues();
        void saveSettings();

    public slots:
        void selectDirectory();
        void directorySelected(QString directory);

        void movieWidthChanged(int newValue);
        void movieFieldHMarginChanged(int newValue);
        void movieFieldVMarginChanged(int newValue);
        void movieFieldHPaddingChanged(int newValue);
        void movieFieldVPaddingChanged(int newValue);

        void ok();
        void okAndRun();
};

#endif // SETUPDIALOG_H
