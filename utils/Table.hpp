//
//  Table.hpp
//  FastEMD
//
//  Created by Till Hainbach on 07.04.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp
namespace FastEMD
{
namespace utils
{


enum class TextAlignment
{
    leftAligned,
    centered,
    rightAligned
};

class Table
{
public:
    Table(std::vector<std::string> const& _header,
          std::vector< std::vector<std::string> > const& _data,
          TextAlignment _textAlignment = TextAlignment::leftAligned,
          bool _headerUnderlined = true,
          std::string underlineStyle = "-",
          size_t _columnWidth = 12,
          std::string columnSeparator = "\t");
    
    //MARK: Setters
    void setColumnSeparator(std::string separator);
    
    void setTextAlignment(TextAlignment alignment);
    
    void setColumnWidth(size_t width);
    
    void setHeaderUnderline(bool setUnderline);
    
    void setHeaderUnderlineStyle(std::string lineStyle);
    
    friend std::ostream& operator<<(std::ostream& os, Table& table);
    
    
private:
    //MARK: Private Member Functions
    inline std::ostream& alignText(std::ostream& os,
                                   std::string& text);
    
    inline std::ostream& padding(std::ostream& os,
                                 size_t paddingSize);
    
    inline std::ostream& printHeader(std::ostream& os);
    
    inline std::ostream& printTableBody(std::ostream& os);
    
    inline std::ostream& underlineHeader(std::ostream& os);
    
    
    
    //MARK: Private Members
    
    // Parameters adjustable via setter.
    bool headerUnderlined;
    TextAlignment textAlignment;
    size_t columnWidth;
    std::string columnSeparator;
    std::string headerUnderlineStyle;
    
    // Parameters based on header/data input and/or other members
    size_t numberOfColumns;
    size_t numberOfRows;
    size_t columnSeparatorWidth;
    size_t tableWidth;
    
    // Input data
    std::vector<std::string> const& header;
    std::vector< std::vector<std::string> > const& data;
    
};

//MARK: Implementation
Table::Table(std::vector<std::string> const& _header,
             std::vector< std::vector<std::string> > const& _data,
             TextAlignment _textAlignment,
             bool _headerUnderlined,
             std::string underlineStyle,
             size_t _columnWidth,
             std::string _columnSeparator)
: header(_header)
, data(_data)
, textAlignment(_textAlignment)
, headerUnderlined(_headerUnderlined)
, headerUnderlineStyle(underlineStyle)
, columnWidth(_columnWidth)
, columnSeparator(_columnSeparator)
, numberOfColumns(_header.size())
{
    columnSeparatorWidth = (columnSeparator == "\t") ? 4 : columnSeparator.size();
    tableWidth = (columnSeparatorWidth + columnWidth) * numberOfColumns - columnSeparatorWidth;
    numberOfRows = 0;
    for (auto const & column : data)
    {
        if (numberOfRows < column.size()) numberOfRows = column.size();
    }
}

//MARK: Setters
void Table::setColumnSeparator(std::string separator)
{
    columnSeparator = separator;
}

void Table::setTextAlignment(TextAlignment alignment)
{
    textAlignment = alignment;
}

void Table::setColumnWidth(size_t width)
{
    columnWidth = width;
}

void Table::setHeaderUnderline(bool setUnderline)
{
    headerUnderlined = setUnderline;
};

void Table::setHeaderUnderlineStyle(std::string lineStyle)
{
    headerUnderlineStyle = lineStyle;
}


// MARK: Private Member Functions
inline std::ostream& Table::alignText(std::ostream& os,
                                      std::string& text)
{
    size_t whitespace = columnWidth - text.size();
    switch (textAlignment)
    {
        case TextAlignment::leftAligned:
            os << text;
            padding(os, whitespace);
            break;
                
        case TextAlignment::rightAligned:
            padding(os, whitespace);
            os << text;
            break;
            
        case TextAlignment::centered:
            size_t leading = whitespace / 2;
            size_t trailing = whitespace - leading;
            padding(os, leading);
            os << text;
            padding(os, trailing);
            break;
    }
    return os;
}

inline std::ostream& Table::padding(std::ostream& os,
                                    size_t paddingSize)
{
    for(int j = 0; j <= paddingSize; ++j) os << " ";
    return os;
}

inline std::ostream& Table::printHeader(std::ostream& os)
{
    for(size_t i = 0; i < numberOfColumns; ++i)
    {
        std::string name = header[i];
        alignText(os, name);
        if (i < numberOfColumns) os << columnSeparator;
    }
    
    os << std::endl;
    return os;
}

inline std::ostream& Table::underlineHeader(std::ostream& os)
{
    for (uint i = 0; i < tableWidth; ++i) os << headerUnderlineStyle;
    os << std::endl;
    return os;
}

inline std::ostream& Table::printTableBody(std::ostream& os)
{
    // print table data
    for (size_t row = 0; row < numberOfRows; ++row)
    {
        size_t columnCounter = 0;
        for (auto const & column : data)
        {
            // check if there are enough elements
            std::string item = column.at(row % column.size());
            alignText(os, item);
            if (columnCounter < numberOfColumns) os << columnSeparator;
            ++columnCounter;
        }
        os << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, Table& table)
                        
{
    table.printHeader(os);
    if (table.headerUnderlined) table.underlineHeader(os);
    table.printTableBody(os);
    return os;
}

}} // utils // FastEMD
#endif /* Table_h */
