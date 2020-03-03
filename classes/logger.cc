#include "logger.h"

/////////////////////////////////////////////////
/// @brief Adds the last line to the log file.
///
/// Opens the log file and adds a last line containing the
/// time at which the log is finished and closes the file.
/////////////////////////////////////////////////
void Logger::finish() {
  time(&now_);
  log_file_.open(kLogFileName_, std::ofstream::app);
  log_file_ << "--- Log file finished at " << ctime(&now_);
  log_file_.close();
}

/////////////////////////////////////////////////
/// @brief Adds the first line to the log file.
///
/// Creates (or overwrites) the log file and adds the
/// first line containing the time at which the log is started.
/// Then closes the file for further uses.
/////////////////////////////////////////////////
void Logger::start() {
  log_file_.open(kLogFileName_, std::ofstream::trunc);
  time(&now_);
  log_file_ << "--- Log file started at " << ctime(&now_);
  log_file_.close();
}

/////////////////////////////////////////////////
/// @brief Writes and arbitrary message to the log file.
///
/// @param msg a string representing the message to be added.
///
/// Opens the log file and adds a new line at the last position.
/// The message is added with a hh:mm:ss at the begining.
/// Then closes the file for further uses.
/////////////////////////////////////////////////
void Logger::write(const std::string& msg) {
  constexpr auto buffer_size = 80u;
  char buffer[buffer_size];
  std::ofstream log_file;
  std::time_t now;
  const struct tm* time_info;
  log_file.open(kLogFileName_, std::ofstream::app);
  time(&now);
  time_info = localtime(&now);
  strftime(buffer, buffer_size, "%H:%M:%S - ", time_info);
  log_file << buffer << msg << "\n";
  log_file.close();
}
