/*!
 *	\file		utility.hpp
 *	\brief		Declares various helpers used by the library
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#ifndef EGG_COMMAND_LINE_UTILITY
#define EGG_COMMAND_LINE_UTILITY

#include <string>
#include <vector>
#include <system_error>

#include <egg/common.hpp>


namespace egg
{
namespace commandline
{

struct EGG_PRIVATE utility
{
  typedef std::vector<std::string> string_list;

  static const int
  width() noexcept;

  static std::string
  indent(
      const int theIndentSize);

  static void
  split(
      const std::string&  source,
      string_list&        result);

  // Format the text for specific needs
  static const std::string
  format(
      const std::string& source);
};

} // End of egg::commandline namespace
} // End of egg namespace

#endif  // EGG_COMMAND_LINE_UTILITY

/* End of file */
