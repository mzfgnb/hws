#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QFormLayout>
#include <QSpinBox>
#include <QCheckBox>

// Класс формы анкеты сотрудника
class EmployeeForm : public QWidget {
    Q_OBJECT

public:
    explicit EmployeeForm(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private slots:
    void saveEmployeeData() {
        QMessageBox::information(this, "Сохранение", "Данные сотрудника сохранены!");
    }

private:
    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QGroupBox *personalGroup = new QGroupBox("Личные данные");
        QFormLayout *personalLayout = new QFormLayout(personalGroup);

        QLineEdit *fullNameEdit = new QLineEdit;
        QLineEdit *positionEdit = new QLineEdit;
        QLineEdit *departmentEdit = new QLineEdit;
        QDateEdit *employmentDateEdit = new QDateEdit;
        employmentDateEdit->setCalendarPopup(true);

        personalLayout->addRow("ФИО:", fullNameEdit);
        personalLayout->addRow("Должность:", positionEdit);
        personalLayout->addRow("Подразделение:", departmentEdit);
        personalLayout->addRow("Дата приема:", employmentDateEdit);

        QGroupBox *educationGroup = new QGroupBox("Образование и квалификация");
        QFormLayout *educationLayout = new QFormLayout(educationGroup);

        QTextEdit *educationEdit = new QTextEdit;
        QTextEdit *qualificationEdit = new QTextEdit;
        QTextEdit *coursesEdit = new QTextEdit;

        educationLayout->addRow("Образование:", educationEdit);
        educationLayout->addRow("Квалификация:", qualificationEdit);
        educationLayout->addRow("Курсы повышения:", coursesEdit);

        QGroupBox *achievementsGroup = new QGroupBox("Достижения и результаты");
        QVBoxLayout *achievementsLayout = new QVBoxLayout(achievementsGroup);

        QTextEdit *achievementsEdit = new QTextEdit;
        achievementsEdit->setPlaceholderText("Опишите ваши основные достижения за период...");
        achievementsLayout->addWidget(achievementsEdit);

        QPushButton *saveButton = new QPushButton("Сохранить анкету");
        connect(saveButton, &QPushButton::clicked, this, &EmployeeForm::saveEmployeeData);

        mainLayout->addWidget(personalGroup);
        mainLayout->addWidget(educationGroup);
        mainLayout->addWidget(achievementsGroup);
        mainLayout->addWidget(saveButton);
    }
};

// Класс формы отзыва руководителя
class ManagerReviewForm : public QWidget {
    Q_OBJECT

public:
    explicit ManagerReviewForm(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private slots:
    void saveManagerReview() {
        QMessageBox::information(this, "Сохранение", "Отзыв руководителя сохранен!");
    }

private:
    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QGroupBox *employeeInfoGroup = new QGroupBox("Информация о сотруднике");
        QFormLayout *infoLayout = new QFormLayout(employeeInfoGroup);

        QLineEdit *employeeNameEdit = new QLineEdit;
        QLineEdit *managerNameEdit = new QLineEdit;
        QDateEdit *reviewDateEdit = new QDateEdit;
        reviewDateEdit->setDate(QDate::currentDate());

        infoLayout->addRow("Сотрудник:", employeeNameEdit);
        infoLayout->addRow("Руководитель:", managerNameEdit);
        infoLayout->addRow("Дата отзыва:", reviewDateEdit);

        QGroupBox *performanceGroup = new QGroupBox("Оценка профессиональных качеств");
        QFormLayout *performanceLayout = new QFormLayout(performanceGroup);

        QComboBox *workQualityCombo = new QComboBox;
        workQualityCombo->addItems({"Отлично", "Хорошо", "Удовлетворительно", "Неудовлетворительно"});
        
        QComboBox *responsibilityCombo = new QComboBox;
        responsibilityCombo->addItems({"Высокая", "Средняя", "Низкая"});
        
        QComboBox *initiativeCombo = new QComboBox;
        initiativeCombo->addItems({"Активная", "Умеренная", "Пассивная"});

        performanceLayout->addRow("Качество работы:", workQualityCombo);
        performanceLayout->addRow("Ответственность:", responsibilityCombo);
        performanceLayout->addRow("Инициативность:", initiativeCombo);

        QGroupBox *reviewGroup = new QGroupBox("Отзыв и рекомендации");
        QVBoxLayout *reviewLayout = new QVBoxLayout(reviewGroup);

        QTextEdit *strengthsEdit = new QTextEdit;
        strengthsEdit->setPlaceholderText("Сильные стороны сотрудника...");
        
        QTextEdit *improvementsEdit = new QTextEdit;
        improvementsEdit->setPlaceholderText("Области для улучшения...");
        
        QTextEdit *recommendationsEdit = new QTextEdit;
        recommendationsEdit->setPlaceholderText("Рекомендации по развитию...");

        reviewLayout->addWidget(new QLabel("Сильные стороны:"));
        reviewLayout->addWidget(strengthsEdit);
        reviewLayout->addWidget(new QLabel("Области для улучшения:"));
        reviewLayout->addWidget(improvementsEdit);
        reviewLayout->addWidget(new QLabel("Рекомендации:"));
        reviewLayout->addWidget(recommendationsEdit);

        QPushButton *saveButton = new QPushButton("Сохранить отзыв");
        connect(saveButton, &QPushButton::clicked, this, &ManagerReviewForm::saveManagerReview);

        mainLayout->addWidget(employeeInfoGroup);
        mainLayout->addWidget(performanceGroup);
        mainLayout->addWidget(reviewGroup);
        mainLayout->addWidget(saveButton);
    }
};

// Класс формы аттестационной комиссии
class CommissionForm : public QWidget {
    Q_OBJECT

public:
    explicit CommissionForm(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private slots:
    void conductAttestation() {
        QMessageBox::information(this, "Аттестация", "Решение комиссии принято и записано в протокол!");
    }

    void addEmployeeToTable() {
        int row = employeesTable->rowCount();
        employeesTable->insertRow(row);
        
        employeesTable->setItem(row, 0, new QTableWidgetItem("Иванов И.И."));
        employeesTable->setItem(row, 1, new QTableWidgetItem("Специалист"));
        employeesTable->setItem(row, 2, new QTableWidgetItem("Департамент"));
        employeesTable->setItem(row, 3, new QTableWidgetItem("2024-01-15"));
        
        QComboBox *resultCombo = new QComboBox;
        resultCombo->addItems({"Соответствует", "Соответствует с рекомендациями", "Не соответствует"});
        employeesTable->setCellWidget(row, 4, resultCombo);
    }

private:
    QTableWidget *employeesTable;

    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // Информация о комиссии
        QGroupBox *commissionGroup = new QGroupBox("Состав аттестационной комиссии");
        QFormLayout *commissionLayout = new QFormLayout(commissionGroup);

        QLineEdit *chairmanEdit = new QLineEdit;
        QLineEdit *secretaryEdit = new QLineEdit;
        QTextEdit *membersEdit = new QTextEdit;

        commissionLayout->addRow("Председатель:", chairmanEdit);
        commissionLayout->addRow("Секретарь:", secretaryEdit);
        commissionLayout->addRow("Члены комиссии:", membersEdit);

        // Таблица сотрудников
        QGroupBox *employeesGroup = new QGroupBox("Список аттестуемых сотрудников");
        QVBoxLayout *employeesLayout = new QVBoxLayout(employeesGroup);

        employeesTable = new QTableWidget(0, 5);
        QStringList headers = {"ФИО", "Должность", "Подразделение", "Дата аттестации", "Решение комиссии"};
        employeesTable->setHorizontalHeaderLabels(headers);
        employeesTable->horizontalHeader()->setStretchLastSection(true);

        QPushButton *addEmployeeBtn = new QPushButton("Добавить сотрудника");
        connect(addEmployeeBtn, &QPushButton::clicked, this, &CommissionForm::addEmployeeToTable);

        employeesLayout->addWidget(employeesTable);
        employeesLayout->addWidget(addEmployeeBtn);

        // Протокол заседания
        QGroupBox *protocolGroup = new QGroupBox("Протокол заседания комиссии");
        QVBoxLayout *protocolLayout = new QVBoxLayout(protocolGroup);

        QTextEdit *protocolEdit = new QTextEdit;
        protocolEdit->setPlaceholderText("Введите текст протокола...");
        protocolLayout->addWidget(protocolEdit);

        QPushButton *conductBtn = new QPushButton("Провести аттестацию");
        connect(conductBtn, &QPushButton::clicked, this, &CommissionForm::conductAttestation);

        mainLayout->addWidget(commissionGroup);
        mainLayout->addWidget(employeesGroup);
        mainLayout->addWidget(protocolGroup);
        mainLayout->addWidget(conductBtn);
    }
};

// Главное окно приложения
class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private:
    void setupUI() {
        setWindowTitle("Система аттестации муниципальных служащих");
        setMinimumSize(1000, 700);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // Заголовок
        QLabel *titleLabel = new QLabel("Периодическая аттестация муниципальных служащих");
        titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold; margin: 10px;");
        titleLabel->setAlignment(Qt::AlignCenter);

        // Вкладки
        QTabWidget *tabWidget = new QTabWidget;

        // Создаем формы
        EmployeeForm *employeeForm = new EmployeeForm;
        ManagerReviewForm *managerForm = new ManagerReviewForm;
        CommissionForm *commissionForm = new CommissionForm;

        // Добавляем вкладки
        tabWidget->addTab(employeeForm, "Анкета сотрудника");
        tabWidget->addTab(managerForm, "Отзыв руководителя");
        tabWidget->addTab(commissionForm, "Аттестационная комиссия");

        mainLayout->addWidget(titleLabel);
        mainLayout->addWidget(tabWidget);

        // Статусная строка
        QLabel *statusLabel = new QLabel("Готов к работе");
        statusLabel->setStyleSheet("background-color: #f0f0f0; padding: 5px;");
        mainLayout->addWidget(statusLabel);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Установка русского языка
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
