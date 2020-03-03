#ifndef KETE_ARKA_CLASSES_LOGGER_H_
#define KETE_ARKA_CLASSES_LOGGER_H_

#include <ctime>
#include <fstream>  

class Logger {
 public:
  Logger() { start(); }
  ~Logger () { finish(); }
  static void write(const std::string& msg);

 private:
  void finish();
  void start();
  std::ofstream log_file_;
  std::time_t now_;
  static constexpr auto kLogFileName_ = "kete-arka.log";
};

#endif  // KETE_ARKA_CLASSES_LOGGER_H_