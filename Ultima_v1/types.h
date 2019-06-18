typedef struct tmove {
  int& operator[](int i) { return b[i]; }
  int b[4];
} tmove;

typedef std::pair< std::vector<std::vector<char> >, bool> pos;