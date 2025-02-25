VCPKG_REPO = https://github.com/microsoft/vcpkg.git
PREFIX ?= /usr/local

all: pkgconfig

pkgconfig:
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build .

vcpkg: check-vcpkg setup-vcpkg-port
	@echo "Bootstrapping vcpkg..."
	./vcpkg/bootstrap-vcpkg.sh || { echo "Failed to bootstrap vcpkg"; exit 1; }
	@echo "Installing dependencies with vcpkg..."
	./vcpkg/vcpkg --feature-flags=manifests install --triplet x64-linux-release || { echo "Failed to install dependencies"; exit 1; }
	@echo "Generating build files with CMake..."
	mkdir -p build
	cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake .. || { echo "Failed to generate CMake build files"; exit 1; }
	@echo "Building the project..."
	cd build && cmake --build . --parallel || { echo "Build failed"; exit 1; }
	@echo "Build complete!"

setup-vcpkg-port:
	@if [ ! -d "./vcpkg/ports/filerix" ]; then \
		echo "Downloading filerix vcpkg port..."; \
		git clone --recurse-submodules https://github.com/filesverse/vcpkg-port.git vcpkg-port || { echo "Failed to download filerix vcpkg port"; exit 1; }; \
		echo "Copying filerix vcpkg port..."; \
		mv ./vcpkg-port ./vcpkg/ports/filerix || { echo "Failed to copy filerix vcpkg port"; exit 1; }; \
	fi

check-vcpkg:
	@if [ ! -d "./vcpkg" ] || [ -z "$$(ls -A ./vcpkg 2>/dev/null)" ]; then \
		echo "vcpkg is missing or empty. Cloning vcpkg..."; \
		git clone $(VCPKG_REPO) vcpkg || { echo "Failed to clone vcpkg"; exit 1; }; \
	fi

meson:
	meson setup build --reconfigure
	ninja -C build

clean:
	@echo "Cleaning build directory..."
	rm -rf build vcpkg_installed vcpkg-port vcpkg
	@echo "Clean complete!"

.PHONY: all pkgconfig vcpkg uninstall clean
