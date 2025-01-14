#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class ResourceLoader {
private:
    std::unordered_map<std::string, std::vector<unsigned char>> resources;
    static std::unique_ptr<ResourceLoader> instance;

    static std::string ResolvePath(const std::string& basePath);
    
    // �����ڸ� private����
    ResourceLoader(const std::string& archivePath);
    
public:
    // ���� �����ڿ� ���� ������ ����
    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;
    
    // �ʱ�ȭ �Լ�
    static bool Initialize(const std::string& archivePath);
    
    // �ν��Ͻ� ������
    static ResourceLoader* Get();
    
    // ���ҽ� ���� �Լ���
    const std::vector<unsigned char>* GetResource(const std::string& name) const;
    bool HasResource(const std::string& name) const;
    std::vector<std::string> GetResourceNames() const;
};