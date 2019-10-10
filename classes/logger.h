#ifndef KETE_ARKA_CLASSES_LOGGER_H_
#define KETE_ARKA_CLASSES_LOGGER_H_

#include <ctime>
#include <fstream>  

#include "../config.h"

class Logger {
 public:
  Logger() {}
  ~Logger () {
    finish();
  }
  void finish();
  void start();
  static void write(const std::string msg);

 private:
  std::ofstream log_file_;
  std::time_t now_;
};

#endif  // KETE_ARKA_CLASSES_LOGGER_H_