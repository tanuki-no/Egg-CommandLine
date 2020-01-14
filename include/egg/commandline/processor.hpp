/*!
 *	\file		processor.hpp
 *	\brief		Declares command line arguments processor
 *	\author		Vladislav "Tanuki" Mikhailikov \<vmikhailikov\@gmail.com\>
 *	\copyright	GNU GPL v3
 *	\date		14/01/2020
 *	\version	1.0
 */

#ifndef EGG_COMMAND_LINE_PROCESSOR
#define EGG_COMMAND_LINE_PROCESSOR

#include <vector>
#include <string>

#include <egg/common.hpp>

#include <egg/commandline/description.hpp>
#include <egg/commandline/options.hpp>

#include <egg/registry/value.hpp>


namespace egg
{
namespace commandline
{

/*
 * The registry is the non-persistent configuration storage that permits
 * universal hierarchical access to unstructured data with embeded conversion
 * and multiple access to the stored data.
 *
 * Command line stored in registry under ["cmd"] tag with the the name of command
 * line parameter after it, either/or short (one char) or long (string)
 *
 * Example:
 *
 * <egg::registry::value>["cmd"]["configuration"] = "/etc/sample.xml";
 * <egg::registry::value>["cmd"]["C"] = "/etc/sample.xml";
 *
 * Ordered list of arguments available as:
 *
 * <egg::registry::value>["cmd"][' '][<digit>] = <arg>
 *
 * where short and long options available as:
 *
 * <egg::registry::value>["cmd"]['\t'][<digit>]["short"]
 *
 * and
 *
 * <egg::registry::value>["cmd"]['\t'][<digit>]["long"]
 */
struct EGG_PUBLIC processor
{
  typedef std::vector<std::string>	string_list;
  typedef egg::registry::value		value;

  processor() = delete;

  processor(
      const egg::commandline::description&	theDescription,
      const egg::commandline::options&		theOptions,
      const bool				optionsFirst = true);

  processor(const processor&) = delete;
  processor& operator=(const processor&) = delete;

  processor(processor&&) = delete;
  processor& operator=(processor&&) = delete;

 ~processor() noexcept;

  void parse(
      const int		argc,
      const char*	argv[],
      value&		the_result);

  const string_list&
  values() const noexcept;

  const egg::commandline::options&
  options() const noexcept;

  const std::string
  help();

  const bool
  found(const char, value&) const noexcept;

  const bool
  found(const std::string&, value&) const noexcept;

private:

  bool				_optionsFirst;
  egg::commandline::description	_description;
  egg::commandline::options	_options;
  string_list			_valuelist;
};

} // End of egg::commandline namespace
} // End of egg namespace

#endif  // EGG_COMMAND_LINE_PROCESSOR

/* End of file */
