#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <unordered_map>
#include <memory>

template <typename Resource, typename Identifier>
class ResourceHolder {
    public:
        void set(const Identifier id, const Resource& resource);
        void set(const Identifier id, std::unique_ptr<Resource> resource);
        void remove(const Identifier id);
        Resource& get(const Identifier id);
        const Resource& get(const Identifier id) const;
        bool has(const Identifier id) const;

    private:
        void insertResource(Identifier id, std::unique_ptr<Resource> resource);
        
        std::unordered_map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

#include "ResourceHolder.inl"

#endif // RESOURCE_HOLDER_HPP