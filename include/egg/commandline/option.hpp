/*!
 *	\file		option.hpp
 *	\brief		Declares command line option
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#ifndef EGG_COMMAND_LINE_OPTION
#define EGG_COMMAND_LINE_OPTION

#include <string>

#include <egg/common.hpp>
#include <egg/variable.hpp>


namespace egg
{
namespace commandline
{

// The command line option
struct EGG_PUBLIC option
{
  option() noexcept;

  option(
      const char          theShort,
      const std::string&  theLong,
      const std::string&  theDescription);

  // If the value is set, then it is the default value
  option(
      const char          theShort,
      const std::string&  theLong,
      const std::string&  theDescription,
      variable&           theValue);

  option(const option& other);
  option& operator=(const option& other);

  option(option&& other) noexcept;
  option& operator=(option&& other) noexcept;

 ~option() noexcept;

  const char
  get_short() const noexcept;

  const std::string&
  get_long() const noexcept;

  const std::string&
  get_description() const noexcept;

  const variable&
  get_value() const noexcept;

  const bool
  has_argument() const noexcept;

  template <typename T>
  void assign(const T& t);

  template <typename T>
  void assign(T&& t);

private:

  char          _short;
  std::string   _long;
  std::string   _description;
  variable      _value;
  bool          _has_argument;
};

} // End of egg::commandline namespace
} // End of egg namespace

namespace egg
{
namespace commandline
{

inline const char
option::get_short() const noexcept
{ return _short; }

inline const std::string&
option::get_long() const noexcept
{ return _long; }

inline const std::string&
option::get_description() const noexcept
{ return _description; }

inline const variable&
option::get_value() const noexcept
{
  return _value;
}

inline const bool
option::has_argument() const noexcept
{
  return _has_argument;
}

template <>
inline void
option::assign<egg::variable>(
    const egg::variable& v)
{
  if (!_has_argument)
    return;

  _value = v;
}

template <>
inline void
option::assign<egg::variable>(
    egg::variable&& v)
{
  if (!_has_argument)
    return;

  _value = std::move(v);
}

template <typename T>
inline void
option::assign(const T& t)
{
  if (!_has_argument)
    return;

  _value = egg::variable(t);
}

template <typename T>
inline void
option::assign(T&& t)
{
  if (!_has_argument)
    return;

  _value = std::move(egg::variable(std::move(t)));
}

} // End of egg::commandline namespace
} // End of egg namespace

#endif  // EGG_COMMAND_LINE_OPTION

/* End of file */
