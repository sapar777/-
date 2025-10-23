#include <iostream>
#include <string>
#include <vector>
#include <limits> 
#include "locale.h"

class FreightCompany {
private:
    std::string companyName;
    double paymentPerTon;
    double totalWeightShipped;
    double totalRevenue;
    const double WEIGHT_LIMIT = 1000.0;
    const double PAYMENT_LIMIT = 1000.0;

public:

    FreightCompany(const std::string& name, double payment)
        : companyName(name), totalWeightShipped(0), totalRevenue(0) {
        setPaymentPerTon(payment); 
    }

  
    std::string getCompanyName() const {
        return companyName;
    }

    double getPaymentPerTon() const {
        return paymentPerTon;
    }

    double getTotalWeightShipped() const {
        return totalWeightShipped;
    }

    double getTotalRevenue() const {
        return totalRevenue;
    }

    double getWeightLimit() const {
        return WEIGHT_LIMIT;
    }

    double getPaymentLimit() const {
        return PAYMENT_LIMIT;
    }

 
    void setCompanyName(const std::string& name) {
        if (!name.empty()) {
            companyName = name;
        }
    }

    void setPaymentPerTon(double payment) {
        if (payment <= 0) {
            std::cout << "Ошибка: оплата за тонну должна быть положительной!" << std::endl;
            return;
        }

        if (payment > PAYMENT_LIMIT) {
            std::cout << "Ошибка: оплата за тонну не может превышать " << PAYMENT_LIMIT << " руб.!" << std::endl;
            return; 
        }
        else {
            paymentPerTon = payment;
        }

        
        totalRevenue = totalWeightShipped * paymentPerTon;
    }

    
    void addShipment(double weight) {
        if (weight <= 0) {
            std::cout << "Ошибка: вес должен быть положительным!" << std::endl;
            return;
        }

        if (totalWeightShipped + weight > WEIGHT_LIMIT) {
            double available = WEIGHT_LIMIT - totalWeightShipped;
            std::cout << "Ошибка: превышено ограничение в " << WEIGHT_LIMIT << " тонн!" << std::endl;
            std::cout << "Доступно для перевозки: " << available << " тонн" << std::endl;
            return;
        }

        totalWeightShipped += weight;
        totalRevenue = totalWeightShipped * paymentPerTon;
        std::cout << "Добавлена перевозка: " << weight << " тонн" << std::endl;
        std::cout << "Всего перевезено: " << totalWeightShipped << " тонн из " << WEIGHT_LIMIT << " тонн" << std::endl;
    }

    
    double calculateTotalRevenue() const {
        return totalWeightShipped * paymentPerTon;
    }

    
    void displayCompanyInfo() const {
        std::cout << "\n=== Информация о фирме ===" << std::endl;
        std::cout << "Наименование: " << companyName << std::endl;
        std::cout << "Оплата за тонну: " << paymentPerTon << " руб." << std::endl;
        std::cout << "Лимит оплаты за тонну: " << PAYMENT_LIMIT << " руб." << std::endl;
        std::cout << "Перевезено грузов: " << totalWeightShipped << " тонн" << std::endl;
        std::cout << "Лимит перевозок: " << WEIGHT_LIMIT << " тонн" << std::endl;
        std::cout << "Общая выручка: " << totalRevenue << " руб." << std::endl;
        std::cout << "==========================" << std::endl;
    }
};


double getDoubleInput(const std::string& prompt, double maxValue = -1) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число: ";
        }
        else if (maxValue > 0 && value > maxValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: значение не может превышать " << maxValue << "!" << std::endl;
            std::cout << "Пожалуйста, введите значение не больше " << maxValue << ": ";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}


std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "=== СИСТЕМА УЧЕТА ФИРМЫ ГРУЗОПЕРЕВОЗОК ===" << std::endl;

    
    std::string companyName = getStringInput("Введите наименование фирмы: ");
    double paymentPerTon;

   
    while (true) {
        paymentPerTon = getDoubleInput("Введите оплату за перевозку одной тонны (руб.): ", 1000.0); 
        if (paymentPerTon <= 1000.0) {
            break;
        }
        std::cout << "Ошибка: оплата за тонну не может превышать 1000 руб.! Попробуйте снова." << std::endl;
    }

 
    FreightCompany company(companyName, paymentPerTon);

    int choice;
    do {
        std::cout << "\n=== МЕНЮ ===" << std::endl;
        std::cout << "1. Добавить перевозку" << std::endl;
        std::cout << "2. Показать информацию о фирме" << std::endl;
        std::cout << "3. Рассчитать общую выручку" << std::endl;
        std::cout << "4. Изменить оплату за тонну" << std::endl;
        std::cout << "5. Изменить название фирмы" << std::endl;
        std::cout << "6. Показать лимиты" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: {
            double weight = getDoubleInput("Введите массу перевезенного груза (тонн): ");
            company.addShipment(weight);
            break;
        }
        case 2:
            company.displayCompanyInfo();
            break;
        case 3:
            std::cout << "\nОбщая выручка фирмы: " << company.calculateTotalRevenue() << " руб." << std::endl;
            break;
        case 4: {
            double newPayment;
            while (true) {
                newPayment = getDoubleInput("Введите новую оплату за тонну (руб.): ", 1000.0); 
                if (newPayment <= 1000.0) {
                    company.setPaymentPerTon(newPayment);
                    break;
                }
                std::cout << "Ошибка: оплата за тонну не может превышать 1000 руб.! Попробуйте снова." << std::endl;
            }
            break;
        }
        case 5: {
            std::string newName = getStringInput("Введите новое название фирмы: ");
            company.setCompanyName(newName);
            std::cout << "Название фирмы обновлено!" << std::endl;
            break;
        }
        case 6:
            std::cout << "\n=== ЛИМИТЫ СИСТЕМЫ ===" << std::endl;
            std::cout << "Лимит перевозок: " << company.getWeightLimit() << " тонн" << std::endl;
            std::cout << "Перевезено: " << company.getTotalWeightShipped() << " тонн" << std::endl;
            std::cout << "Доступно: " << company.getWeightLimit() - company.getTotalWeightShipped() << " тонн" << std::endl;
            std::cout << "Лимит оплаты за тонну: " << company.getPaymentLimit() << " руб." << std::endl;
            std::cout << "Текущая оплата за тонну: " << company.getPaymentPerTon() << " руб." << std::endl;
            break;
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
        }

    } while (choice != 0);

   
    std::cout << "\n=== ФИНАЛЬНАЯ ИНФОРМАЦИЯ ===" << std::endl;
    company.displayCompanyInfo();

    return 0;
}