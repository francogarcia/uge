/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#pragma once

namespace uge
{

    // Forward declarations for quick reference.
    class IFile;
    class TextFile;
    class BinaryFile;
    class XMLFile;

    namespace File
    {
        /// Defines the read/write mode of the file.
        enum class FileMode : unsigned char
        {
            FileReadOnly,
            FileWriteOnly,
            FileWriteAppend,
            FileReadWrite,

            MemoryBufferReadOnly,
            MemoryBufferWriteOnly,
            MemoryBufferWriteAppend,
            MemoryBufferReadWrite,

            FileUninitialized
        };
    };

    /**
     * @class IFile
     * An abstract interface for file I/O.
     */
    class IFile
    {
    public:

        /// Possible start positions to the file.
        enum class FilePosition : unsigned char
        {
            FileBeginning,
            FileEnd,
            FileCurrent
        };

        /**
         *  Destructor.
         */
        virtual ~IFile()
        {

        }

        /**
         *  Opens a file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        virtual bool OpenFile(const std::string& fileName, const File::FileMode mode) = 0;

        /**
         * Creates a new file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        virtual bool CreateFile(const std::string& fileName, const File::FileMode mode) = 0;

        /**
         *  Closes the file.
         */
        virtual bool CloseFile() = 0;

        /**
         *  Checks whether the file is opened.
         * @return : true if the file is open; false otherwise.
         */
        virtual bool IsOpen() const = 0;

        /**
         *  Checks whether the file has data to be read.
         * @return : true if the file has more data; false is EOF.
         */
        virtual bool IsGood() const = 0;

        /**
         *  Writes data to the file.
         * @param buffer : data to be written.
         * @return : true if the data was written to the file; false otherwise.
         */
        virtual bool Write(const std::string& buffer) = 0;

        /**
         *  Reads data from the file.
         * @return : the data read from the file.
         */
        virtual const std::string Read() = 0;

        /**
         *  Sets the position on which the file will be read.
         * @param position : start position which the file will be read.
         * @param offset : offset from the position.
         */
        virtual void SetReadPosition(const FilePosition position, const int offset = 0) = 0;

        /**
         *  Sets the position on which the file will be written.
         * @param position : start position which the file will be written.
         * @param offset : offset from the position.
         */
        virtual void SetWritePosition(const FilePosition position, const int offset = 0) = 0;

        /**
         *  Gets the current read position of the file.
         * @return : the current position the file is being read.
         */
        virtual const unsigned int GetReadPosition() = 0;

        /**
         *  Gets the current write position of the file.
         * @return : the current position in which the file is being written to.
         */
        virtual const unsigned int GetWritePosition() = 0;

        /**
         *  Gets the name of the file.
         * @return : a string containing the name of file.
         */
        virtual const std::string GetFileName() const
        {
            return m_FileName;
        }

    protected:
        /// The name of the file.
        std::string m_FileName;
    };

    /**
     * @class TextFile
     * An implementation for text file I/O.
     */
    class TextFile : public IFile
    {
    public:
        /**
         *  Constructor.
         */
        TextFile();

        /**
         *  Destructor.
         */
        ~TextFile();

        /**
         *  Opens a text file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        bool OpenFile(const std::string& fileName, const File::FileMode mode);

        /**
         * Creates a new text file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        bool CreateFile(const std::string& fileName, const File::FileMode mode);

        /**
         *  Closes the file.
         */
        bool CloseFile();

        /**
         *  Checks whether the file is openned.
         * @return : true if the file is open; false otherwise.
         */
        bool IsOpen() const;

        /**
         *  Checks whether the file has data to be read.
         * @return : true if the file has more data; false is EOF.
         */
        bool IsGood() const;

        /**
         *  Writes data to the file.
         * @param : data to be written.
         * @return : true if the data was written to the file; false otherwise.
         */
        bool Write(const std::string& buffer);

        /**
         *  Reads data from the file.
         * @return : the data read from the file.
         */
        const std::string Read();

        /**
         *  Sets the position on which the file will be read.
         * @param position : start position which the file will be read.
         * @param offset : offset from the position.
         */
        void SetReadPosition(const FilePosition position, const int offset = 0);

        /**
         *  Sets the position on which the file will be written.
         * @param position : start position which the file will be written.
         * @param offset : offset from the position.
         */
        void SetWritePosition(const FilePosition position, const int offset = 0);

        /**
         *  Gets the current read position of the file.
         * @return : the current position the file is being read.
         */
        const unsigned int GetReadPosition();

        /**
         *  Gets the current write position of the file.
         * @return : the current position in which the file is being written to.
         */
        const unsigned int GetWritePosition();

    private:
        /// The file abstraction.
        std::fstream m_File;

        /// The mode on which the file be opened.
        File::FileMode m_Mode;
    };

    /**
     * @class BinaryFile
     * An implementation for binary file I/O.
     */
    class BinaryFile : public IFile
    {
    public:
        /**
         *  Constructor.
         */
        BinaryFile();

        /**
         *  Destructor.
         */
        ~BinaryFile();

        /**
         *  Opens a binary file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        bool OpenFile(const std::string& fileName, const File::FileMode mode);

        /**
         * Creates a new binary file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        bool CreateFile(const std::string& fileName, const File::FileMode mode);

        /**
         *  Closes the file.
         */
        bool CloseFile();

        /**
         *  Checks whether the file is opened.
         * @return : true if the file is open; false otherwise.
         */
        bool IsOpen() const;

        /**
         *  Checks whether the file has data to be read.
         * @return : true if the file has more data; false is EOF.
         */
        bool IsGood() const;

        /**
         *  Writes data to the file.
         * @param : data to be written.
         * @return : true if the data was written to the file; false otherwise.
         */
        bool Write(const std::string& buffer);

        /**
         *  Reads data from the file.
         * @return : the data read from the file.
         */
        const std::string Read();

        /**
         *  Writes data to the file.
         * @param : data to be written.
         * @return : true if the data was written to the file; false otherwise.
         */
        template<typename T>
        bool Write(const T& buffer);

        /**
         *  Reads data from the file.
         * @return : the data read from the file.
         */
        template<typename T>
        void Read(T& buffer);

        /**
         *  Sets the position on which the file will be read.
         * @param position : start position which the file will be read.
         * @param offset : offset from the position.
         */
        void SetReadPosition(const FilePosition position, const int offset = 0);

        /**
         *  Sets the position on which the file will be written.
         * @param position : start position which the file will be written.
         * @param offset : offset from the position.
         */
        void SetWritePosition(const FilePosition position, const int offset = 0);

        /**
         *  Gets the current read position of the file.
         * @return : the current position the file is being read.
         */
        const unsigned int GetReadPosition();

        /**
         *  Gets the current write position of the file.
         * @return : the current position in which the file is being written to.
         */
        const unsigned int GetWritePosition();

    private:
        /// The file abstraction.
        std::fstream m_File;

        /// The mode on which the file be opened.
        File::FileMode m_Mode;
    };

}
