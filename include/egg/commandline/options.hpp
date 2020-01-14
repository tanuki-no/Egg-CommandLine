/*!
 *	\file		options.hpp
 *	\brief		Declares command line options combined
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#ifndef EGG_COMMAND_LINE_OPTIONS
#define EGG_COMMAND_LINE_OPTIONS

#include <string>
#include <vector>
#include <map>

#include <egg/commandline/option.hpp>


namespace egg
{
namespace commandline
{

// The command line options
struct EGG_PUBLIC options
{
  // Construct/destruct
  options() noexcept;
 ~options() noexcept;

  options(const options&);
  options& operator=(const options&);

  options(options&&) noexcept;
  options& operator=(options&&) noexcept;

  // Easy build
  options&
  operator()(
      const char          theShort,
      const std::string&  theLong,
      const std::string&  theDescription);

  template <typename T>
  options&
  operator()(
      const char          theShort,
      const std::string&  theLong,
      const std::string&  theDescription,
      T                   theValue);

  // Check
  bool
  exist(
      const char key) const noexcept;

  bool
  exist(
      const std::string& key) const noexcept;

  // Lookup
  const option&
  get(
      const char key) const;

  const option&
  get(
      const std::string& key) const;

  // Assign
  template <typename T>
  void assign(
      const char          theKey,
      T                   theValue);

  template <typename T>
  void assign(
      const std::string&  theKey,
      T                   theValue);

  // Nice output
  const std::string
  to_string(
      const unsigned indent = 2) const;

protected:

  void check(
      const char          theShort,
      const std::string&  theLong);

private:

  typedef std::vector<option> data_type;

  typedef std::map
  <
    char,
    data_type::size_type
  > short_index_type;

  typedef std::map
  <
    std::string,
    data_type::size_type
  > long_index_type;

private:

  data_type         _options;
  short_index_type  _short;
  long_index_type   _long;
};

} // End of egg::commandline namespace
} // End of egg namespace

namespace egg
{
namespace commandline
{

template <>
inline options&
options::operator()(
      const char          theShort,
      const std::string&  theLong,
      const std::string&  theDescription,
      variable            theValue)
{
  check(theShort, theLong);

  _options.emplace_back(theShort, theLong, theDescription, theValue);

  if (theShort)
    _short[theShort]  = _options.size() - 1;

  if (theLong.size())
    _long[theLong]    = _options.size() - 1;

  return *this;
}

template <typename T>
options&
options::operator()(
    const char            theShort,
    const std::string&    theLong,
    const std::string&    theDescription,
    T                     theValue)
{
  check(theShort, theLong);

  variable v(theValue);
  _options.emplace_back(theShort, theLong, theDescription, v);

  if (theShort)
    _short[theShort]  = _options.size() - 1;

  if (theLong.size())
    _long[theLong]    = _options.size() - 1;

  return *this;
}

template <typename T>
void
options::assign(
    const char            theKey,
    T                     theValue)
{
  auto result = _short.find(theKey);

  if (result != _short.end())
  {
    variable v(theValue);
    _options[result->second].assign(std::move(v));
  }
}

template <typename T>
void
options::assign(
    const std::string&    theKey,
    T                     theValue)
{
  auto result = _long.find(theKey);

  if (result != _long.end())
  {
    variable v(theValue);
    _options[result->second].assign(std::move(v));
  }
}

} // End of egg::commandline namespace
} // End of egg namespace

#endif  // EGG_COMMAND_LINE_OPTIONS

/* End of file */
