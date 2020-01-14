/*!
 *	\file		utility.cpp
 *	\brief		Implements library utilities
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#include <sys/types.h>
#include <sys/ioctl.h>

#include <egg/commandline/utility.hpp>


namespace egg
{
namespace commandline
{

const int
utility::width() noexcept
{
  constexpr int default_width = 80;

  struct winsize w;
  ::ioctl(0, TIOCGWINSZ, &w);

  return (w.ws_col > 0 ? w.ws_col : default_width);
}

std::string
utility::indent(
  const int theIndentSize)
{
  std::string result;

  for (auto i = 0; i < theIndentSize; i++)
    result.push_back(' ');

  return result;
}


void
utility::split(
  const std::string&  source,
  string_list&        result)
{
  auto i = source.cbegin();

  while (i < source.cend())
  {
    while (i < source.cend() && std::isspace(*i))
      ++i;

    if (i == source.cend())
      break;

    std::string s;

    while (i < source.cend() && !std::isspace(*i))
      s.push_back(*i++);

    result.emplace_back(s);
  }
}

const std::string
utility::format(
    const std::string& source)
{
  const int terminal_width = utility::width();
  utility::string_list split_list;
  utility::split(source, split_list);

  std::string result;
  int space_left = terminal_width;
  for (auto word : split_list)
  {
    if (word.size() > space_left)
    {
      result.push_back('\n');
      space_left = terminal_width;
    }

    result.append(word);
    space_left -= word.size();

    if (space_left)
    {
      result.push_back(' ');
      --space_left;
    }
  }
  return result;
}

} // End of egg::commandline namespace
} // End of egg namespace

/* End of file */
