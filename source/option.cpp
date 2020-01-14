/*!
 *	\file		option.cpp
 *	\brief		Implements command line option
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#include <egg/commandline/option.hpp>


namespace egg
{
namespace commandline
{

option::option() noexcept
  : _short(0),
    _has_argument(false)
{}

option::option(
  const char          theShort,
  const std::string&  theLong,
  const std::string&  theDescription)
  : _short(theShort),
    _long(theLong),
    _description(theDescription),
    _has_argument(false)
{}

option::option(
  const char          theShort,
  const std::string&  theLong,
  const std::string&  theDescription,
  variable&              theValue)
  : _short(theShort),
    _long(theLong),
    _description(theDescription),
    _value(theValue),
    _has_argument(true)
{}

option::~option() noexcept
{}

option::option(
    const option& other)
  : _short(other._short),
    _long(other._long),
    _description(other._description),
    _value(other._value),
    _has_argument(other._has_argument)
{}

option&
option::operator=(
    const option& other)
{
  if (this != &other)
  {
    _short        = other._short;
    _long         = other._long;
    _description  = other._description;
    _value        = other._value;
    _has_argument = other._has_argument;
  }

  return *this;
}

option::option(
    option&& other) noexcept
  : _short(other._short),
    _long(std::move(other._long)),
    _description(std::move(other._description)),
    _value(std::move(other._value)),
    _has_argument(other._has_argument)
{
  other._short = 0;
  other._has_argument = false;
}

option&
option::operator=(
    option&& other) noexcept
{
  if (this != &other)
  {
    _short        = other._short;
    _long         = std::move(other._long);
    _description  = std::move(other._description);
    _value        = std::move(other._value);
    _has_argument = other._has_argument;

    other._short        = 0;
    other._has_argument = false;
  }

  return *this;
}

} // End of egg::commandline namespace
} // End of egg namespace

/* End of file */
