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

#include "File.h"

namespace uge
{

    // Forward declarations.
    class XMLAttribute;
    class XMLElement;
    class XMLNode;
    class XMLFile;

    /**
     *  @class XMLNode
     * Abstraction for a node in a XML document.
     */
    class XMLNode
    {
        /// Allows access to the TinyXML members by the XMLFile class.
        friend class XMLFile;

    public:
        /**
         *  Constructor.
         */
        XMLNode();

        /**
         *  Desstructor.
         */
        ~XMLNode();

        /**
         *  Tells if the node is valid.
         * If the node is valid, it can be used to navigate the document.
         * @return : true if valid; false otherwise.
         */
        bool IsGood() const;

        /**
         *  Tells whether the node has children or not (in the second case, it's a leaf).
         * @return : true if the node has no children; false otherwise.
         */
        bool IsLeaf() const;

        /**
         *  Retrieves the first child of the node.
         * If the node doesn't have childs, an invalid node is returned.
         * Check if it's valid using IsGood().
         * @return : the first child of the node, if exists. Invalid node otherwise.
         */
        uge::XMLNode GetFirstChild() const;

        /**
         *  Retrieves the XML element of the first children.
         * If a name is supplied, the element retrieved is the first which matches the name.
         * @pChildName : optional name of the children. Default: nullptr.
         * @return : the XML element of the first children, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetFirstChildElement(const char* pChildName = nullptr);

        /**
         *  Retrieves the XML element of the first children named childName.
         * @pChildName : name of the children.
         * @return : the XML element of the first children, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetFirstChildElement(const std::string& childName);

        /**
         *  Retrieves the next sibling of the node.
         * If the node doesn't have childs, an invalid node is returned.
         * Check if it's valid using IsGood().
         * @return : the next child of the node, if exists. Invalid node otherwise.
         */
        uge::XMLNode GetNextSibling() const;

        /**
         *  Retrieves the XML element of the next sibling.
         * If a name is supplied, the element retrieved is the first which matches the name.
         * @pChildName : optional name of the children. Default: nullptr.
         * @return : the XML element of the next sibling, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetNextSiblingElement(const char* pSiblingName = nullptr);

        /**
         *  Retrieves the XML element of the next sibling named siblingName.
         * @pChildName : name of the children. Default: nullptr.
         * @return : the XML element of the next sibling, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetNextSiblingElement(const std::string& siblingName);

        /**
         *  Retrieves the previous child of the node.
         * If the node doesn't have childs, an invalid node is returned.
         * Check if it's valid using IsGood().
         * @return : the previous child of the node, if exists. Invalid node otherwise.
         */
        uge::XMLNode GetPreviousSibling() const;

        /**
         *  Retrieves the XML element of the previous sibling.
         * If a name is supplied, the element retrieved is the first which matches the name.
         * @pChildName : optional name of the children. Default: nullptr.
         * @return : the XML element of the previous sibling, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetPreviousSiblingElement(const char* pSiblingName = nullptr);

        /**
         *  Retrieves the XML element of the previous sibling named siblingName.
         * If a name is supplied, the element retrieved is the first which matches the name.
         * @pChildName : name of the children.
         * @return : the XML element of the previous sibling, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetPreviousSiblingElement(const std::string& siblingName = nullptr);

        /**
         *  Retrieves the last child of the node.
         * If the node doesn't have childs, an invalid node is returned.
         * Check if it's valid using IsGood().
         * @return : the last child of the node, if exists. Invalid node otherwise.
         */
        uge::XMLNode GetLastChild() const;

        /**
         *  Retrieves the XML element of the last children.
         * If a name is supplied, the element retrieved is the first which matches the name.
         * @pChildName : optional name of the children. Default: nullptr.
         * @return : the XML element of the last children, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetLastChildElement(const char* pChildName = nullptr);

        /**
         *  Retrieves the XML element of the last children named childName.
         * If a name is supplied, the element retrieved is the first which matches the name.
         * @pChildName : name of the children. Default: nullptr.
         * @return : the XML element of the last children, if found. Invalid element if the the node has no child.
         */
        uge::XMLElement GetLastChildElement(const std::string& childName = nullptr);

        /**
         *  Retrieves the parent of the current node.
         * If the node doesn't have a parent, an invalid node is returned.
         * @return : parent of the node, if exists. Invalid node otherwise.
         */
        uge::XMLNode GetParent() const;

        /**
         *  Checks if this node is a XML element.
         * @return : true if the node is an element; false if it is not.
         */
        bool IsElement() const;

        /**
         *  Retrieves the XML element stored in the node.
         * Check if it's an element before using.
         * @return : the XML of the node.
         */
        uge::XMLElement GetElement() const;

        /**
         *  Changes the node's value to a new value.
         * @param value : new value for the node.
         */
        void SetNodeValue(const std::string& value);

        /**
         *  Changes the node's value to a new value.
         * @param value : new value for the node.
         */
        void SetNodeValue(const std::wstring& value);

        /**
         *  Retrieves the current value of the node.
         * To retrieve the value as a wide string, use GetNodeWValue().
         * @return : new value of the node.
         */
        const std::string GetNodeValue() const;

        /**
         *  Retrieves the current value of the node.
         * To retrieve the value as a string, use GetNodeValue().
         * @return : new value of the node.
         */
        const std::wstring GetNodeWValue() const;

    protected:
        /**
         *  Constructor.
         * @param pTinyXMLNode : the TinyXML2's node abstraction.
         */
        XMLNode(tinyxml2::XMLNode* pTinyXMLNode);

        /// The TinyXML2 abstraction of the node.
        tinyxml2::XMLNode* m_pTinyXMLNode;
    };

    /**
     * @class XMLElement
     * Abstraction for manipulating XML elements in XML documents.
     */
    class XMLElement : public uge::XMLNode
    {
        /// Allows access to the TinyXML members by the XMLAttribute class.
        friend class uge::XMLAttribute;
        /// Allows access to the TinyXML members by the XMLNode class.
        friend class uge::XMLNode;
        /// Allows access to the TinyXML members by the XMLFile class.
        friend class uge::XMLFile;

    public:
        /**
         *  Destructor.
         */
        ~XMLElement();

        /**
         *  Retrieves the name of the XML element.
         * @return : a string containing the name of this element.
         */
        std::string GetElementName();

        /**
         *  Retrieves the name of the XML element as a wide string.
         * @return : a wide string containing the name of this element.
         */
        std::wstring GetElementWName();

        /**
         *  Changes the name of the XML element to the value of the attribute.
         * @param attributeName : new name of the attribute.
         */
        void SetElementName(const std::string& attributeName);

        /**
         *  Changes the name of the XML element to the value of the attribute.
         * @param attributeName : new name of the attribute.
         */
        void SetElementName(const std::wstring& attributeName);

        /**
         *  Retrieves the current XML element as text.
         * Use this method to retrieve a value stored between tags.
         * If the element cannot be converted into text, the argument isn't changed.
         * @param elementText : a string with the value of the element.
         * @return : true if successful; false otherwise.
         */
        bool GetElementAsText(std::string& elementText) const;

        /**
         *  Retrieves the current XML element as text.
         * Use this method to retrieve a value stored between tags.
         * If the element cannot be converted into text, the argument isn't changed.
         * @param elementText : a string with the value of the element.
         * @return : true if successful; false otherwise.
         */
        bool GetElementAsText(std::wstring& elementText) const;

        /**
         *  Retrieves the first attribute of the element.
         * This allows iteration in all the attributes of an element.
         * @param attributeName : the name of the attribute.
         * @return : returns the attribute.
         */
        uge::XMLAttribute GetFirstAttribute() const;

        /**
         *  Sets a new value for an attribute of the element.
         * @param attributeName : the name of the element.
         * @param attributeValue : the new value for the element.
         */
        void SetAttribute(const std::string& attributeName, const std::string& attributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * If the element cannot be retrieved, the argument isn't changed.
         * To avoid converting the value, type specific methods are also available.
         * @param attributeName : the name of the element.
         * @param pAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetAttribute(const std::string& attributeName, std::string* pAttributeValue) const;

        /**
         *  Sets a new value for an attribute of the element.
         * @param attributeName : the name of the element.
         * @param attributeValue : the new value for the element.
         */
        void SetAttribute(const std::wstring& attributeName, const std::wstring& attributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * If the element cannot be retrieved, the argument isn't changed.
         * To avoid converting the value, type specific methods are also available.
         * @param attributeName : the name of the element.
         * @param pAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetAttribute(const std::wstring& attributeName, std::wstring* pAttributeValue) const;

        /**
         *  Sets a new value for an integer attribute of the element.
         * @param attributeName : the name of the element.
         * @param attributeValue : the new value for the element.
         */
        void SetAttribute(const std::string& attributeName, const int attributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to an integer.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetIntAttribute(const std::string& attributeName, int* pAttributeValue) const;

        /**
         *  Sets a new value for an integer attribute of the element.
         * @param attributeName : the name of the element.
         * @param attributeValue : the new value for the element.
         */
        void SetAttribute(const std::wstring& attributeName, const int attributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to an integer.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetIntAttribute(const std::wstring& attributeName, int* pAttributeValue) const;

        /**
         *  Sets a new value for a unsigned integer attribute of the element.
         * @param attributeName : the name of the element.
         * @param attributeValue : the new value for the element.
         */
        void SetAttribute(const std::string& attributeName, const unsigned int attributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to an unsigned integer.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetUnsignedIntAttribute(const std::string& attributeName, unsigned int* pAttributeValue) const;

        /**
         *  Sets a new value for a unsigned integer attribute of the element.
         * @param attributeName : the name of the element.
         * @param attributeValue : the new value for the element.
         */
        void SetAttribute(const std::wstring& attributeName, const unsigned int attributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to an unsigned integer.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetUnsignedIntAttribute(const std::wstring& attributeName, unsigned int* pAttributeValue) const;

        /**
         *  Sets a new value for a boolean attribute of the element.
         * @param attributeName : the name of the element.
         * @param bAttributeValue : the new value for the element.
         */
        void SetAttribute(const std::string& attributeName, const bool bAttributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to a boolean.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pbAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetBoolAttribute(const std::string& attributeName, bool* pbAttributeValue) const;

        /**
         *  Sets a new value for a boolean attribute of the element.
         * @param attributeName : the name of the element.
         * @param bAttributeValue : the new value for the element.
         */
        void SetAttribute(const std::wstring& attributeName, const bool bAttributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to a boolean.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pbAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetBoolAttribute(const std::wstring& attributeName, bool* pbAttributeValue) const;

        /**
         *  Sets a new value for a double attribute of the element.
         * @param attributeName : the name of the element.
         * @param fAttributeValue : the new value for the element.
         */
        void SetAttribute(const std::string& attributeName, const double fAttributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to double.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param attributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetDoubleAttribute(const std::string& attributeName, double* pfAttributeValue) const;

        /**
         *  Sets a new value for a double attribute of the element.
         * @param attributeName : the name of the element.
         * @param fAttributeValue : the new value for the element.
         */
        void SetAttribute(const std::wstring& attributeName, const double fAttributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to double.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pfAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetDoubleAttribute(const std::wstring& attributeName, double* pfAttributeValue) const;

        /**
         *  Sets a new value for a float attribute of the element.
         * @param attributeName : the name of the element.
         * @param fAttributeValue : the new value for the element.
         */
        void SetAttribute(const std::string& attributeName, const float fAttributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to float.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pfAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetFloatAttribute(const std::string& attributeName, float* pfAttributeValue) const;

        /**
         *  Sets a new value for a float attribute of the element.
         * @param attributeName : the name of the element.
         * @param fAttributeValue : the new value for the element.
         */
        void SetAttribute(const std::wstring& attributeName, const float fAttributeValue);

        /**
         *  Retrieves the value for an attribute of the element.
         * The retrieved value is converted to float.
         * If the element cannot be retrieved, the argument isn't changed.
         * @param attributeName : the name of the element.
         * @param pfAttributeValue : the value of the retrieved attribute, if exists.
         * @return : true if successful; false otherwise.
         */
        bool GetFloatAttribute(const std::wstring& attributeName, float* pfAttributeValue) const;

        /**
         *  Removes the attribute with the specified name from the element.
         * @param attributeName : the name of the element to be removed.
         */
        void RemoveAttribute(const std::string& attributeName);

        /**
         *  Removes the attribute with the specified name from the element.
         * @param attributeName : the name of the element to be removed.
         */
        void RemoveAttribute(const std::wstring& attributeName);

    private:
        /**
         *  Private constructor.
         * XML elements can only be created by XMLNodes and XMLFiles.
         */
        XMLElement();

        /**
         *  Private constructor.
         * XML elements can only be created by XMLNodes and XMLFiles.
         * @param pTinyXMLNode : the TinyXML2's node abstraction.
         */
        XMLElement(tinyxml2::XMLElement* pTinyXMLElement);

        /// The TinyXML2's XML element abstraction.
        tinyxml2::XMLElement* m_pTinyXMLElement;
    };

    /**
     *  @class XMLFile
     * Abstraction for a XML document.
     */
    class XMLFile : public IFile
    {
    public:
        /**
         *  Constructor.
         */
        XMLFile();

        /**
         *  Destructor.
         */
        ~XMLFile();

        /**
         *  Opens a XML file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        bool OpenFile(const std::string& fileName, const File::FileMode mode);

        /**
         * Creates a new XML file.
         * @param fileName : the name of the file.
         * @param fileMode : the mode on which the window will be opened.
         */
        bool CreateFile(const std::string& fileName, const File::FileMode mode);

        /**
         *  Parses the XML text buffer and loads a XML document with it.
         *  The text string should be null-terminated.
         * @param xmlText : a string containing a XML document.
         * @return : true if the buffer is loaded; false otherwise.
         */
        bool LoadFromMemory(const char* pXMLText);

        /**
         *  Parses the XML text buffer and loads a XML document with it.
         * @param xmlText : a string containing a XML document.
         * @param xmlTextSize : the size of the XML string buffer.
         * @return : true if the buffer is loaded; false otherwise.
         */
        bool LoadFromMemory(const char* pXMLText, unsigned int xmlTextSize);

        /**
         *  Parses the XML text buffer and loads a XML document with it.
         *  The text string should be null-terminated.
         * @param xmlText : a string containing a XML document.
         * @return : true if the buffer is loaded; false otherwise.
         */
        bool LoadFromMemory(const std::string& xmlText);

        /**
         *  Parses the XML text buffer and loads a XML document with it.
         *  The text string should be null-terminated.
         * @param xmlText : a string containing a XML document.
         * @return : true if the buffer is loaded; false otherwise.
         */
        bool LoadFromMemory(const std::wstring& xmlText);

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

        /**
         *  Inserts a new node as the first node of the XML document.
         * @param pNode : pointer to the node to be inserted.
         */
        void InsertNode(const uge::XMLNode* pNode);

        /**
         *  Inserts a new node after another node of the XML document.
         * @param pAfterThisNode : pointer to the node that will precede the new one.
         * @param pNewNode : new node to be added after the other's parameter one.
         */
        void AppendNodeAsChild(const uge::XMLNode* pAfterThisNode, const uge::XMLNode* pNewNode);

        /**
         *  Removes a node from the XML document.
         * @param pNode : pointer to the node to be removed.
         */
        void RemoveNode(const uge::XMLNode* pNode);

        /**
         *  Retrieves the root of the XML document.
         * @return : a node with the root of the document.
         */
        uge::XMLNode GetRoot() const;

        /**
         *  Retrieves the root of the XML document.
         * @return : a node with the root of the document.
         */
        XMLElement GetRootElement();

        /**
         *  Sets a new root for the XML document.
         * @param pRootNode : pointer to the new root of the document.
         */
        void SetRoot(uge::XMLNode* pRootNode);

        /**
         *  Retrieves the name of the root element.
         * To retrieve the name as a wide string, use GetRootWName().
         * @return : the name of root.
         */
        std::string GetRootName() const;

        /**
         *  Retrieves the value of the root element.
         * To retrieve the value as a wide string, use GetRootWValue().
         * @return : the value of root.
         */
        std::string GetRootValue() const;

        /**
         *  Retrieves the name of the root element.
         * To retrieve the name as a string, use GetRootName().
         * @return : the name of root.
         */
        std::wstring GetRootWName() const;

        /**
         *  Retrieves the value of the root element.
         * To retrieve the value as a string, use GetRootValue().
         * @return : the value of root.
         */
        std::wstring GetRootWValue() const;

    private:
        /**
         *  Sample transversal of a XML document.
         * This method does a depth tranversal in the document.
         * @return : the tags in the document.
         */
        std::string Transverse();
        /**
         *  Sample transversal of a XML document.
         * This method does a depth tranversal in the document.
         * @param pNode : pointer to the current node of the tree.
         * @param buffer : the tags in the document.
         */
        void DoTransverse(tinyxml2::XMLNode* pNode, std::string& buffer);

        /// The TinyXML2 abstraction for XML files.
        tinyxml2::XMLDocument m_TinyXMLDocument;
        /// The XML document's root;
        tinyxml2::XMLElement* m_pTinyXMLRootElement;

        /// The root node of the tree. It contains the root element of the XML.
        uge::XMLNode m_RootNode;

        /// The file used by the XML document.
        FILE* m_pFile;
        /// The mode on which the file be opened.
        File::FileMode m_Mode;
    };

    /**
     *  @class XMLFile
     * Helper class to parse attributes of a XML element.
     */
    class XMLAttribute
    {
        /// Allows access to the TinyXML members by the XMLElement class.
        friend class XMLElement;

    public:
        /**
         *  Retrieves the next attribute.
         * Check the element with IsGood() before using.
         * @return : the next attribute of the element.
         */
        XMLAttribute GetNextAttribute();

        /**
         *  Tells if the attribute is valid.
         * If the attribute is valid, its name or value can be retrieved.
         * @return : true if valid; false otherwise.
         */
        bool IsGood() const;

        /**
         *  Retrieves the name of the attribute.
         * @return : the name of the attribute.
         */
        std::string GetName() const;

        /**
         *  Retrieves the value of the attribute.
         * @return : the value of the attribute.
         */
        std::string GetValue() const;

        /**
         *  Retrieves the value of the attribute.
         * @return : the value of the attribute.
         */
        std::wstring GetWValue() const;

        /**
         *  Retrieves the value of the attribute.
         * @return : the value of the attribute.
         */
        int GetIntValue() const;

        /**
         *  Retrieves the value of the attribute.
         * @return : the value of the attribute.
         */
        unsigned int GetUnsignedIntValue() const;

        /**
         *  Retrieves the value of the attribute.
         * @return : the value of the attribute.
         */
        bool GetBoolValue() const;

        /**
         *  Retrieves the value of the attribute.
         * @return : the value of the attribute.
         */
        double GetDoubleValue() const;

        /**
         *  Retrieves the value of the attribute.
         * @return : the value of the attribute.
         */
        float GetFloatValue() const;

    private:
        /**
         *  Constructor.
         * @param pTinyXMLNode : the TinyXML2's attribute abstraction.
         */
        XMLAttribute(const tinyxml2::XMLAttribute* pTinyXMLAttribute);

        /// The TinyXML2 abstraction for XML attributes.
        const tinyxml2::XMLAttribute* m_pTinyXMLAttribute;
    };

}
