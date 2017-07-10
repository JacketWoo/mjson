#include <stdio.h>
#include <string.h>
#include <iostream>

#include "mjson.h"


void Usage() {
  fprintf(stderr, "Usage:\n\t ./mjson_sample mjson_file");
}

uint32_t ReadByte(char* buf, uint32_t num, FILE* fp) {
  uint32_t nread = 0, s_read = 0;
  while (!feof(fp)) {
    nread = fread(buf + s_read, 1, num - s_read, fp);
    if (nread == 0) { /* error or end-of-file */
      return 0;
    }
    s_read += nread;
    if (s_read == num) {
      return num;
    }
  }
  return 0;
}

void TrimSpace(std::string* str) {
  static std::string SPACE_STR=" \t\n";
  if (!str || str->empty()) {
    return;
  }
  size_t st = str->find_first_not_of(SPACE_STR);
  if (st == std::string::npos) {
    str->clear();
    return;
  }
  size_t ed = str->find_last_not_of(SPACE_STR);
  if (st == 0 && ed == str->size()-1) {
    return;
  }
  *str = str->substr(st, ed-st+1);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    Usage();
    return -1;
  }
  FILE* fp = fopen(argv[1], "rb");    
  if (!fp) {
    fprintf(stderr, "fopen file: %s failed, error: %s\n", argv[1], strerror(errno));
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  int32_t fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  if (fsize < 0) {
    fprintf(stderr, "ftell error: %s\n", strerror(errno));
    return -1;
  }
  char *buf = reinterpret_cast<char*>(calloc(fsize+1, 1));
  if (!buf) {
    fprintf(stderr, "cmalloc failed, error: %s\n", strerror(errno));
    return -1;
  }
  if (!ReadByte(buf, fsize, fp)) {
    delete buf;
    return -1;
  }
 
  mjson::JsonInterpreter j_ipt;
  mjson::Json json;  

  std::string json_str(buf, fsize);
  delete buf;
  TrimSpace(&json_str);

  if (j_ipt.Decode(json_str, &json) == -1) {
    fprintf(stderr, "decode failed1\n"); 
    return -1;
  }
  std::cout << "origin json:" << std::endl;
  std::cout << json.GetHstr() << std::endl;
  
  json_str = json.Encode();
  std::cout << json_str << std::endl;
  if (j_ipt.Decode(json_str, &json) == -1) {
    fprintf(stderr, "decode failed2\n"); 
    return -1;
  }
  std::cout << "encoded-decoded json:" << std::endl;
  std::cout << json.GetHstr() << std::endl; 
  


  return 0;
}
