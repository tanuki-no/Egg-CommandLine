/*!
 *	\file		description.hpp
 *	\brief		Declares command line description
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#ifndef EGG_COMMAND_LINE_DESCRIPTION
#define EGG_COMMAND_LINE_DESCRIPTION

#include <string>

#include <egg/common.hpp>


namespace egg
{
namespace commandline
{

// The command line description
struct EGG_PUBLIC description
{
  description() = delete;

  description(
      const std::string theName,
      const std::string theVersion,
      const std::string theCopyright,
      const std::string theHeader,
      const std::string theTralier);

  description(const description&);
  description& operator=(const description&) = delete;

  description& operator=(description&&) = delete;
  description(description&&) = delete;

  ~description() noexcept;

  const std::string name;
  const std::string version;
  const std::string copyright;
  const std::string header;
  const std::string trailer;
};

} // End of egg::commandline namespace
} // End of egg namespace

#endif  // EGG_COMMAND_LINE_DESCRIPTION

/* End of file */
