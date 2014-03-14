#include "GameEngineStd.h"

#include "File.h"

#include <Utilities/Debug/Logger.h>

namespace uge
{

    TextFile::TextFile()
    {
        m_Mode = File::FileMode::FileUninitialized;
    }

    TextFile::~TextFile()
    {
        CloseFile();
    }

    bool TextFile::OpenFile(const std::string& fileName, const File::FileMode mode)
    {
        assert(fileName != "" && "Invalid file name!");

        m_FileName = fileName;
        m_Mode = mode;

        m_File.clear();
        switch (m_Mode)
        {
            case File::FileMode::FileReadOnly:
                m_File.open(fileName, std::ios::in);
                break;

            case File::FileMode::FileWriteOnly:
                m_File.open(fileName, std::ios::out);
                break;

            case File::FileMode::FileWriteAppend:
                m_File.open(fileName, std::ios::out | std::ios::app);
                break;

            case File::FileMode::FileReadWrite:
                m_File.open(fileName, std::ios::in | std::ios::out);
                break;

            default:
                LOG_ERROR("Invalid file mode.");
                return false;
        }

        return (m_File && m_File.is_open());
    }

    bool TextFile::CreateFile(const std::string& fileName, const File::FileMode mode)
    {
        assert(fileName != "" && "Invalid file name!");

        m_FileName = fileName;
        m_Mode = mode;

        m_File.clear();
        switch (m_Mode)
        {
            case File::FileMode::FileReadOnly:
                m_File.open(fileName, std::ios::in | std::ios::trunc);
                break;

            case File::FileMode::FileWriteOnly:
            case File::FileMode::FileWriteAppend:
                m_File.open(fileName, std::ios::out | std::ios::trunc);
                break;

            case File::FileMode::FileReadWrite:
                m_File.open(fileName, std::ios::in | std::ios::out | std::ios::trunc);
                break;

            default:
                LOG_ERROR("Invalid file mode.");
                return false;
        }

        return m_File.is_open();
    }

    bool TextFile::CloseFile()
    {
        if (m_File.is_open())
        {
            m_File.close();
        }

        m_Mode = File::FileMode::FileUninitialized;

        return (!m_File.is_open());
    }

    bool TextFile::IsOpen() const
    {
        return (m_File.is_open());
    }

    bool TextFile::IsGood() const
    {
        return (m_File.good());
    }

    bool TextFile::Write(const std::string& buffer)
    {
        if ((m_Mode == File::FileMode::FileWriteOnly ||
             m_Mode == File::FileMode::FileWriteAppend ||
             m_Mode == File::FileMode::FileReadWrite)
            && m_File.is_open())
        {
            m_File << buffer;
            m_File.flush();

            return true;
        }

        return false;
    }

    const std::string TextFile::Read()
    {
        if (m_File.good())
        {
            std::string buffer;
            m_File >> buffer;

            return buffer;
        }

        return "";
    }

    void TextFile::SetReadPosition(const FilePosition position, const int offset)
    {
        m_File.clear();
        switch (position)
        {
            case FilePosition::FileBeginning:
                m_File.seekg(offset, std::ios::beg);
                return;

            case FilePosition::FileEnd:
                m_File.seekg(offset, std::ios::end);

            case FilePosition::FileCurrent:
                m_File.seekg(offset, std::ios::cur);

            default:
                LOG_ERROR("Invalid file position!");
        }
    }

    void TextFile::SetWritePosition(const FilePosition position, const int offset)
    {
        m_File.clear();
        switch (position)
        {
            case FilePosition::FileBeginning:
                m_File.seekp(offset, std::ios::beg);
                return;

            case FilePosition::FileEnd:
                m_File.seekp(offset, std::ios::end);

            case FilePosition::FileCurrent:
                m_File.seekp(offset, std::ios::cur);

            default:
                LOG_ERROR("Invalid file position!");
        }
    }

    const unsigned int TextFile::GetReadPosition()
    {
        return static_cast<unsigned int>(m_File.tellg());
    }

    const unsigned int TextFile::GetWritePosition()
    {
        return static_cast<unsigned int>(m_File.tellp());
    }

    BinaryFile::BinaryFile()
    {
        m_Mode = File::FileMode::FileUninitialized;
    }

    BinaryFile::~BinaryFile()
    {
        CloseFile();
    }

    bool BinaryFile::OpenFile(const std::string& fileName, const File::FileMode mode)
    {
        assert(fileName != "" && "Invalid file name!");

        m_FileName = fileName;
        m_Mode = mode;

        m_File.clear();
        switch (m_Mode)
        {
            case File::FileMode::FileReadOnly:
                m_File.open(fileName, std::ios::in | std::ios::binary);
                break;

            case File::FileMode::FileWriteOnly:
                m_File.open(fileName, std::ios::out | std::ios::binary);
                break;

            case File::FileMode::FileWriteAppend:
                m_File.open(fileName, std::ios::out | std::ios::app | std::ios::binary);
                break;

            case File::FileMode::FileReadWrite:
                m_File.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
                break;

            default:
                LOG_ERROR("Invalid file mode.");
                return false;
        }

        return m_File.is_open();
    }

    bool BinaryFile::CreateFile(const std::string& fileName, const File::FileMode mode)
    {
        assert(fileName != "" && "Invalid file name!");

        m_FileName = fileName;
        m_Mode = mode;

        m_File.clear();
        switch (m_Mode)
        {
            case File::FileMode::FileReadOnly:
                m_File.open(fileName, std::ios::in | std::ios::trunc | std::ios::binary);
                break;

            case File::FileMode::FileWriteOnly:
            case File::FileMode::FileWriteAppend:
                m_File.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary);
                break;

            case File::FileMode::FileReadWrite:
                m_File.open(fileName, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
                break;

            default:
                LOG_ERROR("Invalid file mode.");
                return false;
        }

        return m_File.is_open();
    }

    bool BinaryFile::CloseFile()
    {
        if (m_File.is_open())
        {
            m_File.close();
        }

        m_Mode = File::FileMode::FileUninitialized;

        return (!m_File.is_open());
    }

    bool BinaryFile::IsOpen() const
    {
        return (m_File.is_open());
    }

    bool BinaryFile::IsGood() const
    {
        return (m_File.good());
    }

    bool BinaryFile::Write(const std::string& buffer)
    {
        if ((m_Mode == File::FileMode::FileWriteOnly ||
             m_Mode == File::FileMode::FileWriteAppend ||
             m_Mode == File::FileMode::FileReadWrite)
            && m_File.is_open())
        {
            int size = buffer.length();
            m_File.write(reinterpret_cast<const char*>(&size), sizeof(int));
            m_File.write(buffer.c_str(), buffer.length());
            return true;
        }

        return false;
    }

    const std::string BinaryFile::Read()
    {
        int size;
        m_File.read(reinterpret_cast<char*>(&size), sizeof(int));
        char* buffer = LIB_NEW char[size];
        m_File.read(buffer, size * sizeof(char));

        std::string text(buffer);
        delete [] buffer;
        buffer = nullptr;

        return text;
    }

    template<typename T>
    inline bool BinaryFile::Write(const T& buffer)
    {
        if ((m_Mode == File::FileMode::FileWriteOnly ||
             m_Mode == File::FileMode::FileWriteAppend ||
             m_Mode == File::FileMode::FileReadWrite)
            && m_File.is_open())
        {
            m_File.write(reinterpret_cast<const char*>(&buffer), sizeof(T));
            return true;
        }

        return false;
    }

    template<typename T>
    inline void BinaryFile::Read(T& buffer)
    {
        m_File.read(reinterpret_cast<char*>(&buffer), sizeof(T));
        return true;
    }

    void BinaryFile::SetReadPosition(const FilePosition position, const int offset)
    {
        m_File.clear();
        switch (position)
        {
            case FilePosition::FileBeginning:
                m_File.seekg(offset, std::ios::beg);
                return;

            case FilePosition::FileEnd:
                m_File.seekg(offset, std::ios::end);

            case FilePosition::FileCurrent:
                m_File.seekg(offset, std::ios::cur);

            default:
                LOG_ERROR("Invalid file position!");
        }
    }

    void BinaryFile::SetWritePosition(const FilePosition position, const int offset)
    {
        m_File.clear();
        switch (position)
        {
            case FilePosition::FileBeginning:
                m_File.seekp(offset, std::ios::beg);
                return;

            case FilePosition::FileEnd:
                m_File.seekp(offset, std::ios::end);

            case FilePosition::FileCurrent:
                m_File.seekp(offset, std::ios::cur);

            default:
                LOG_ERROR("Invalid file position!");
        }
    }

    const unsigned int BinaryFile::GetReadPosition()
    {
        return static_cast<unsigned int>(m_File.tellg());
    }

    const unsigned int BinaryFile::GetWritePosition()
    {
        return static_cast<unsigned int>(m_File.tellp());
    }

}
