//
// Created by Rakhmon Radjabov on 07/06/23.
//

#ifndef RED_BELT_C___LOGGER_H
#define RED_BELT_C___LOGGER_H
#include "test_runner.h
#include <sstream>

using namespace std;


class Logger {
public:
    explicit Logger(ostream& output_stream);

    void SetLogLine(bool value);
    bool GetLogLine();
    void SetLogFile(bool value);
    bool GetLogFile();

    void Log(const string& message);

private:
    ostream& os;
    bool log_line = false;
    bool log_file = false;
};

Logger::Logger(ostream& output_stream) : os(output_stream) {
}

void Logger::SetLogLine(bool value) { log_line = value; }

bool Logger::GetLogFile() {
    return this->log_file;
}

void Logger::SetLogFile(bool value) { log_file = value; }

bool Logger::GetLogLine() {
    return this->log_line;
}

void Logger::Log(const string& message) {
    if (GetLogFile() && GetLogLine()) {
        os << __FILE__ << " " << __LINE__ << message;
    } else if (GetLogFile()) {
        os << __FILE__ << " " << message;
    } else if (GetLogLine()) {
        os << __LINE__ << " " << message;
    } else {
        os << message;
    }
}

#define LOG(logger, message) \
            logger.Log(message)

void TestLog() {
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"

    ostringstream logs;
    Logger l(logs);
    LOG(l, "hello");

    l.SetLogFile(true);
    LOG(l, "hello");

    l.SetLogLine(true);
    LOG(l, "hello");

    l.SetLogFile(false);
    LOG(l, "hello");

    string expected = "hello\n";
    expected += "logger.cpp hello\n";
    expected += "logger.cpp:10 hello\n";
    expected += "Line 13 hello\n";
    ASSERT_EQUAL(logs.str(), expected);
}



#endif //RED_BELT_C___LOGGER_H
