#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "students.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddStudent();
    void onSearchById();
    void onSearchByName();
    void onUpdateScore();
    void refreshTable();

private:
    Students m_students;
    QTableWidget* m_tableWidget;

    QLineEdit* m_idInput;
    QLineEdit* m_nameInput;
    QLineEdit* m_genderInput;
    QLineEdit* m_englishInput;
    QLineEdit* m_mathInput;
    QLineEdit* m_programmingInput;
    QLineEdit* m_dataStructureInput;

    void setupUI();
};