/*!
 *	\file		options.cpp
 *	\brief		Implements command line options
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#include <egg/commandline/options.hpp>
#include <egg/commandline/utility.hpp>


namespace egg
{
namespace commandline
{

options::options() noexcept
{}

options::~options() noexcept
{}

options::options(
    const options& other)
  : _options(other._options),
    _short(other._short),
    _long(other._long)
{}

options&
options::operator=(
    const options& other)
{
  if (this != &other)
  {
    _options  = other._options;
    _short    = other._short;
    _long     = other._long;
  }

  return *this;
}

options::options(
    options&& other) noexcept
  : _options(std::move(other._options)),
    _short(std::move(other._short)),
    _long(std::move(other._long))
{}

options&
options::operator=(
    options&& other) noexcept
{
  if (this != &other)
  {
    _options  = std::move(other._options);
    _short    = std::move(other._short);
    _long     = std::move(other._long);
  }

  return *this;
}

// Construct option
options&
options::operator()(
    const char          theShort,
    const std::string&  theLong,
    const std::string&  theDescription)
{
  check(theShort, theLong);

  _options.emplace_back(
        theShort,
        theLong,
        theDescription);

  if (theShort)
    _short[theShort]  = _options.size() - 1;

  if (theLong.size())
    _long[theLong]    = _options.size() - 1;

  return *this;
}

// Helper
void
options::check(
    const char          theShort,
    const std::string&  theLong)
{
  if (!theShort && theLong.empty())
  {
    std::string msg("No option set. Please set al least one option: long or short.");
    throw std::invalid_argument(msg);
  }

  if (_short.count(theShort))
  {
    std::string msg("Short option '");
    msg.push_back(theShort);
    msg += "' exists.";
    throw std::invalid_argument(msg);
  }

  if (_long.count(theLong))
  {
    std::string msg("Long option '" + theLong + "' exists.");
    throw std::invalid_argument(msg);
  }
}

// Accessors
bool
options::exist(
    const char key) const noexcept
{
  return (_short.find(key) == _short.cend() ? false : true);
}

bool
options::exist(
    const std::string& key) const noexcept
{
  return (_long.find(key) == _long.cend() ? false : true);
}

const option&
options::get(
    const char key) const
{
  auto result = _short.find(key);

  if (result != _short.end())
    return _options[result->second];

  std::string msg("Option '");
  msg.push_back(key);
  msg.append("' not found!");
  throw std::invalid_argument(msg);
}

const option&
options::get(
    const std::string& key) const
{
  auto result = _long.find(key);

  if (result != _long.end())
    return _options[result->second];

  std::string msg("Option \"");
  msg.append(key);
  msg.append("\" not found!");
  throw std::invalid_argument(msg);
}

const std::string
options::to_string(
    const unsigned indent) const
{
  // Declaration
  std::string result;

  auto longest = [](const long_index_type& li) -> std::string::size_type
  {
    std::string::size_type result = 0;

    for (auto i : li)
      result = std::max(result, i.first.size());

    return result;
  };

  auto get_short = [](const option& o) -> std::string
  {
    std::string result;

    if (o.get_short())
    {
      result.push_back('-');
      result.push_back(o.get_short());
      result.push_back(',');
      result.push_back(' ');
    }

    return result;
  };

  const std::string indent_string(
        std::move(utility::indent(indent)));

  const int teminal_width = utility::width();

  const std::string::size_type option_width =
      indent + 4 + 2 + longest(_long) + 2;

  const std::string desc_indent_string(
        std::move(utility::indent(option_width)));

  const int desc_width =
      teminal_width - option_width;

  // Build help string
  utility::string_list split_list;
  for (auto o : _options)
  {
    // Construct option record from indent, short and long options
    std::string row(indent_string + get_short(o)  + "--" + o.get_long());

    // Pad the rest
    row += utility::indent(option_width - row.length());

    // Split the description by the spaces
    split_list.clear();
    utility::split(o.get_description(), split_list);

    // Add default value if exists
    if (!o.get_value().is_empty())
    {
      split_list.push_back("(Default");
      split_list.push_back("value:");
      split_list.push_back(o.get_value().to_string() + ',');
      split_list.push_back("type:");
      split_list.push_back(o.get_value().to_type_string() + ')');
    }

    // Write description
    std::string::size_type space_left = desc_width;
    for (auto word : split_list)
    {
      if (word.size() > space_left)
      {
        row.push_back('\n');
        row.append(desc_indent_string);
        space_left = desc_width;
      }

      row.append(word);
      space_left -= word.size();

      if (space_left)
      {
        row.push_back(' ');
        --space_left;
      }
    }

    // Append option
    result += row + '\n';
  }

  return result;
}

} // End of egg::commandline namespace
} // End of egg namespace

/* End of file */
