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

#include "GameEngineStd.h"

#include "XMLFile.h"

#include <Utilities/Debug/Logger.h>
#include <Utilities/Util.h>

namespace uge
{

    XMLNode::XMLNode() : m_pTinyXMLNode(nullptr)
    {

    }

    XMLNode::XMLNode(tinyxml2::XMLNode* pTinyXMLNode) : m_pTinyXMLNode(pTinyXMLNode)
    {

    }

    XMLNode::~XMLNode()
    {
        m_pTinyXMLNode = nullptr;
    }

    bool XMLNode::IsGood() const
    {
        return (m_pTinyXMLNode != nullptr);
    }

    bool XMLNode::IsLeaf() const
    {
        return (m_pTinyXMLNode->NoChildren());
    }

    XMLNode XMLNode::GetFirstChild() const
    {
        tinyxml2::XMLNode* xmlFirstChildNode = m_pTinyXMLNode->FirstChild();

        return XMLNode(xmlFirstChildNode);
    }

    XMLElement XMLNode::GetFirstChildElement(const char* pChildName)
    {
        tinyxml2::XMLElement* xmlFirstChildElement;
        xmlFirstChildElement = m_pTinyXMLNode->FirstChildElement(pChildName);

        return XMLElement(xmlFirstChildElement);
    }

    XMLElement XMLNode::GetFirstChildElement(const std::string& childName)
    {
        return GetFirstChildElement(childName.c_str());
    }

    XMLNode XMLNode::GetNextSibling() const
    {
        tinyxml2::XMLNode* tinyXMLNextNode = m_pTinyXMLNode->NextSibling();

        return XMLNode(tinyXMLNextNode);
    }

    XMLElement XMLNode::GetNextSiblingElement(const char* pSiblingName)
    {
        tinyxml2::XMLElement* xmlNextSiblingElement;
        xmlNextSiblingElement = m_pTinyXMLNode->NextSiblingElement(pSiblingName);

        return XMLElement(xmlNextSiblingElement);
    }

    XMLElement XMLNode::GetNextSiblingElement(const std::string& siblingName)
    {
        return GetNextSiblingElement(siblingName.c_str());
    }

    XMLNode XMLNode::GetPreviousSibling() const
    {
        tinyxml2::XMLNode* tinyXMLPreviousNode = m_pTinyXMLNode->PreviousSibling();

        return XMLNode(tinyXMLPreviousNode);
    }

    XMLElement XMLNode::GetPreviousSiblingElement(const char* pSiblingName)
    {
        tinyxml2::XMLElement* xmlPreviousSiblingElement;
        xmlPreviousSiblingElement = m_pTinyXMLNode->PreviousSiblingElement(pSiblingName);

        return XMLElement(xmlPreviousSiblingElement);
    }

    XMLElement XMLNode::GetPreviousSiblingElement(const std::string& siblingName)
    {
        return GetPreviousSiblingElement(siblingName.c_str());
    }

    XMLNode XMLNode::GetLastChild() const
    {
        tinyxml2::XMLNode* xmlLastChildNode = m_pTinyXMLNode->LastChild();

        return XMLNode(xmlLastChildNode);
    }

    XMLElement XMLNode::GetLastChildElement(const char* pChildName)
    {
        tinyxml2::XMLElement* xmlLastChildElement;
        xmlLastChildElement = m_pTinyXMLNode->LastChildElement(pChildName);

        return XMLElement(xmlLastChildElement);
    }

    XMLElement XMLNode::GetLastChildElement(const std::string& childName)
    {
        return GetLastChildElement(childName.c_str());
    }

    XMLNode XMLNode::GetParent() const
    {
        tinyxml2::XMLNode* xmlParentNode = m_pTinyXMLNode->Parent();

        return XMLNode(xmlParentNode);
    }

    bool XMLNode::IsElement() const
    {
        tinyxml2::XMLElement* pXMLElement = m_pTinyXMLNode->ToElement();

        return (pXMLElement != nullptr);
    }

    XMLElement XMLNode::GetElement() const
    {
        tinyxml2::XMLElement* pXMLElement = m_pTinyXMLNode->ToElement();

        if (pXMLElement == nullptr)
        {
            LOG_ERROR("Invalid XML element!");
        }

        return XMLElement(pXMLElement);
    }

    void XMLNode::SetNodeValue(const std::string& value)
    {
        m_pTinyXMLNode->SetValue(value.c_str());
    }

    void XMLNode::SetNodeValue(const std::wstring& value)
    {
        SetNodeValue(WStringToString(value));
    }

    const std::string XMLNode::GetNodeValue() const
    {
        if (m_pTinyXMLNode != nullptr)
        {
            const char* value = m_pTinyXMLNode->Value();

            if (value != nullptr)
            {
                return value;
            }
        }

        return "";
    }

    const std::string XMLNode::GetNodeValueLowerCase() const
    {
        return StringToLower(GetNodeValue());
    }

    const std::string XMLNode::GetNodeValueUpperCase() const
    {
        return StringToUpper(GetNodeValue());
    }

    const std::wstring XMLNode::GetNodeWValue() const
    {
        return StringToWString(GetNodeValue());
    }

    const std::wstring XMLNode::GetNodeWValueLowerCase() const
    {
        return WStringToLower(GetNodeWValue());
    }

    const std::wstring XMLNode::GetNodeWValueUpperCase() const
    {
        return WStringToUpper(GetNodeWValue());
    }

    XMLElement::XMLElement() : m_pTinyXMLElement(nullptr)
    {

    }

    XMLElement::XMLElement(tinyxml2::XMLElement* pTinyXMLElement)
        : XMLNode(pTinyXMLElement), m_pTinyXMLElement(pTinyXMLElement)
    {

    }

    XMLElement::~XMLElement()
    {
        m_pTinyXMLElement = nullptr;
    }

    std::string XMLElement::GetElementName()
    {
        return m_pTinyXMLElement->Name();
    }

    std::string XMLElement::GetElementNameLowerCase()
    {
        return StringToLower(GetElementName());
    }

    std::string XMLElement::GetElementNameUpperCase()
    {
        return StringToUpper(GetElementName());
    }

    std::wstring XMLElement::GetElementWName()
    {
        return StringToWString(m_pTinyXMLElement->Name());
    }

    std::wstring XMLElement::GetElementWNameLowerCase()
    {
        return WStringToLower(GetElementWName());
    }

    std::wstring XMLElement::GetElementWNameUpperCase()
    {
        return WStringToUpper(GetElementWName());
    }

    void XMLElement::SetElementName(const std::string& attributeName)
    {
        m_pTinyXMLElement->SetName(attributeName.c_str());
    }

    void XMLElement::SetElementName(const std::wstring& attributeName)
    {
        m_pTinyXMLElement->SetName(WStringToString(attributeName).c_str());
    }

    bool XMLElement::GetElementAsText(std::string& elementText) const
    {
        const char* pText = m_pTinyXMLElement->GetText();

        if (pText != nullptr)
        {
            elementText = pText;

            return true;
        }

        return false;
    }

    bool XMLElement::GetElementAsTextLowerCase(std::string& elementText) const
    {
        if (!GetElementAsText(elementText))
        {
            return false;
        }

        elementText = StringToLower(elementText);

        return true;
    }

    bool XMLElement::GetElementAsTextUpperCase(std::string& elementText) const
    {
        if (!GetElementAsText(elementText))
        {
            return false;
        }

        elementText = StringToUpper(elementText);

        return true;
    }

    bool XMLElement::GetElementAsText(std::wstring& elementText) const
    {
        const char* pText = m_pTinyXMLElement->GetText();

        if (pText != nullptr)
        {
            elementText = StringToWString(pText);

            return true;
        }

        return false;
    }

    bool XMLElement::GetElementAsTextLowerCase(std::wstring& elementText) const
    {
        if (!GetElementAsText(elementText))
        {
            return false;
        }

        elementText = WStringToLower(elementText);

        return true;
    }

    bool XMLElement::GetElementAsTextUpperCase(std::wstring& elementText) const
    {
        if (!GetElementAsText(elementText))
        {
            return false;
        }

        elementText = WStringToUpper(elementText);

        return true;
    }

    XMLAttribute XMLElement::GetFirstAttribute() const
    {
        //tinyxml2::XMLAttribute* xmlFirstChildAttribute;
        const tinyxml2::XMLAttribute* xmlAttribute;
        xmlAttribute = m_pTinyXMLElement->FirstAttribute();

        return XMLAttribute(xmlAttribute);
    }

    void XMLElement::SetAttribute(const std::string& attributeName, const std::string& attributeValue)
    {
        m_pTinyXMLElement->SetAttribute(attributeName.c_str(), attributeValue.c_str());
    }

    void XMLElement::SetAttribute(const std::wstring& attributeName, const std::wstring& attributeValue)
    {
        m_pTinyXMLElement->SetAttribute(WStringToString(attributeName).c_str(),
                                        WStringToString(attributeValue).c_str());
    }

    bool XMLElement::GetAttribute(const std::string& attributeName, std::string* pAttributeValue) const
    {
        const char* pValue = m_pTinyXMLElement->Attribute(attributeName.c_str());

        if (pValue != nullptr)
        {
            *pAttributeValue = pValue;

            return true;
        }

        return false;
    }

    bool XMLElement::GetAttributeLowerCase(const std::string& attributeName, std::string* pAttributeValue) const
    {
        if (!GetAttribute(attributeName, pAttributeValue))
        {
            return false;
        }

        *pAttributeValue = StringToLower(*pAttributeValue);

        return true;
    }

    bool XMLElement::GetAttributeUpperCase(const std::string& attributeName, std::string* pAttributeValue) const
    {
        if (!GetAttribute(attributeName, pAttributeValue))
        {
            return false;
        }

        *pAttributeValue = StringToUpper(*pAttributeValue);

        return true;
    }

    bool XMLElement::GetAttribute(const std::wstring& attributeName, std::wstring* pAttributeValue) const
    {
        const char* pValue = m_pTinyXMLElement->Attribute(WStringToString(attributeName).c_str());

        if (pValue != nullptr)
        {
            *pAttributeValue = StringToWString(pValue);

            return true;
        }

        return false;
    }

    bool XMLElement::GetAttributeLowerCase(const std::wstring& attributeName, std::wstring* pAttributeValue) const
    {
        if (!GetAttribute(attributeName, pAttributeValue))
        {
            return false;
        }

        *pAttributeValue = WStringToLower(*pAttributeValue);

        return true;
    }

    bool XMLElement::GetAttributeUpperCase(const std::wstring& attributeName, std::wstring* pAttributeValue) const
    {
        if (!GetAttribute(attributeName, pAttributeValue))
        {
            return false;
        }

        *pAttributeValue = WStringToUpper(*pAttributeValue);

        return true;
    }

    void XMLElement::SetAttribute(const std::string& attributeName, const int attributeValue)
    {
        m_pTinyXMLElement->SetAttribute(attributeName.c_str(), attributeValue);
    }

    void XMLElement::SetAttribute(const std::wstring& attributeName, const int attributeValue)
    {
        m_pTinyXMLElement->SetAttribute(WStringToString(attributeName).c_str(), attributeValue);
    }

    bool XMLElement::GetIntAttribute(const std::string& attributeName, int* pAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryIntAttribute(attributeName.c_str(), pAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    bool XMLElement::GetIntAttribute(const std::wstring& attributeName, int* pAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryIntAttribute(WStringToString(attributeName).c_str(), pAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    void XMLElement::SetAttribute(const std::string& attributeName, const unsigned int attributeValue)
    {
        m_pTinyXMLElement->SetAttribute(attributeName.c_str(), attributeValue);
    }

    void XMLElement::SetAttribute(const std::wstring& attributeName, const unsigned int attributeValue)
    {
        m_pTinyXMLElement->SetAttribute(WStringToString(attributeName).c_str(), attributeValue);
    }

    bool XMLElement::GetUnsignedIntAttribute(const std::string& attributeName, unsigned int* pAttributeValue) const
    {
        unsigned int value;
        if (m_pTinyXMLElement->QueryUnsignedAttribute(attributeName.c_str(), &value) == tinyxml2::XML_NO_ERROR)
        {
            *pAttributeValue = value;

            return true;
        }

        return false;
    }

    bool XMLElement::GetUnsignedIntAttribute(const std::wstring& attributeName, unsigned int* pAttributeValue) const
    {
        unsigned int value;
        if (m_pTinyXMLElement->QueryUnsignedAttribute(WStringToString(attributeName).c_str(), &value) == tinyxml2::XML_NO_ERROR)
        {
            *pAttributeValue = value;

            return true;
        }

        return false;
    }

    void XMLElement::SetAttribute(const std::string& attributeName, const bool bAttributeValue)
    {
        m_pTinyXMLElement->SetAttribute(attributeName.c_str(), bAttributeValue);
    }

    void XMLElement::SetAttribute(const std::wstring& attributeName, const bool bAttributeValue)
    {
        m_pTinyXMLElement->SetAttribute(WStringToString(attributeName).c_str(), bAttributeValue);
    }

    bool XMLElement::GetBoolAttribute(const std::string& attributeName, bool* pbAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryBoolAttribute(attributeName.c_str(), pbAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    bool XMLElement::GetBoolAttribute(const std::wstring& attributeName, bool* pbAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryBoolAttribute(WStringToString(attributeName).c_str(), pbAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    void XMLElement::SetAttribute(const std::string& attributeName, const double fAttributeValue)
    {
        m_pTinyXMLElement->SetAttribute(attributeName.c_str(), fAttributeValue);
    }

    void XMLElement::SetAttribute(const std::wstring& attributeName, const double fAttributeValue)
    {
        m_pTinyXMLElement->SetAttribute(WStringToString(attributeName).c_str(), fAttributeValue);
    }

    bool XMLElement::GetDoubleAttribute(const std::string& attributeName, double* pfAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryDoubleAttribute(attributeName.c_str(), pfAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    bool XMLElement::GetDoubleAttribute(const std::wstring& attributeName, double* pfAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryDoubleAttribute(WStringToString(attributeName).c_str(), pfAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    void XMLElement::SetAttribute(const std::string& attributeName, const float fAttributeValue)
    {
        m_pTinyXMLElement->SetAttribute(attributeName.c_str(), fAttributeValue);
    }

    void XMLElement::SetAttribute(const std::wstring& attributeName, const float fAttributeValue)
    {
        m_pTinyXMLElement->SetAttribute(WStringToString(attributeName).c_str(), fAttributeValue);
    }

    bool XMLElement::GetFloatAttribute(const std::string& attributeName, float* pfAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryFloatAttribute(attributeName.c_str(), pfAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    bool XMLElement::GetFloatAttribute(const std::wstring& attributeName, float* pfAttributeValue) const
    {
        return (m_pTinyXMLElement->QueryFloatAttribute(WStringToString(attributeName).c_str(), pfAttributeValue) == tinyxml2::XML_NO_ERROR);
    }

    void XMLElement::RemoveAttribute(const std::string& attributeName)
    {
        m_pTinyXMLElement->DeleteAttribute(attributeName.c_str());
    }

    void XMLElement::RemoveAttribute(const std::wstring& attributeName)
    {
        m_pTinyXMLElement->DeleteAttribute(WStringToString(attributeName).c_str());
    }

    XMLFile::XMLFile() : m_pFile(nullptr), m_pTinyXMLRootElement(nullptr)
    {
        m_Mode = File::FileMode::FileUninitialized;
    }

    XMLFile::~XMLFile()
    {
        CloseFile();

        m_pTinyXMLRootElement = nullptr;
    }

    bool XMLFile::OpenFile(const std::string& fileName, const File::FileMode mode)
    {
        assert(fileName != "" && "Invalid file name!");

        m_FileName = fileName;
        m_Mode = mode;

        switch (m_Mode)
        {
            case File::FileMode::FileReadOnly:
                m_pFile = fopen(fileName.c_str(), "rb");
                break;

            case File::FileMode::FileWriteOnly:
                m_pFile = fopen(fileName.c_str(), "wb");
                break;

            case File::FileMode::FileReadWrite:
                m_pFile = fopen(fileName.c_str(), "rb+");
                break;

            default:
                LOG_ERROR("Invalid file mode.");
                return false;
        }

        if (m_pFile != nullptr)
        {
            if (m_TinyXMLDocument.LoadFile(m_pFile) == tinyxml2::XML_NO_ERROR)
            {
                m_pTinyXMLRootElement = m_TinyXMLDocument.RootElement();
                m_RootNode.m_pTinyXMLNode = m_TinyXMLDocument.FirstChild();

                return true;
            }
        }

        m_Mode = File::FileMode::FileUninitialized;

        return false;
    }

    bool XMLFile::CreateFile(const std::string& fileName, const File::FileMode mode)
    {
        assert(fileName != "" && "Invalid file name!");

        m_FileName = fileName;
        m_Mode = mode;

        bool bReadDocumentRoot = false;
        switch (m_Mode)
        {
            case File::FileMode::FileReadOnly:
                m_pFile = fopen(fileName.c_str(), "rb");
                bReadDocumentRoot = true;
                break;

            case File::FileMode::FileWriteOnly:
                m_pFile = fopen(fileName.c_str(), "wb+");
                break;

            case File::FileMode::FileReadWrite:
                m_pFile = fopen(fileName.c_str(), "rb+");
                bReadDocumentRoot = true;
                break;

            default:
                LOG_ERROR("Invalid file mode.");
                return false;
        }

        if (m_pFile != nullptr)
        {
            if (m_TinyXMLDocument.LoadFile(m_pFile) == tinyxml2::XML_NO_ERROR)
            {
                if (bReadDocumentRoot)
                {
                    m_pTinyXMLRootElement = m_TinyXMLDocument.RootElement();
                    m_RootNode.m_pTinyXMLNode = m_TinyXMLDocument.FirstChild();
                }

                return true;
            }
        }

        m_Mode = File::FileMode::FileUninitialized;

        return false;
    }

    bool XMLFile::CloseFile()
    {
        if (m_Mode == File::FileMode::FileWriteOnly || m_Mode == File::FileMode::FileReadWrite
            || m_Mode == File::FileMode::MemoryBufferWriteOnly || m_Mode == File::FileMode::MemoryBufferReadWrite)
        {
            m_TinyXMLDocument.SaveFile(m_FileName.c_str());
        }

        m_Mode = File::FileMode::FileUninitialized;

        if (m_pFile != nullptr)
        {
            fclose(m_pFile);
        }
        m_pFile = nullptr;

        return true;
    }

    bool XMLFile::IsOpen() const
    {
        return (m_Mode != File::FileMode::FileUninitialized);
    }

    bool XMLFile::IsGood() const
    {
        return (!feof(m_pFile));
    }

    bool XMLFile::Write(const std::string& buffer)
    {
        LOG_ERROR("Not implemented");

        if (m_Mode == File::FileMode::FileWriteOnly || m_Mode == File::FileMode::FileReadWrite
            || m_Mode == File::FileMode::MemoryBufferWriteOnly || m_Mode == File::FileMode::MemoryBufferReadWrite)
        {
            return (m_TinyXMLDocument.SaveFile(m_pFile) == tinyxml2::XML_NO_ERROR);
        }

        return false;
    }

    const std::string XMLFile::Read()
    {
        if (m_Mode == File::FileMode::FileReadOnly || m_Mode == File::FileMode::FileReadWrite)
        {
            tinyxml2::XMLPrinter xmlPrinter;
            m_TinyXMLDocument.Print(&xmlPrinter);

            return xmlPrinter.CStr();
        }

        return "";
    }

    void XMLFile::SetReadPosition(const FilePosition position, const int offset)
    {
        assert(IsOpen() && "File wasn't opened before using!");

        switch (position)
        {
            case FilePosition::FileBeginning:
                fseek(m_pFile, offset, SEEK_SET);
                return;

            case FilePosition::FileEnd:
                fseek(m_pFile, offset, SEEK_END);
                return;

            case FilePosition::FileCurrent:
                fseek(m_pFile, offset, SEEK_CUR);
                return;

            default:
                LOG_ERROR("Invalid file position!");
        }
    }

    void XMLFile::SetWritePosition(const FilePosition position, const int offset)
    {
        assert(IsOpen() && "File wasn't opened before using!");

        switch (position)
        {
            case FilePosition::FileBeginning:
                fseek(m_pFile, offset, SEEK_SET);
                return;

            case FilePosition::FileEnd:
                fseek(m_pFile, offset, SEEK_END);
                return;

            case FilePosition::FileCurrent:
                fseek(m_pFile, offset, SEEK_CUR);
                return;

            default:
                LOG_ERROR("Invalid file position!");
        }
    }

    const unsigned int XMLFile::GetReadPosition()
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return static_cast<unsigned int>(ftell(m_pFile));
    }

    const unsigned int XMLFile::GetWritePosition()
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return static_cast<unsigned int>(ftell(m_pFile));
    }

    bool XMLFile::LoadFromMemory(const char* pXMLText)
    {
        assert((pXMLText != nullptr) && "Invalid XML text buffer!");

        m_TinyXMLDocument.Parse(pXMLText);
        if (m_TinyXMLDocument.ErrorID() == 0)
        {
            m_Mode = File::FileMode::MemoryBufferReadWrite;
            m_pFile = nullptr;

            m_pTinyXMLRootElement = m_TinyXMLDocument.RootElement();
            m_RootNode.m_pTinyXMLNode = m_TinyXMLDocument.FirstChild();

            return true;
        }

        return false;
    }

    bool XMLFile::LoadFromMemory(const char* pXMLText, unsigned int xmlTextSize)
    {
        assert((pXMLText != nullptr) && "Invalid XML text buffer!");
        assert((xmlTextSize > 0) && "Invalid size!");

        m_TinyXMLDocument.Parse(pXMLText, xmlTextSize);
        if (m_TinyXMLDocument.ErrorID() == 0)
        {
            m_Mode = File::FileMode::MemoryBufferReadWrite;
            m_pFile = nullptr;

            m_pTinyXMLRootElement = m_TinyXMLDocument.RootElement();
            m_RootNode.m_pTinyXMLNode = m_TinyXMLDocument.FirstChild();

            return true;
        }

        return false;
    }

    bool XMLFile::LoadFromMemory(const std::string& xmlText)
    {
        m_TinyXMLDocument.Parse(xmlText.c_str());
        if (m_TinyXMLDocument.ErrorID() == 0)
        {
            m_Mode = File::FileMode::MemoryBufferReadWrite;
            m_pFile = nullptr;

            m_pTinyXMLRootElement = m_TinyXMLDocument.RootElement();
            m_RootNode.m_pTinyXMLNode = m_TinyXMLDocument.FirstChild();

            return true;
        }

        return false;
    }

    bool XMLFile::LoadFromMemory(const std::wstring& xmlText)
    {
        assert(IsOpen() && "File wasn't opened before using!");

        std::string utf8Text = WStringToString(xmlText);

        return LoadFromMemory(utf8Text);
    }

    void XMLFile::InsertNode(const XMLNode* pNode)
    {
        assert(IsOpen() && "File wasn't opened before using!");
        assert((m_Mode == File::FileMode::FileWriteOnly ||  m_Mode == File::FileMode::FileWriteOnly)
               && "Invalid mode to write!");

        m_TinyXMLDocument.InsertFirstChild(pNode->m_pTinyXMLNode);
    }

    void XMLFile::AppendNodeAsChild(const XMLNode* pAfterThisNode, const XMLNode* pNewNode)
    {
        assert(IsOpen() && "File wasn't opened before using!");
        assert((m_Mode == File::FileMode::FileWriteOnly ||  m_Mode == File::FileMode::FileWriteOnly)
               && "Invalid mode to write!");

        m_TinyXMLDocument.InsertAfterChild(pAfterThisNode->m_pTinyXMLNode, pNewNode->m_pTinyXMLNode);
    }

    void XMLFile::RemoveNode(const XMLNode* pNode)
    {
        assert(IsOpen() && "File wasn't opened before using!");
        assert((m_Mode == File::FileMode::FileWriteOnly ||  m_Mode == File::FileMode::FileWriteOnly)
               && "Invalid mode to write!");

        m_RootNode.m_pTinyXMLNode->DeleteChild(pNode->m_pTinyXMLNode);
    }

    void XMLFile::SetRoot(XMLNode* pRootNode)
    {
        assert(IsOpen() && "File wasn't opened before using!");
        assert((m_Mode == File::FileMode::FileWriteOnly ||  m_Mode == File::FileMode::FileWriteOnly)
               && "Invalid mode to write!");

        m_RootNode.m_pTinyXMLNode = pRootNode->m_pTinyXMLNode;
    }

    XMLNode XMLFile::GetRoot() const
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return m_RootNode;
    }

    XMLElement XMLFile::GetRootElement()
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return XMLElement(m_TinyXMLDocument.RootElement());
    }

    std::string XMLFile::GetRootName() const
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return m_pTinyXMLRootElement->Name();
    }

    std::string XMLFile::GetRootValue() const
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return m_pTinyXMLRootElement->Value();
    }

    std::wstring XMLFile::GetRootWName() const
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return StringToWString(m_pTinyXMLRootElement->Name());
    }

    std::wstring XMLFile::GetRootWValue() const
    {
        assert(IsOpen() && "File wasn't opened before using!");

        return StringToWString(m_pTinyXMLRootElement->Value());
    }

    std::string XMLFile::Transverse()
    {
        assert(IsOpen() && "File wasn't opened before using!");

        std::string buffer("");
        for (tinyxml2::XMLNode* pRootNode = m_TinyXMLDocument.FirstChild();
             pRootNode != nullptr; pRootNode = pRootNode->NextSibling())
        {
            DoTransverse(pRootNode, buffer);
        }

        return buffer;
    }

    void XMLFile::DoTransverse(tinyxml2::XMLNode* pNode, std::string& buffer)
    {
        buffer += pNode->Value();
        buffer += "\n";
        for (tinyxml2::XMLNode* pChild = pNode->FirstChild();
             pChild != nullptr; pChild = pChild->NextSibling())
        {
            DoTransverse(pChild, buffer);
        }
    }

    XMLAttribute::XMLAttribute(const tinyxml2::XMLAttribute* pTinyXMLAttribute) : m_pTinyXMLAttribute(pTinyXMLAttribute)
    {

    }

    XMLAttribute XMLAttribute::GetNextAttribute()
    {
        const tinyxml2::XMLAttribute* nextAttribute;
        nextAttribute = m_pTinyXMLAttribute->Next();

        return XMLAttribute(nextAttribute);
    }

    bool XMLAttribute::IsGood() const
    {
        return (m_pTinyXMLAttribute != nullptr);
    }

    std::string XMLAttribute::GetName() const
    {
        return m_pTinyXMLAttribute->Name();
    }

    std::string XMLAttribute::GetNameLowerCase() const
    {
        return StringToLower(GetName());
    }

    std::string XMLAttribute::GetNameUpperCase() const
    {
        return StringToUpper(GetName());
    }

    std::string XMLAttribute::GetValue() const
    {
        return m_pTinyXMLAttribute->Value();
    }

    std::string XMLAttribute::GetValueLowerCase() const
    {
        return StringToLower(GetValue());
    }

    std::string XMLAttribute::GetValueUpperCase() const
    {
        return StringToUpper(GetValue());
    }    

    std::wstring XMLAttribute::GetWValue() const
    {
        return StringToWString(GetValue());
    }

    std::wstring XMLAttribute::GetWValueLowerCase() const
    {
        return WStringToLower(GetWValue());
    }

    std::wstring XMLAttribute::GetWValueUpperCase() const
    {
        return WStringToUpper(GetWValue());
    }

    int XMLAttribute::GetIntValue() const
    {
        return m_pTinyXMLAttribute->IntValue();
    }

    unsigned int XMLAttribute::GetUnsignedIntValue() const
    {
        return m_pTinyXMLAttribute->UnsignedValue();
    }

    bool XMLAttribute::GetBoolValue() const
    {
        return m_pTinyXMLAttribute->BoolValue();
    }

    double XMLAttribute::GetDoubleValue() const
    {
        return m_pTinyXMLAttribute->DoubleValue();
    }

    float XMLAttribute::GetFloatValue() const
    {
        return m_pTinyXMLAttribute->FloatValue();
    }

}
