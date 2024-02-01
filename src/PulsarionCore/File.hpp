#pragma once

#include "Core.hpp"

#include <filesystem>
#include <string>

namespace Pulsarion
{
    class PULSARION_API File
    {
    public:
        static std::string ReadAllText(const std::string& path);

        explicit File(const std::string& path);
        ~File();

        [[nodiscard]] std::filesystem::path GetPath() const;
        [[nodiscard]] std::filesystem::path GetAbsolutePath() const;
        [[nodiscard]] std::filesystem::path GetParentPath() const;
        [[nodiscard]] std::string GetExtension() const;
        [[nodiscard]] std::string GetFileName() const;
        [[nodiscard]] std::string GetFileNameWithoutExtension() const;

        [[nodiscard]] bool Exists() const;
        [[nodiscard]] bool IsDirectory() const;
        [[nodiscard]] bool IsFile() const;

        // Can error, so it returns a bool
        [[nodiscard]] bool CreateDirectory() const;
        [[nodiscard]] bool Delete() const;
        [[nodiscard]] bool CreateFile() const;

        [[nodiscard]] bool Read(std::string& out) const;
        [[nodiscard]] bool Write(const std::string& in) const;
        [[nodiscard]] bool Append(const std::string& in) const;
        [[nodiscard]] bool ReadLines(std::vector<std::string>& out) const;
        [[nodiscard]] bool WriteLines(const std::vector<std::string>& in) const;
        [[nodiscard]] bool AppendLines(const std::vector<std::string>& in) const;
        [[nodiscard]] bool ReadBytes(std::vector<uint8_t>& out) const;
        [[nodiscard]] bool WriteBytes(const std::vector<uint8_t>& in) const;
        [[nodiscard]] bool AppendBytes(const std::vector<uint8_t>& in) const;
        
    private:
        std::filesystem::path m_Path;
        // Maybe in the future cache some meta data or even the content of the file
    };
}
