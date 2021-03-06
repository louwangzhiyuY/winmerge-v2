//
// PrettyPrint.cpp
//
// $Id: //poco/1.4/XML/samples/PrettyPrint/src/PrettyPrint.cpp#1 $
//
// This sample demonstrates the SAXParser, WhitespaceFilter,
// InputSource and XMLWriter classes.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/SAX/SAXParser.h"
#include "Poco/SAX/WhitespaceFilter.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/XML/XMLWriter.h"
#include "Poco/Exception.h"
#include <iostream>


using Poco::XML::SAXParser;
using Poco::XML::XMLReader;
using Poco::XML::WhitespaceFilter;
using Poco::XML::InputSource;
using Poco::XML::XMLWriter;
using Poco::Exception;


int main(int argc, char** argv)
{
	// read XML from standard input and pretty-print it to standard output

	SAXParser parser;
	WhitespaceFilter filter(&parser);
	
	XMLWriter writer(std::cout, XMLWriter::CANONICAL | XMLWriter::PRETTY_PRINT);
	writer.setNewLine(XMLWriter::NEWLINE_LF);

	filter.setContentHandler(&writer);
	filter.setDTDHandler(&writer);
	filter.setProperty(XMLReader::PROPERTY_LEXICAL_HANDLER, static_cast<Poco::XML::LexicalHandler*>(&writer));

	try
	{
		InputSource source(std::cin);
		filter.parse(&source);
	}
	catch (Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}

	return 0;
}
