/*!
 *	\file		description.cpp
 *	\brief		Implements command line description
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#include <egg/commandline/description.hpp>


namespace egg
{
namespace commandline
{

// Description
description::description(
  const std::string theName,
  const std::string theVersion,
  const std::string theCopyright,
  const std::string theHeader,
  const std::string theTralier)
  : name(theName),
    version(theVersion),
    copyright(theCopyright),
    header(theHeader),
    trailer(theTralier)
{}

description::description(
    const description& other)
  : name(other.name),
    version(other.version),
    copyright(other.copyright),
    header(other.header),
    trailer(other.trailer)
{}

description::~description() noexcept
{}

} // End of egg::commandline namespace
} // End of egg namespace

/* End of file */
