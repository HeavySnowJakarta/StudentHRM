#include "mainwindow.h"
#include "student.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) { setupUI(); }

void MainWindow::setupUI() {
  qDebug() << "Now setting up UI";
  setWindowTitle("学生成绩管理系统");
  resize(800, 600);

  // Create the window and layouts.
  QWidget* centralWidget = new QWidget(this);
  QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
  QGroupBox* inputGroup = new QGroupBox("学生信息录入");
  QGridLayout* inputLayout = new QGridLayout(inputGroup);

  // The widgets.
  m_idInput = new QLineEdit(this);
  m_nameInput = new QLineEdit(this);
  m_genderInput = new QLineEdit(this); // 如果是下拉框
  m_englishInput = new QLineEdit(this);
  m_mathInput = new QLineEdit(this);
  m_programmingInput = new QLineEdit(this);
  m_dataStructureInput = new QLineEdit(this);

  inputLayout->addWidget(new QLabel("学号:"), 0, 0);
  inputLayout->addWidget(m_idInput, 0, 1);
  inputLayout->addWidget(new QLabel("姓名:"), 0, 2);
  inputLayout->addWidget(m_nameInput, 0, 3);
  inputLayout->addWidget(new QLabel("性别:"), 1, 0);
  inputLayout->addWidget(m_genderInput, 1, 1);
  inputLayout->addWidget(new QLabel("英语:"), 1, 2);
  inputLayout->addWidget(m_englishInput, 1, 3);
  inputLayout->addWidget(new QLabel("数学:"), 2, 0);
  inputLayout->addWidget(m_mathInput, 2, 1);
  inputLayout->addWidget(new QLabel("程序设计:"), 2, 2);
  inputLayout->addWidget(m_programmingInput, 2, 3);
  inputLayout->addWidget(new QLabel("数据结构:"), 3, 0);
  inputLayout->addWidget(m_dataStructureInput, 3, 1);

  QHBoxLayout* buttonLayout = new QHBoxLayout();
  QPushButton* addButton = new QPushButton("添加学生");
  QPushButton* searchByIdButton = new QPushButton("按学号查询");
  QPushButton* searchByNameButton = new QPushButton("按姓名查询");
  QPushButton* updateScoreButton = new QPushButton("更新成绩");
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(searchByIdButton);
  buttonLayout->addWidget(searchByNameButton);
  buttonLayout->addWidget(updateScoreButton);

  // Connect the signal and slots.
  connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddStudent);
  connect(searchByIdButton, &QPushButton::clicked, this, &MainWindow::onSearchById);
  connect(searchByNameButton, &QPushButton::clicked, this, &MainWindow::onSearchByName);
  connect(updateScoreButton, &QPushButton::clicked, this, &MainWindow::onUpdateScore);

  m_tableWidget = new QTableWidget();
  m_tableWidget->setColumnCount(9);
  m_tableWidget->setHorizontalHeaderLabels({"学号", "姓名", "性别", "英语", "数学", "程序设计", "数据结构", "总分", "排名"});

  mainLayout->addWidget(inputGroup);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addWidget(m_tableWidget);

  setCentralWidget(centralWidget);
}

void MainWindow::onAddStudent() {
  try {
    // Get the data from the input fields.
    long long id = m_idInput->text().toLongLong();
    std::string name = m_nameInput->text().toStdString();
    std::string gender_str = m_genderInput->text().toStdString();
    Gender gender;
    int math = m_mathInput->text().toInt();
    int english = m_englishInput->text().toInt();
    int programming = m_programmingInput->text().toInt();
    int dataStructure = m_dataStructureInput->text().toInt();

    // Get the gender.
    if (gender_str == "男") {
      gender = Gender::Male;
    }
    else if (gender_str == "女") {
      gender = Gender::Female;
    }
    else {
      gender = Gender::NonBinary;
    }

    // Initialize and add the student.
    StudentInfo new_student_info(
      gender,
      english,
      math,
      programming,
      dataStructure
    );
    Student new_student(id, name.c_str(), new_student_info);
    m_students.addStudent(new_student);

    // Refresh the widgets.
    refreshTable();
    m_idInput->clear();
    m_nameInput->clear();
    m_genderInput->clear();
    m_mathInput->clear();
    m_englishInput->clear();
    m_programmingInput->clear();
    m_dataStructureInput->clear();
    QMessageBox::information(this, "成功", "学生信息添加成功");
  } catch (const std::string &e) {
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
  catch (const char* e){
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
}

void MainWindow::onSearchById() {
  try {
    long long id = m_idInput->text().toLongLong();
    Student student = m_students.getStudentById(id);
    StudentInfo info = student.getInfo();

    std::string gender_str;
    switch (info.gender) {
    case Gender::Male:
      gender_str = "男";
      break;
    case Gender::Female:
      gender_str = "女";
      break;
    case Gender::NonBinary:
      gender_str = "非二元";
      break;
    }

    // Fill the input fields.
    m_nameInput->setText(student.getName());
    m_genderInput->setText(QString::fromStdString(gender_str));
    m_englishInput->setText(QString::number(info.english_score));
    m_mathInput->setText(QString::number(info.math_score));
    m_programmingInput->setText(QString::number(info.programming_score));
    m_dataStructureInput->setText(QString::number(info.data_structure_score));
  } catch (const std::string &e) {
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
  catch (const char* e){
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
}

void MainWindow::onSearchByName() {
  try {
    std::string name = m_nameInput->text().toStdString();
    Student student = m_students.getStudentByName(name.c_str());
    StudentInfo info = student.getInfo();

    std::string gender_str;
    switch (info.gender) {
    case Gender::Male:
      gender_str = "男";
      break;
    case Gender::Female:
      gender_str = "女";
      break;
    case Gender::NonBinary:
      gender_str = "非二元";
      break;
    }

    // Fill the input fields.
    m_nameInput->setText(student.getName());
    m_genderInput->setText(QString::fromStdString(gender_str));
    m_englishInput->setText(QString::number(info.english_score));
    m_mathInput->setText(QString::number(info.math_score));
    m_programmingInput->setText(QString::number(info.programming_score));
    m_dataStructureInput->setText(QString::number(info.data_structure_score));
  } catch (const std::string &e) {
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
  catch (const char* e){
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
}

void MainWindow::onUpdateScore() {
  try {
    long long id = m_idInput->text().toLongLong();
    // Update the scores.
    m_students.setEnglishScore(id, m_englishInput->text().toInt());
    m_students.setMathScore(id, m_mathInput->text().toInt());
    m_students.setProgrammingScore(id, m_programmingInput->text().toInt());
    m_students.setDataStructureScore(id, m_dataStructureInput->text().toInt());

    // Refresh the table.
    refreshTable();

    QMessageBox::information(this, "成功", "学生成绩更新成功");
  } catch (const std::string &e) {
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
  catch (const char* e){
    QMessageBox::warning(this, "错误", QString::fromStdString(e));
  }
}

void MainWindow::refreshTable() {
  // Get the info.
  const char* info = m_students.getTable();
  m_tableWidget->setRowCount(0);
  QString infoStr(info);
  
  // Split the data.
  QStringList rows = infoStr.split('\n', Qt::SkipEmptyParts);
  m_tableWidget->setRowCount(rows.size());
  
  // Get the data.
  for (int i = 0; i < rows.size(); ++i) {
    QStringList cols = rows[i].split(',');
    if (cols.size() >= 8) {
      m_tableWidget->setItem(i, 0, new QTableWidgetItem(cols[0]));   // Id
      m_tableWidget->setItem(i, 1, new QTableWidgetItem(cols[1]));   // Name
      m_tableWidget->setItem(i, 2, new QTableWidgetItem(cols[2]));   // Gender
      m_tableWidget->setItem(i, 3, new QTableWidgetItem(cols[3]));   // English
      m_tableWidget->setItem(i, 4, new QTableWidgetItem(cols[4]));   // Math
      m_tableWidget->setItem(i, 5, new QTableWidgetItem(cols[5]));   // Programming
      m_tableWidget->setItem(i, 6, new QTableWidgetItem(cols[6]));   // DataStructrue
      m_tableWidget->setItem(i, 7, new QTableWidgetItem(cols[7]));   // TotalScore
      m_tableWidget->setItem(i, 8, new QTableWidgetItem(cols[8]));   // Rank
    }
  }
  // m_tableWidget->resizeColumnsToContents();
  delete[] info;
}