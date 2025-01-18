#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class ResourceLoader {
private:
    std::unordered_map<std::string, std::vector<unsigned char>> resources;
    static std::unique_ptr<ResourceLoader> instance;

    static std::string resolvePath(const std::string& basePath);
    
    // 생성자를 private으로
    ResourceLoader(const std::string& archivePath);
    
public:
    // 복사 생성자와 대입 연산자 삭제
    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;
    
    // 초기화 함수
    static bool initialize(const std::string& archivePath);
    
    // 인스턴스 접근자
    static ResourceLoader* get();
    
    // 리소스 접근 함수들
    const std::vector<unsigned char>* getResource(const std::string& name) const;
    bool hasResource(const std::string& name) const;
    std::vector<std::string> getResourceNames() const;
};