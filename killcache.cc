// Copyright 2012 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <windows.h>

int main(int argc, wchar_t** argv) {
  std::wstring drive(L"\\\\.\\x:");
  if (argc < 2) {
    printf("usage: killcache {drive} [drive...]\n"
           "e.g.:\n"
           "  killcache c d\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    drive[4] = argv[i][0];
    HANDLE file_handle = CreateFile(drive.c_str(),
        FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (file_handle != INVALID_HANDLE_VALUE) {
      CloseHandle(file_handle);
    } else {
      DWORD le = GetLastError();
      if (le != ERROR_SHARING_VIOLATION && le != ERROR_ACCESS_DENIED) {
        fwprintf(stderr, L"Error %d clearing %ls\n", le, drive.c_str());
        return le;
      }
    }
  }
  return 0;
}

