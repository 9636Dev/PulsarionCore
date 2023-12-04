#pragma once

#include "Core.hpp"

#include <string>
#include <filesystem>

namespace Pulsarion
{
    class PULSARION_API File
    {
    public:
        static std::string ReadAllText(const std::string& path);

        File(const std::string& path);
        ~File();

        std::filesystem::path GetPath() const; 
        std::filesystem::path GetAbsolutePath() const;
        std::filesystem::path GetParentPath() const;
        std::string GetExtension() const;
        std::string GetFileName() const;
        std::string GetFileNameWithoutExtension() const;

        bool Exists() const;
        bool IsDirectory() const;
        bool IsFile() const;

        // Can error, so it returns a bool
        bool CreateDirectory() const;
        bool Delete() const;
        bool CreateFile() const;

        bool Read(std::string& out) const;
        bool Write(const std::string& in) const;
        bool Append(const std::string& in) const;
        bool ReadLines(std::vector<std::string>& out) const;
        bool WriteLines(const std::vector<std::string>& in) const;
        bool AppendLines(const std::vector<std::string>& in) const;
        bool ReadBytes(std::vector<uint8_t>& out) const;
        bool WriteBytes(const std::vector<uint8_t>& in) const;
        bool AppendBytes(const std::vector<uint8_t>& in) const;
        
    private:
        std::filesystem::path m_Path;
        // Maybe in the future cache some meta data or even the content of the file
    };
}
