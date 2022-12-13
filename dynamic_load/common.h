#include <iostream>

class Data {
public:
  static Data &GetInstance();

  Data(const Data &) = delete;
  Data &operator=(const Data &&) = delete;

private:
  Data();
  ~Data();
};

static Data &data = Data::GetInstance();