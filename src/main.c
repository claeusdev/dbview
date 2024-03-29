#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "common.h"
#include "file.h"

void print_usage(char *argv[]) {
  printf("Usage: %s -n -f <database file>\n", argv[0]);
  printf("\t -n - create a new database file\n");
  printf("\t -f - (required) path to database file\n");
  return;
}

void check_valid_filepath(char *filepath, char *argv[]) {
  printf("Filepath is a required argument\n");
  print_usage(argv);
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;
  bool newfile = false;
  int c;
  int dbfd = -1;

  while ((c = getopt(argc, argv, "nf:")) != -1) {
    switch (c) {
    case 'n':
      newfile = true;
      break;
    case 'f':
      filepath = optarg;
      break;
    case '?':
      printf("Unknown option -%d\n", c);
      break;
    default:
      return -1;
    }
  }

  if (filepath == NULL) {
    check_valid_filepath(filepath, argv);
    return 0;
  }

  if (newfile) {
    dbfd = create_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      printf("Unable to create database file\n");
      return STATUS_ERROR;
    }
  } else {
    dbfd = open_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      printf("Unable to open database file\n");
      return STATUS_ERROR;
    }
  }

  return 0;
}
