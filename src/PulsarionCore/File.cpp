#include "File.hpp"
#include "Log.hpp"

#include <fstream>
#include <sstream>

namespace Pulsarion
{
    std::string File::ReadAllText(const std::string &path)
    {
        File file(path);
        std::string out;
        if (!file.Read(out))
        {
            PULSARION_CORE_LOG_ERROR("Failed to read file: {0}", path);
            return "";
        }
        return out;
    }

    File::File(const std::string& path)
        : m_Path(path)
    {

    }

    File::~File()
    {

    }

    std::filesystem::path File::GetPath() const
    {
        return m_Path;
    }

    std::filesystem::path File::GetAbsolutePath() const
    {
        return std::filesystem::absolute(m_Path);
    }

    std::filesystem::path File::GetParentPath() const
    {
        return std::filesystem::absolute(m_Path).parent_path();
    }

    std::string File::GetExtension() const
    {
        return std::filesystem::absolute(m_Path).extension().string();
    }

    std::string File::GetFileName() const
    {
        return std::filesystem::absolute(m_Path).filename().string();
    }

    std::string File::GetFileNameWithoutExtension() const
    {
        return std::filesystem::absolute(m_Path).stem().string();
    }

    bool File::Exists() const
    {
        return std::filesystem::exists(m_Path);
    }

    bool File::IsDirectory() const
    {
        return std::filesystem::is_directory(m_Path);
    }

    bool File::IsFile() const
    {
        return std::filesystem::is_regular_file(m_Path);
    }

    bool File::CreateDirectory() const
    {
        try
        {
            return std::filesystem::create_directory(m_Path);
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to create directory: {0}", e.what());
            return false;
        }
    }

    bool File::Delete() const
    {
        try
        {
            return std::filesystem::remove_all(m_Path);
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to delete file: {0}", e.what());
            return false;
        }
    }

    bool File::CreateFile() const
    {
        try
        {
            std::ofstream file(m_Path);
            return file.good();
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to create file: {0}", e.what());
            return false;
        }
    }

    bool File::Read(std::string& out) const
    {
        try
        {
            std::ifstream file(m_Path);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to read file: {0}", m_Path.string());
                return false;
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            out = buffer.str();
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to read file: {0}", e.what());
            return false;
        }
    }

    bool File::Write(const std::string& in) const
    {
        try
        {
            std::ofstream file(m_Path);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to write file: {0}", m_Path.string());
                return false;
            }

            file << in;
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to write file: {0}", e.what());
            return false;
        }
    }

    bool File::Append(const std::string& in) const
    {
        try
        {
            std::ofstream file(m_Path, std::ios_base::app);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to append to file: {0}", m_Path.string());
                return false;
            }

            file << in;
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to append to file: {0}", e.what());
            return false;
        }
    }

    bool File::ReadLines(std::vector<std::string>& out) const
    {
        try
        {
            std::ifstream file(m_Path);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to read file: {0}", m_Path.string());
                return false;
            }

            std::string line;
            while (std::getline(file, line))
            {
                out.push_back(line);
            }
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to read file: {0}", e.what());
            return false;
        }
    }

    bool File::WriteLines(const std::vector<std::string>& in) const
    {
        try
        {
            std::ofstream file(m_Path);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to write file: {0}", m_Path.string());
                return false;
            }

            for (const auto& line : in)
            {
                file << line << '\n';
            }
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to write file: {0}", e.what());
            return false;
        }
    }

    bool File::AppendLines(const std::vector<std::string>& in) const
    {
        try
        {
            std::ofstream file(m_Path, std::ios_base::app);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to append to file: {0}", m_Path.string());
                return false;
            }

            for (const auto& line : in)
            {
                file << line << '\n';
            }
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to append to file: {0}", e.what());
            return false;
        }
    }

    bool File::ReadBytes(std::vector<uint8_t>& out) const
    {
        try
        {
            std::ifstream file(m_Path, std::ios::binary);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to read file: {0}", m_Path.string());
                return false;
            }

            file.seekg(0, std::ios::end);
            out.resize(file.tellg());
            file.seekg(0, std::ios::beg);
            file.read(reinterpret_cast<char*>(out.data()), out.size());
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to read file: {0}", e.what());
            return false;
        }
    }

    bool File::WriteBytes(const std::vector<uint8_t>& in) const
    {
        try
        {
            std::ofstream file(m_Path, std::ios::binary);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to write file: {0}", m_Path.string());
                return false;
            }

            file.write(reinterpret_cast<const char*>(in.data()), in.size());
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to write file: {0}", e.what());
            return false;
        }
    }

    bool File::AppendBytes(const std::vector<uint8_t>& in) const
    {
        try
        {
            std::ofstream file(m_Path, std::ios::binary | std::ios_base::app);
            if (!file.good())
            {
                PULSARION_CORE_LOG_ERROR("Failed to append to file: {0}", m_Path.string());
                return false;
            }

            file.write(reinterpret_cast<const char*>(in.data()), in.size());
            return true;
        }
        catch (const std::exception& e)
        {
            PULSARION_CORE_LOG_ERROR("Failed to append to file: {0}", e.what());
            return false;
        }
    }
}
