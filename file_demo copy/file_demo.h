#ifndef FILE_DEMO_FILE_DEMO_H_
#define FILE_DEMO_FILE_DEMO_H_

#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>

class BaseSink {
 public:
  virtual ~BaseSink() = default;
  virtual void Log(const char* buf, int size) = 0;
  virtual void Flush() = 0;
  virtual int GetTimeout() = 0;
};

class StdoutSink : public BaseSink {
 public:
  StdoutSink();
  void Log(const char* buf, int size) override;
  void Flush() override;
  int GetTimeout() override;

 private:
  FILE* fd_;
};

class FileHelper {
 public:
  void Open(const std::string& filename);
  void Reopen();
  void Flush();
  void Close();
  bool Write(const char* buf, int size);
  // size_t Size() const;
  const std::string& FileName() const;

 private:
  std::string GetDirName(const std::string& filename);
  std::FILE* fd_{nullptr};
  std::string filename_;
};

class RotatingFileSink : public BaseSink {
 public:
  RotatingFileSink(const std::string filename,
                   int max_files,
                   int64_t max_size_);
  virtual ~RotatingFileSink();
  void Log(const char* buf, int size) override;
  void Flush() override;
  int GetTimeout() override;

 private:
  void Rotate();
  std::string CalcFileName(const std::string& filename, int i);
  std::string filename_;
  int max_files_;
  int64_t max_size_;
  int64_t current_size;
  FileHelper file_helper_;
};

class SinkFactory {
 public:
  static std::unique_ptr<BaseSink> CreateSink();
};

#endif  // FILE_DEMO_FILE_DEMO_H_
