from filerix.driveUtils import getDrives
from filerix.fileUtils import getFiles
from filerix.userUtils import getUserName

def main():
    print("Listing available drives...")
    drives = getDrives()

    if not drives:
        print("No drives found.")
        return

    for drive in drives:
        print(f"Device: {drive.device}, Mount Point: {drive.mountPoint}, FS Type: {drive.fsType}")

    files = getFiles("/")

    for file in files:
        print(f"Name: {file.name}, Path: {file.path}, Size: {file.size}, Directory: {file.isDirectory}")

    print("Current user:", getUserName())
if __name__ == "__main__":
    main()
