#include "file_demo.h"
#include <errno.h>
#include <linux/limits.h>
#include <string.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

constexpr int kStdoutTimeout = 0;
constexpr int kRotatingFileTimeout = 1000;

StdoutSink::StdoutSink() : fd_(stdout) {}
const char* PRINT_ENV = "PX_LOG";
const char* PRINT = "print";
const char* BASE_FILE = "file";
std::unique_ptr<BaseSink> SinkFactory::CreateSink() {
  char* log_env = getenv(PRINT_ENV);
  if (log_env == nullptr) { return std::make_unique<StdoutSink>(); }
  if (strcmp(log_env, PRINT) == 0) {
    return std::make_unique<StdoutSink>();
  } else if (strcmp(log_env, BASE_FILE) == 0) {
    char path[PATH_MAX]{0};
    if (getcwd(path, sizeof(path)) == nullptr) {
      std::cout << "getcwd failed\n" << std::endl;
      return 0;
    }
    std::string path_str(path);
    std::string filename = path_str + "/px.log";
    return std::make_unique<RotatingFileSink>(filename, 6, 10);
  }
  return std::make_unique<StdoutSink>();
}
void StdoutSink::Log(const char* buf, int size) { fwrite(buf, 1, size, fd_); }

void StdoutSink::Flush() { fflush(fd_); }

int StdoutSink::GetTimeout() { return kStdoutTimeout; }

std::string FileHelper::GetDirName(const std::string& filename) {
  auto pos = filename.find_last_of("/");
  return pos != std::string::npos ? filename.substr(0, pos) : std::string("");
}

void FileHelper::Open(const std::string& filename) {
  Close();
  filename_ = filename;

  // check directory
  if (access(GetDirName(filename).c_str(), F_OK)) {
    char buf[100];
    int len =
        snprintf(buf, sizeof(buf), "%s dir is not exist\n", filename.c_str());
    fwrite(buf, 1, len, stderr);
    return;
  }

  // create dir
  fd_ = fopen(filename.c_str(), "ab");
  if (fd_ == nullptr) {
    char buf[100];
    int len =
        snprintf(buf, sizeof(buf), "create %s failed\n", filename.c_str());
    fwrite(buf, 1, len, stderr);
    return;
  }
}

void FileHelper::Reopen() {
  if (filename_.empty()) {
    char buf[100];
    int len =
        snprintf(buf, sizeof(buf), "cannot reopen, because not open before\n");
    fwrite(buf, 1, len, stderr);
    return;
  }
  this->Open(filename_);
}

bool FileHelper::Write(const char* buf, int size) {
  if (fd_ == nullptr) {
    char buf[100];
    int len =
        snprintf(buf, sizeof(buf), " failed write to file %s errno:%d %s\n",
                 filename_.c_str(), errno, strerror(errno));
    fwrite(buf, 1, len, stderr);
    return false;
  }
  if (std::fwrite(buf, 1, size, fd_) != size) {
    char buf[100];
    int len =
        snprintf(buf, sizeof(buf), "failed write to file %s errno:%d %s\n",
                 filename_.c_str(), errno, strerror(errno));
    fwrite(buf, 1, len, stderr);
    return false;
  }

  return true;
}

void FileHelper::Flush() { std::fflush(fd_); }

const std::string& FileHelper::FileName() const { return filename_; }

void FileHelper::Close() {
  if (fd_ != nullptr) {
    std::fclose(fd_);
    fd_ = nullptr;
  }
}

RotatingFileSink::RotatingFileSink(std::string filename,
                                   int max_files,
                                   int64_t max_size)
    : filename_(filename),
      max_files_(max_files),
      max_size_(max_size),
      current_size(0) {
  file_helper_.Open(filename_);
}

RotatingFileSink::~RotatingFileSink() {
  Flush();
  file_helper_.Close();
}

int RotatingFileSink::GetTimeout() { return kRotatingFileTimeout; }

void RotatingFileSink::Log(const char* buf, int size) {
  current_size += size;
  if (current_size > max_size_) {
    Rotate();
    current_size = size;
  }

  if (!file_helper_.Write(buf, size)) { current_size -= size; }
}

// remove the oldest file, rename other
// ex: (px.log, px.1.log, px.2.log, px.3.log), max_files_ is 3
// rm px.3.log, px.2.log->px.3.log, px.1.log->px.2.log, px.log->px.1.log, create
// px.log
void RotatingFileSink::Rotate() {
  file_helper_.Close();
  for (int i = max_files_; i > 0; --i) {
    std::string src_filename = CalcFileName(filename_, i - 1);
    if (access(src_filename.c_str(), F_OK)) { continue; }

    std::string target_filename = CalcFileName(filename_, i);
    std::rename(src_filename.c_str(), target_filename.c_str());
  }
  file_helper_.Reopen();
}

std::string RotatingFileSink::CalcFileName(const std::string& filename, int i) {
  if (i == 0) { return filename; }
  auto ext_index = filename.find_last_of('.');
  if ((ext_index == std::string::npos) ||
      (ext_index == (filename.size() - 1))) {
    return filename + "." + std::to_string(i);
  }

  return filename.substr(0, ext_index) + "." + std::to_string(i) +
         filename.substr(ext_index, filename.size());
}
void RotatingFileSink::Flush() { file_helper_.Flush(); }
