#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "filerix/FileSystem/DriveUtils.h"
#include "filerix/FileSystem/UserUtils.h"
#include "filerix/FileSystem/FileUtils.h"

void create_file(const char *file_path, const char *content)
{
  FILE *file = fopen(file_path, "w");
  if (!file)
  {
    fprintf(stderr, "Failed to create file: %s\n", file_path);
    return;
  }
  fprintf(file, "%s", content);
  fclose(file);
  printf("File created: %s\n", file_path);
}

void create_directory(const char *dir_path)
{
  if (mkdir(dir_path, 0777) == 0)
  {
    printf("Directory created: %s\n", dir_path);
  }
  else
  {
    fprintf(stderr, "Failed to create directory: %s\n", dir_path);
  }
}

int main()
{
  const char *drive_path = "/dev/sda1";

  const DriveUsage usage = GetDriveUsage(drive_path);

  if (usage.used || usage.total)
  {
    printf("Used space: %llu bytes\n", usage.used);
    printf("Total space: %llu bytes\n", usage.total);
  }
  else
  {
    fprintf(stderr, "Failed to get drive usage for %s\n", drive_path);
  }

  DriveList drives = GetDrives();

  if (drives.count < 0)
  {
    printf("No drives found or an error occurred.\n");
    return 1;
  }

  printf("Available Drives:\n");
  for (size_t i = 0; i < drives.count; ++i)
  {
    printf("Device: %s, Status: %s, Mount Point: %s\n",
           drives.drives[i].device,
           drives.drives[i].status,
           drives.drives[i].mountPoint);
  }

  const char *username = GetUserName();

  printf("Current user: %s\n", username);

  char home_dir[512];
  snprintf(home_dir, sizeof(home_dir), "/home/%s/Downloads/TestFolder", username);
  create_directory(home_dir);

  char file_path[512];
  snprintf(file_path, sizeof(file_path), "%s/example.txt", home_dir);
  create_file(file_path, "Hello, Filerix!");

  struct FileList files = GetFiles(home_dir);

  if (files.count == 0)
  {
    printf("No files found in %s\n", home_dir);
  }

  printf("Files in %s:\n", home_dir);
  for (size_t i = 0; i < files.count; i++)
  {
    printf("- %s\n", files.files[i]);
  }

  char search_query[] = "example";
  struct FileList result = SearchFiles(home_dir, search_query);

  if (result.count == 0)
  {
    printf("No files found matching query '%s'\n", search_query);
  }

  printf("Search results for '%s':\n", search_query);
  for (size_t i = 0; i < result.count; i++)
  {
    printf("- %s\n", result.files[i]);
  }

  char new_file_path[512];
  snprintf(new_file_path, sizeof(new_file_path), "%s/renamed_example.txt", home_dir);
  if (Rename(file_path, new_file_path))
  {
    printf("File renamed successfully\n");
  }
  else
  {
    fprintf(stderr, "Failed to rename file\n");
  }

  char copy_path[512];
  snprintf(copy_path, sizeof(copy_path), "%s/copy_example.txt", home_dir);
  if (Copy(new_file_path, copy_path))
  {
    printf("File copied successfully\n");
  }
  else
  {
    fprintf(stderr, "Failed to copy file\n");
  }

  char move_dir[512];
  snprintf(move_dir, sizeof(move_dir), "%s/Moved", home_dir);
  create_directory(move_dir);

  char move_path[512];
  snprintf(move_path, sizeof(move_path), "%s/example_moved.txt", move_dir);
  if (MoveTo(copy_path, move_path))
  {
    printf("File moved successfully\n");
  }
  else
  {
    fprintf(stderr, "Failed to move file\n");
  }

  if (remove(new_file_path) == 0)
  {
    printf("File deleted: %s\n", new_file_path);
  }
  else
  {
    fprintf(stderr, "Failed to delete file\n");
  }

  if (ChangePermissions(move_path, 0644))
  {
    printf("Permissions changed successfully\n");
  }
  else
  {
    fprintf(stderr, "Failed to change permissions\n");
  }

  return 0;
}
