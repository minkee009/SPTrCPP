#include "resource_loader.hpp"
#include <stdexcept>

#define MINIZ_IMPLEMENTATION
#include "miniz.h"

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

std::unique_ptr<ResourceLoader> ResourceLoader::instance = nullptr;

std::string ResourceLoader::ResolvePath(const std::string& basePath){
#if defined(__APPLE__)
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        std::string pathString = std::string(path);
        // .app/Contents/MacOS 문자열이 경로에 포함되어 있는지 확인
        if (pathString.find(".app/Contents/MacOS") != std::string::npos) {
            // 앱 번들 내부에서 실행 중
            size_t pos = pathString.find_last_of("/\\");
            if (pos != std::string::npos) {
                // ../Resources 경로 사용
                return pathString.substr(0, pos) + "/../Resources/" + basePath;
            }
        } else {
            // 일반 실행 파일로 실행 중
            size_t pos = pathString.find_last_of("/\\");
            if (pos != std::string::npos) {
                // 실행 파일과 같은 디렉토리 사용
                return pathString.substr(0, pos) + "/" + basePath;
            }
        }
    }
#endif
    return basePath;
}

ResourceLoader::ResourceLoader(const std::string& archivePath) {
    mz_zip_archive zip = {};
    
    if (!mz_zip_reader_init_file(&zip, archivePath.c_str(), 0)) {
        throw std::runtime_error("Failed to open archive: " + archivePath);
    }

    mz_uint numFiles = mz_zip_reader_get_num_files(&zip);
    for (mz_uint i = 0; i < numFiles; i++) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(&zip, i, &file_stat)) {
            continue;
        }

        if (mz_zip_reader_is_file_a_directory(&zip, i)) {
            continue;
        }

        std::vector<unsigned char> buffer(file_stat.m_uncomp_size);
        if (!mz_zip_reader_extract_to_mem(&zip, i, buffer.data(), buffer.size(), 0)) {
            continue;
        }

        resources[file_stat.m_filename] = std::move(buffer);
    }

    mz_zip_reader_end(&zip);
}

bool ResourceLoader::Initialize(const std::string& archivePath) {
    if (!instance) {
        try {
            instance = std::unique_ptr<ResourceLoader>(new ResourceLoader(ResolvePath(archivePath)));
            return true;
        } catch (...) {
            return false;
        }
    }
    return true;
}

ResourceLoader* ResourceLoader::Get() {
    return instance.get();
}

const std::vector<unsigned char>* ResourceLoader::GetResource(const std::string& name) const {
    auto it = resources.find(name);
    return (it != resources.end()) ? &it->second : nullptr;
}

bool ResourceLoader::HasResource(const std::string& name) const {
    return resources.find(name) != resources.end();
}

std::vector<std::string> ResourceLoader::GetResourceNames() const {
    std::vector<std::string> names;
    names.reserve(resources.size());
    for (const auto& pair : resources) {
        names.push_back(pair.first);
    }
    return names;
}