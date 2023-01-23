#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
 public:
  MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
    // Create folder label and entry
    folderLabel = new QLabel("Caminho da pasta:", this);
    folderEntry = new QLineEdit(this);
    folderButton = new QPushButton("Procurar", this);
    folderButton->setStyleSheet("background-color: #009688; color: white;");
    connect(folderButton, &QPushButton::clicked, this, &MainWindow::browseFolder);
    QHBoxLayout *folderLayout = new QHBoxLayout();
    folderLayout->addWidget(folderLabel);
    folderLayout->addWidget(folderEntry);
    folderLayout->addWidget(folderButton);

    // Create string label and entry
    stringLabel = new QLabel("Nome da pasta:", this);
    stringEntry = new QLineEdit(this);
    QHBoxLayout *stringLayout = new QHBoxLayout();
    stringLayout->addWidget(stringLabel);
    stringLayout->addWidget(stringEntry);

    // Create submit button
    submitButton = new QPushButton("Enviar", this);
    submitButton->setStyleSheet("background-color: #009688; color: white;");
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::onSubmit);

    // Create message label
    messageLabel = new QLabel(this);

    // Create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(folderLayout);
    mainLayout->addLayout(stringLayout);
    mainLayout->addWidget(submitButton);
    mainLayout->addWidget(messageLabel);

    setLayout(mainLayout);
  }

 private:
  QLabel *folderLabel, *stringLabel, *messageLabel;
  QLineEdit *folderEntry, *stringEntry;
  QPushButton *folderButton, *submitButton;

  void browseFolder() {    
    // Open file dialog to browse for folder
    QString folderPath = QFileDialog::getExistingDirectory(this, "Procurar pasta");
    if (!folderPath.isEmpty()) {
        folderEntry->setText(folderPath);
    }
  }

  void onSubmit() {
    QString folderPath = folderEntry->text();
    QString stringValue = stringEntry->text();

    if (folderPath.isEmpty() || stringValue.isEmpty()) {
        messageLabel->setText("Por favor, preencha todos os campos");
        messageLabel->setStyleSheet("color: red;");
    } else {
        // Run the PowerShell script
        QString script = "teste.ps1";
        QStringList arguments;
        arguments << "-folderPath" << folderPath << "-folderName" << stringValue;
        QProcess::startDetached("powershell.exe", arguments, QDir::currentPath(), &script);

        messageLabel->setText("Arquivos criados com sucesso!");
        messageLabel->setStyleSheet("color: green;");
    }
  }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}