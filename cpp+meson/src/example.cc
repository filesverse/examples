#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "filerix/FileSystem/DriveUtils.h"
#include "filerix/FileSystem/UserUtils.h"
#include "filerix/FileSystem/FileUtils.h"

namespace fs = std::filesystem;

void createFile(const std::string &filePath, const std::string &content)
{
  std::ofstream file(filePath);
  if (!file)
  {
    std::cerr << "Failed to create file: " << filePath << std::endl;
    return;
  }
  file << content;
  file.close();
  std::cout << "File created: " << filePath << std::endl;
}

void createDirectory(const std::string &dirPath)
{
  if (fs::create_directories(dirPath))
  {
    std::cout << "Directory created: " << dirPath << std::endl;
  }
  else
  {
    std::cerr << "Failed to create directory: " << dirPath << std::endl;
  }
}

int main()
{
  std::string drivePath = "/dev/sda1";

  auto [usedBytes, totalBytes] = DriveUtils::GetDriveUsage(drivePath);
  std::cout << "Used space: " << usedBytes << " bytes" << std::endl;
  std::cout << "Total space: " << totalBytes << " bytes" << std::endl;

  auto drives = DriveUtils::GetDrives();
  if (drives.empty())
  {
    std::cout << "No drives found." << std::endl;
  }
  else
  {
    std::cout << "Available Drives:" << std::endl;
    for (const auto &drive : drives)
    {
      std::cout << "Device: " << drive.device << std::endl;
    }
  }

  std::string username = UserUtils::GetUserName();
  if (!username.empty())
  {
    std::cout << "Current user: " << username << std::endl;
  }
  else
  {
    std::cerr << "Failed to get username" << std::endl;
  }

  std::string homeDir = "/home/" + username + "/Downloads/TestFolder";
  createDirectory(homeDir);

  std::string filePath = homeDir + "/example.txt";
  createFile(filePath, "Hello, Filerix!");

  auto files = FileUtils::GetFiles(homeDir);
  if (files.empty())
  {
    std::cout << "No files found in " << homeDir << std::endl;
  }
  else
  {
    std::cout << "Files in " << homeDir << ":" << std::endl;
    for (const auto &file : files)
    {
      std::cout << "- " << file.name << std::endl;
    }
  }

  std::string searchQuery = "example";
  auto foundFiles = FileUtils::SearchFiles(homeDir, searchQuery);
  if (foundFiles.empty())
  {
    std::cout << "No files found matching query '" << searchQuery << "'" << std::endl;
  }
  else
  {
    std::cout << "Search results for '" << searchQuery << "':" << std::endl;
    for (const auto &file : foundFiles)
    {
      std::cout << "- " << file.name << std::endl;
    }
  }

  std::string newFilePath = homeDir + "/renamed_example.txt";
  if (FileUtils::Rename(filePath, newFilePath))
  {
    std::cout << "File renamed successfully" << std::endl;
  }
  else
  {
    std::cerr << "Failed to rename file" << std::endl;
  }

  std::string copyPath = homeDir + "/copy_example.txt";
  if (FileUtils::Copy(newFilePath, copyPath))
  {
    std::cout << "File copied successfully" << std::endl;
  }
  else
  {
    std::cerr << "Failed to copy file" << std::endl;
  }

  std::string moveDir = homeDir + "/Moved";
  createDirectory(moveDir);
  std::string movePath = moveDir + "/example_moved.txt";

  if (FileUtils::MoveTo(copyPath, movePath))
  {
    std::cout << "File moved successfully" << std::endl;
  }
  else
  {
    std::cerr << "Failed to move file" << std::endl;
  }

  if (fs::remove(newFilePath))
  {
    std::cout << "File deleted: " << newFilePath << std::endl;
  }
  else
  {
    std::cerr << "Failed to delete file" << std::endl;
  }

  if (UserUtils::ChangePermissions(movePath, 0644))
  {
    std::cout << "Permissions changed successfully" << std::endl;
  }
  else
  {
    std::cerr << "Failed to change permissions" << std::endl;
  }

  return 0;
}
